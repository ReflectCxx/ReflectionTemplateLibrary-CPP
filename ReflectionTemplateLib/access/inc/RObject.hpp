#pragma once

#include <optional>
#include <iostream>
#include <cassert>

#include "RObject.h"
#include "RObjectPtr.h"
#include "ReflectCast.h"
#include "RObjectBuilder.h"

namespace rtl::access
{
    inline RObject::RObject(std::any&& pObject, Cloner&& pCloner, const detail::RObjectId& pRObjectId)
        : m_getClone(std::forward<Cloner>(pCloner))
        , m_object(std::forward<std::any>(pObject))
        , m_objectId(pRObjectId)
    {
        if (m_objectId.m_allocatedOn == alloc::Heap) {
            RObject::m_rtlOwnedHeapAllocCount.fetch_add(1);
        }
    }


    inline RObject::RObject(RObject&& pOther) noexcept
        : m_object(std::move(pOther.m_object))
        , m_getClone(std::move(pOther.m_getClone))
        , m_objectId(pOther.m_objectId)
    {
        // Explicitly clear moved-from source
        pOther.m_object.reset();
        pOther.m_objectId.reset();
        pOther.m_getClone = nullptr;
    }


    inline std::size_t RObject::getConverterIndex(const std::size_t pToTypeId) const
    {
        if (!isEmpty()){
            for (std::size_t index = 0; index < m_objectId.m_converters.size(); index++) {
                if (m_objectId.m_converters[index].first == pToTypeId) {
                    return index;
                }
            }
        }
        return index_none;
    }


    template<>
    inline std::pair<error, RObject> RObject::createCopy<alloc::Heap>() const
    {
        error err = error::None;
        return { err, m_getClone(err, *this, alloc::Heap) };
    }


    template<>
    inline std::pair<error, RObject> RObject::createCopy<alloc::Stack>() const
    {
        if (m_objectId.m_allocatedOn == alloc::Stack) {
            //std::any will call the copy-ctor of the containing type.
            return { error::None, RObject(*this) };
        }
        else if (m_objectId.m_allocatedOn == alloc::Heap) {
            //contains pointer, need type to access the object. (view<T>, T=?)
            error err = error::None;
            return { err, m_getClone(err, *this, alloc::Stack) };
        }
        assert(false && "Disaster: invalid RObject cloning! System predictability compromised.");
        return { error::None,  RObject() }; //dead code. compiler warning ommited.
    }


    template<alloc _allocOn>
    inline std::pair<error, RObject> RObject::clone() const
    {
        static_assert(_allocOn != alloc::None, "Instance cannot be created with 'alloc::None' option.");
        if (isEmpty()) {
            return { error::EmptyRObject, RObject() };
        }
        else if (m_objectId.m_wrapperType == Wrapper::None && !m_getClone) {
            return { error::Instantiating_typeNotCopyConstructible, RObject() };
        }
        else if (m_objectId.m_wrapperType == Wrapper::Unique) {
            return { error::ReflectingUniquePtrCopyDisallowed, RObject() };
        }
        else return createCopy<_allocOn>();
    }


    template <class T, traits::enable_if_std_wrapper<T>>
    std::optional<rtl::view<T>> RObject::view() const
    {
        traits::validate_view<T>();
        if (m_objectId.m_wrapperType == Wrapper::Shared)
        {
            if (detail::TypeId<T>::get() == m_objectId.m_wrapperTypeId)
            {
                const T& sptrRef = *extract<T>();
                return std::optional<rtl::view<T>>(sptrRef);   //No Copy, init by reference.
            }
        }
        return std::nullopt;
    }


    template <class T, traits::enable_if_raw_pointer<T>>
    std::optional<rtl::view<T>> RObject::view() const
    {
        traits::validate_view<T>();
        using _T = traits::base_t<T>;
        if (detail::TypeId<_T>::get() == m_objectId.m_typeId)
        {
            const _T& valueRef = *extract<_T>();
            return std::optional<rtl::view<T>>(std::move(&valueRef));   //Copy pointer.
        }
        else {
            const std::size_t index = getConverterIndex(detail::TypeId<T>::get());
            if (index != index_none) {
                return performConversion<T>(index);
            }
        }
        return std::nullopt;
    }


