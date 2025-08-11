#pragma once

#include <optional>
#include <iostream>
#include <cassert>

#include "RObject.h"
#include "ReflectCast.h"
#include "RObjectBuilder.h"

namespace rtl::access
{
    inline access::RObject::~RObject()
    {
        if (m_objectId.m_allocatedOn == alloc::Heap) {
            RObject::m_rtlOwnedHeapAllocCount.fetch_sub(1);
        }
    }

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


    template<class T, traits::enable_if_not_std_wrapper<T>>
    inline T* RObject::extract() const
    {
        switch (m_objectId.m_containsAs)
        {
        case detail::Contains::Pointer: {
            return (std::any_cast<T*>(m_object));
        }
        case detail::Contains::Wrapper: {
            return extractFromWrapper<T>();
        }
        case detail::Contains::Value: {
            using U = traits::raw_t<T>;
            const U& valueRef = std::any_cast<const U&>(m_object);
            return static_cast<T*>(&valueRef);
        }
        }
        return nullptr;  //dead-code, eliminates compiler warning.
    }


    template<class T, traits::enable_if_std_wrapper<T>>
    inline T* RObject::extract() const
    {
        using U = traits::raw_t<T>;
        using _T = traits::std_wrapper<U>::value_type;
        // std::any can't hold std::unique_ptr, its stored as shared_ptr but uniqueness is maintained.
        if (m_objectId.m_wrapperType == detail::Wrapper::Shared ||
            m_objectId.m_wrapperType == detail::Wrapper::Unique)
        {
            if (m_objectId.m_isWrappingConst) {
                using U = std::shared_ptr<const _T>;
                const std::shared_ptr<const _T>& sptrRef = std::any_cast<const U&>(m_object);
                return static_cast<T*>(&sptrRef);
            }
            else {
                using U = std::shared_ptr<_T>;
                const std::shared_ptr<_T>& sptrRef = std::any_cast<const U&>(m_object);
                return static_cast<T*>(&sptrRef);
            }
        }
    }


    template<class T>
    inline T* access::RObject::extractFromWrapper() const
    {
        using _T = traits::raw_t<T>;
        // std::any stores unique_ptr as shared_ptr internally, but still preserves sole ownership.
        if (m_objectId.m_wrapperType == detail::Wrapper::Shared ||
            m_objectId.m_wrapperType == detail::Wrapper::Unique)
        {
            if (m_objectId.m_isWrappingConst) {
                using U = std::shared_ptr<const _T>;
                const auto& sptrRef = std::any_cast<const U&>(m_object);
                return static_cast<T*>(sptrRef.get());
            }
            else {
                using U = std::shared_ptr<_T>;
                const auto& sptrRef = std::any_cast<const U&>(m_object);
                return static_cast<T*>(sptrRef.get());
            }
        }
        return nullptr;  //dead-code, eliminates compiler warning.
    }


    template <class T, traits::enable_if_raw_pointer<T>>
    std::optional<rtl::view<T>> RObject::view() const
    {
        traits::validate_view<T>();
        using _T = traits::raw_t<T>;

        if (detail::TypeId<_T>::get() == m_objectId.m_typeId)
        {
            const _T& valueRef = *extract<const _T>();
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
            using _T = traits::raw_t<T>;
            const _T& valueRef = *extract<const _T>();
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

    template <class T, traits::enable_if_std_wrapper<T>>
    std::optional<rtl::view<T>> RObject::view() const
    {
        traits::validate_view<T>();
        const detail::Wrapper wrap = m_objectId.m_wrapperType;
        if (wrap == detail::Wrapper::Shared || wrap == detail::Wrapper::Unique)
        {
            if (detail::TypeId<T>::get() == m_objectId.m_wrapperTypeId)
            {
                using W = traits::std_wrapper<traits::raw_t<T>>;
                if constexpr (W::type == detail::Wrapper::Unique) {
                    // std::any can't hold std::unique_ptr, its stored as shared_ptr but uniqueness is maintained.
                    using _T = W::value_type;
                    if (m_objectId.m_isWrappingConst)
                    {
                        //using U = std::shared_ptr<const _T>;
                        //U& sptrRef = *(const_cast<U*>(extract<const U>()));
                        //if (sptrRef.use_count() == 1) {
                        //    const _T* rawPtr = sptrRef.get();
                        //    sptrRef.reset();
                        //    std::unique_ptr<const _T> uptr(rawPtr);
                        //    return std::optional<rtl::view<T>>(std::move(uptr));   //No Copy, init by reference.
                        //}
                        //else {
                        //    assert(false && "exception: uniqueness compromised! failed to manage std::unique_ptr as std::shared_ptr");
                        //}
                    }
                    else
                    {
                        //using U = std::shared_ptr<_T>;
                        //const U& sptrRef = *extract<const U>();
                        //if (sptrRef.use_count() == 1) {
                        //    _T* rawPtr = sptrRef.get();
                        //    sptrRef.reset();
                        //    std::unique_ptr<_T> uptr(rawPtr);
                        //    return std::optional<rtl::view<T>>(std::move(uptr));   //No Copy, init by reference.
                        //}
                        //else {
                        //    assert(false && "exception: uniqueness compromised! failed to manage std::unique_ptr as std::shared_ptr");
                        //}
                    }
                }
                else {
                    const T& sptrRef = *extract<const T>();
                    return std::optional<rtl::view<T>>(sptrRef);   //No Copy, init by reference.
                }
            }
        }
        return std::nullopt;
    }
}