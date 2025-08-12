#pragma once

#include <optional>
#include <iostream>
#include <cassert>

#include "RObject.h"
#include "RObjectUPtr.h"
#include "ReflectCast.h"
#include "RObjectBuilder.h"

namespace rtl::access
{
    inline RObject::RObject(std::any&& pObject, Cloner&& pCloner, const detail::RObjectId& pRObjectId)
        : m_getClone(std::forward<Cloner>(pCloner))
        , m_object(std::forward<std::any>(pObject))
        , m_objectId(pRObjectId)
    { }

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
        if (!isEmpty()) {
            for (std::size_t index = 0; index < m_objectId.m_converters.size(); index++) {
                if (m_objectId.m_converters[index].first == pToTypeId) {
                    return index;
                }
            }
        }
        return index_none;
    }


    template<>
    inline std::pair<error, RObject> RObject::clone<alloc::Heap>() const
    {
        if (isEmpty()) {
            return { error::EmptyRObject, RObject() };
        }
        else if (m_objectId.m_containsAs == detail::Contains::Wrapper && 
            m_objectId.m_allocatedOn != alloc::Heap) {

            return { error::ReflectingStlWrapper_copyOnHeapDisallowed, RObject() };
        }
        error err = error::None;
        return { err, m_getClone(err, *this, alloc::Heap) };
    }


    template<>
    inline std::pair<error, RObject> RObject::clone<alloc::Stack>() const
    {
        if (isEmpty()) {
            return { error::EmptyRObject, RObject() };
        }
        else if (m_objectId.m_allocatedOn == alloc::Stack) {
            //std::any will call the copy-ctor of the containing type.
            return { error::None, RObject(*this) };
        }
        else if (m_objectId.m_allocatedOn == alloc::Heap) {
            //need to call 'new T()', but T=?, call the cloner-lambda.
            error err = error::None;
            return { err, m_getClone(err, *this, alloc::Stack) };
        }
        assert(false && "Disaster: invalid RObject cloning! System predictability compromised.");
        return { error::None,  RObject() }; //dead code. compiler warning ommited.
    }


    template<class T>
    inline bool RObject::canViewAs() const
    {
        if constexpr (traits::is_view_suported<T>())
        {
            using _T = traits::raw_t<T>;
            if constexpr (std::is_pointer_v<T>) {
                if (m_objectId.m_ptrTypeId == detail::TypeId<_T*>::get()) {
                    return true;
                }
            }
            else if constexpr (traits::std_wrapper<_T>::type != detail::Wrapper::None) {
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
        detail::ConversionKind conversionKind = detail::ConversionKind::NotDefined;
        const std::any& viewObj = m_objectId.m_converters[pIndex].second(m_object, m_objectId.m_containsAs, conversionKind);
        if (viewObj.has_value())  //if true, 'conversionKind' can only be 'ConversionKind::ByRef/ByValue'
        {
            const T& viewRef = std::any_cast<const T&>(viewObj);
            if (conversionKind == detail::ConversionKind::ByRef) {
                return std::optional<rtl::view<T>>(std::in_place, viewRef);
            }
            else /*if (ConversionKind == ConversionKind::ByValue)*/ {
                if constexpr (std::is_copy_constructible_v<T>) {
                    return std::optional<rtl::view<T>>(std::in_place, T(viewRef));
                }
                else {
                    assert(false && "exception: invalid conversion! Type validation system failed.");
                }
            }
        }
        else {/* This ought to be a dead code block, still..TODO: handle ConversionKind::NoDefined/BadAnyCast */ }
        return std::nullopt;
    }
}



namespace rtl::access
{
    template<class T, traits::enable_if_unique_ptr<T>>
    inline T RObject::extractWrapper() const 
    {
        using _T = traits::std_wrapper<traits::raw_t<T>>::value_type;
        try {
            if (m_objectId.m_wrapperType == detail::Wrapper::Unique) {
                using U = detail::RObjectUPtr<_T>;
                const U& uptr = std::any_cast<const U&>(m_object);
                return (const_cast<U&>(uptr)).release();
            }
            else return std::unique_ptr<_T>();
        }
        catch (const std::bad_any_cast&) {
            return std::unique_ptr<_T>();
        }
    }


    template<class T, traits::enable_if_shared_ptr<T>>
    inline const T* RObject::extractWrapper() const
    {
        try {
            if (m_objectId.m_wrapperType == detail::Wrapper::Shared)
            {
                using _T = traits::std_wrapper<traits::raw_t<T>>::value_type;
                if constexpr (traits::is_const_v<_T>)
                {
                    if (m_objectId.m_isWrappingConst) {
                        using U = std::shared_ptr<const _T>;
                        const U& sptrRef = std::any_cast<const U&>(m_object);
                        return static_cast<const T*>(&sptrRef);
                    }
                }
                else
                {
                    using U = std::shared_ptr<_T>;
                    const U& sptrRef = std::any_cast<const U&>(m_object);
                    return static_cast<const T*>(&sptrRef);
                }
            }
            return nullptr;
        }
        catch (const std::bad_any_cast&) {
            return nullptr;
        }
    }


    template <class T, traits::enable_if_std_wrapper<T>>
    std::optional<rtl::view<T>> RObject::view() const
    {
        traits::validate_view<T>();
        using _T = traits::raw_t<T>;
        const detail::Wrapper wrapper = m_objectId.m_wrapperType;
        if (wrapper == detail::Wrapper::Shared || wrapper == detail::Wrapper::Unique)
        {
            if (detail::TypeId<T>::get() == m_objectId.m_wrapperTypeId)
            {
                using W = traits::std_wrapper<_T>;
                if constexpr (W::type == detail::Wrapper::Unique) {
                    _T sptrRef = extractWrapper<_T>();
                    return std::optional<rtl::view<T>>(std::move(sptrRef));
                }
                else if constexpr (W::type == detail::Wrapper::Shared) {
                    const _T& sptrRef = *extractWrapper<_T>();
                    return std::optional<rtl::view<T>>(sptrRef);
                }
            }
        }
        return std::nullopt;
    }
}



namespace rtl::access
{
    template<class T>
    inline const T* RObject::extractRefrence() const
    {
        try {
            switch (m_objectId.m_containsAs)
            {
            case detail::Contains::Pointer: {
                return (std::any_cast<const T*>(m_object));
            }
            case detail::Contains::Wrapper: {
                return extractFromWrapper<T>();
            }
            case detail::Contains::Value: {
                const T& valueRef = std::any_cast<const T&>(m_object);
                return static_cast<const T*>(&valueRef);
            }
            }
            return nullptr;  //dead-code, eliminates compiler warning.
        }
        catch (const std::bad_any_cast&) {
            return nullptr;
        }
    }


    template<class T>
    inline const T* access::RObject::extractFromWrapper() const
    {
        try {
            if (m_objectId.m_wrapperType == detail::Wrapper::Unique)
            {
                using U = detail::RObjectUPtr<T>;
                const U& objRef = std::any_cast<const U&>(m_object);
                return objRef.m_ptr;
            }
            if (m_objectId.m_wrapperType == detail::Wrapper::Shared)
            {
                if (m_objectId.m_isWrappingConst) {
                    using U = std::shared_ptr<const T>;
                    const auto& sptrRef = std::any_cast<const U&>(m_object);
                    return static_cast<const T*>(sptrRef.get());
                }
                else {
                    using U = std::shared_ptr<T>;
                    const auto& sptrRef = std::any_cast<const U&>(m_object);
                    return static_cast<const T*>(sptrRef.get());
                }
            }
            else return nullptr;
        } 
        catch (const std::bad_any_cast&) {
            return nullptr;
        }
    }


    template <class T, traits::enable_if_not_std_wrapper<T>>
    inline std::optional<rtl::view<T>> RObject::view() const
    {
        traits::validate_view<T>();
        using _T = traits::raw_t<T>;
        const std::size_t asTypeId = detail::TypeId<_T>::get();
        if (asTypeId == m_objectId.m_typeId)
        {
            const _T* valueRef = extractRefrence<_T>();
            if (valueRef != nullptr) {
                if constexpr (traits::is_raw_ptr_v<T>) {
                    return std::optional<rtl::view<T>>(std::move(valueRef));
                }
                else {
                    return std::optional<rtl::view<T>>(*valueRef);
                }
            }
        }
        else {
            const std::size_t qualifiedId = detail::TypeId<T>::get();
            const std::size_t index = getConverterIndex(qualifiedId);
            if (index != index_none) {
                return performConversion<T>(index);
            }
        }
        return std::nullopt;
    }
}