    template <class T, traits::enable_if_not_std_wrapper_or_raw_ptr<T>>
    inline std::optional<rtl::view<T>> RObject::view() const
    {
        traits::validate_view<T>();
        const std::size_t asTypeId = detail::TypeId<T>::get();
        if (asTypeId == m_objectId.m_typeId)
        {
            using _T = traits::base_t<T>;
            const _T& valueRef = *extract<T>();
            return std::optional<rtl::view<T>>(valueRef);   //No Copy, init by reference.
        }
        else {
            const std::size_t index = getConverterIndex(asTypeId);
            if (index != index_none) {
                return performConversion<T>(index);
            }
        }
        return std::nullopt;
    }


    template<class T>
    inline bool RObject::canViewAs() const
    {
        if constexpr (traits::is_view_suported<T>())
        {
            using _T = traits::base_t<T>;
            if constexpr (std::is_pointer_v<T>) {
                if (m_objectId.m_ptrTypeId == detail::TypeId<_T*>::get()) {
                    return true;
                }
            }
            else if constexpr (traits::std_wrapper<_T>::type != Wrapper::None) {
                if (m_objectId.m_wrapperTypeId == traits::std_wrapper<_T>::id()) {
                    return true;
                }
            }
            const auto& typeId = detail::TypeId<T>::get();
            return (m_objectId.m_typeId == typeId || getConverterIndex(typeId) != index_none);
        }
        return false;
    }


    template <class T>
    inline std::optional<rtl::view<T>> RObject::performConversion(const std::size_t pIndex) const
    {
        ConversionKind conversionKind = ConversionKind::NotDefined;
        const std::any& viewObj = m_objectId.m_converters[pIndex].second(m_object, m_objectId.m_isPointer, conversionKind);
        if (viewObj.has_value())  //if true, 'conversionKind' can only be 'ConversionKind::ByRef/ByValue'
        {
            const T& viewRef = std::any_cast<const T&>(viewObj);
            if (conversionKind == ConversionKind::ByRef) {
                return std::optional<rtl::view<T>>(std::in_place, viewRef);
            }
            else /*if (ConversionKind == ConversionKind::ByValue)*/ {
                if constexpr (std::is_copy_constructible_v<T>) {
                    return std::optional<rtl::view<T>>(std::in_place, T(viewRef));
                }
                else {
                    assert(false && "Disaster: Unexpecetd conversion! System predictability compromised.");
                }
            }
        }
        else {/* This ought to be a dead code block, still..TODO: handle ConversionKind::NoDefined/BadAnyCast */ }
        return std::nullopt;
    }


    template<class T>
    inline const T* RObject::extract() const
    {
        if (m_objectId.m_isPointer == IsPointer::Yes)
        {
            if (m_objectId.m_wrapperType == Wrapper::Unique || m_objectId.m_allocatedOn == alloc::Heap)
            {
                using U = detail::RObjectPtr<T>;
                const U& objRef = std::any_cast<const U&>(m_object);
                return objRef.m_ptr;
            }
            else if (m_objectId.m_wrapperType == Wrapper::Shared)
            {   //std::any holds the actual shared_ptr<T> object.
                const std::size_t asTypeId = detail::TypeId<T>::get();
                if (asTypeId == m_objectId.m_wrapperTypeId) 
                {   // T is std::shared_ptr<U>, so cast directly to 'const T*' (pointer to shared_ptr<U>)
                    const T& sptrRef = std::any_cast<const T&>(m_object);
                    return &sptrRef;
                }
                else if (asTypeId == m_objectId.m_typeId) 
                {   //'T' is not std::shared_ptr<U>, its the pointee type held inside std::shared_ptr<U>.
                    const auto& sptrRef = std::any_cast<const std::shared_ptr<T>&>(m_object);
                    return sptrRef.get();
                }
            }
            else if (m_objectId.m_wrapperType == Wrapper::None)
            {
                return (std::any_cast<const T*>(m_object));
            }
        }
        else
        {
            const T& valueRef = std::any_cast<const T&>(m_object);
            return &valueRef;
        }
        assert(false && "Disaster: Unexpecetd type! System predictability compromised.");
        return nullptr;
    }
}