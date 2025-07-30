#pragma once

#include <optional>
#include <iostream>
#include <cassert>

#include "RObject.h"
#include "ReflectCast.h"

namespace rtl::traits
{
    template<class T>
    void validate_view()
    {
        using _T = traits::remove_const_n_ref_n_ptr<T>;
        constexpr bool isReference = std::is_reference_v<T>;
        constexpr bool isWrapperPtr = (std::is_pointer_v<T> && traits::std_wrapper<_T>::type != Wrapper::None);
        constexpr bool isNonConstPtr = (std::is_pointer_v<T> && !std::is_const_v<std::remove_pointer_t<T>>);

        static_assert(!isReference, "explicit reference views are not supported.");
        static_assert(!isWrapperPtr, "viewing standard wrappers (like std::optional or smart pointers) as raw pointers, not supported.");
        static_assert(!isNonConstPtr, "non-const pointers not supported, Only read-only (const) pointer views are supported.");
    }
}


namespace rtl::access
{
    template<rtl::alloc _allocOn>
    inline std::pair<error, RObject> RObject::clone() const
    {
        return { error::None, RObject(*this) };
    }

    template<class T>
    inline const T& RObject::as(bool pGetFromWrapper/* = false*/) const
    {
        if (pGetFromWrapper) {
            return std::any_cast<const T&>(m_wrapper);
        }
        if (m_objectId.m_isPointer == rtl::IsPointer::Yes) {

            using _ptrT = std::add_pointer_t<std::add_const_t<T>>;
            return *(std::any_cast<_ptrT>(m_object));
        }
        return std::any_cast<const T&>(m_object);
    }


    template<class T>
    inline bool RObject::canViewAs() const
    {
        traits::validate_view<T>();

        using _T = traits::remove_const_n_ref_n_ptr<T>;
        if constexpr (std::is_pointer_v<T> && std::is_const_v<std::remove_pointer_t<T>>)
        {
            if (m_objectId.m_ptrTypeId == rtl::detail::TypeId<_T*>::get()) {
                return true;
            }
        }
        else if constexpr (traits::std_wrapper<_T>::type != Wrapper::None)
        {
            if (m_objectId.m_wrapperTypeId == traits::std_wrapper<_T>::id()) {
                return true;
            }
        }

        const auto& typeId = rtl::detail::TypeId<T>::get();
        return (typeId == m_objectId.m_typeId || getConverterIndex(typeId) != rtl::index_none);
    }


    template <class _asType>
    inline std::optional<rtl::view<_asType>> RObject::view() const
    {
        traits::validate_view<_asType>();

        std::size_t toTypeId = rtl::detail::TypeId<_asType>::get();
        if (toTypeId == m_objectId.m_typeId) {
            const auto& viewRef = as<_asType>();
            return std::optional<rtl::view<_asType>>(std::in_place, viewRef);
        }

        using _T = traits::remove_const_n_reference<_asType>;
        if constexpr (std::is_pointer_v<_T>)
        {
            using T = traits::remove_const_n_ref_n_ptr<_asType>;
            std::size_t typePtrId = rtl::detail::TypeId<T*>::get();
            if (typePtrId == m_objectId.m_ptrTypeId) {
                auto& viewRef = as<T>();
                return std::optional<rtl::view<const T*>>(&viewRef);
            }
        }
        else if constexpr (traits::std_wrapper<_T>::type != Wrapper::None)
        {
            if (traits::std_wrapper<_T>::id() == m_objectId.m_wrapperTypeId) {
                const _asType& viewRef = as<_asType>(true);
                return std::optional<rtl::view<_asType>>(viewRef);
            }
        }

        std::size_t index = getConverterIndex(toTypeId);
        if (index != rtl::index_none)
        {
            rtl::ConversionKind conversionKind = rtl::ConversionKind::NotDefined;
            const std::any& viewObj = m_objectId.m_converters[index].second(m_object, m_objectId.m_isPointer, conversionKind);
            if (viewObj.has_value())  //if true, 'conversionKind' can only be 'rtl::Converted::ByRef/ByValue'
            {
                const _asType& viewRef = std::any_cast<const _asType&>(viewObj);
                if (conversionKind == rtl::ConversionKind::ByRef) {
                    return std::optional<rtl::view<_asType>>(std::in_place, viewRef);
                }
                else /*if (converted == rtl::Converted::ByValue)*/ {
                    return std::optional<rtl::view<_asType>>(std::in_place, _asType(viewRef));
                }
            }
            else {
                //TODO: handle rtl::Converted::NoDefined/BadAnyCast
            }
        }
        return std::nullopt;
    }
}


namespace rtl::access
{
    template <class T>
    inline RObject RObject::create(T&& pVal, std::shared_ptr<void>&& pDeleter, rtl::alloc pAllocOn)
    {
        using _T = traits::remove_const_n_ref_n_ptr<T>;
        using _isPointer = std::is_pointer<traits::remove_const_n_reference<T>>;

        const std::size_t typeId = rtl::detail::TypeId<_T>::get();
        const std::size_t typePtrId = rtl::detail::TypeId<_T*>::get();
        const std::size_t wrapperId = detail::TypeId<>::None;
        const auto& typeStr = rtl::detail::TypeId<_T>::toString();
        const auto& conversions = rtl::detail::ReflectCast<_T>::getConversions();
        const auto isPointer = (_isPointer::value ? IsPointer::Yes : IsPointer::No);
        const auto& robjId = detail::RObjectId(pAllocOn, isPointer, typeId, typePtrId, wrapperId, typeStr, conversions);

        if constexpr (_isPointer::value) {
            return RObject(std::any(static_cast<const _T*>(pVal)), std::any(), std::move(pDeleter), robjId);
        }
        else {
            static_assert(std::is_copy_constructible_v<_T>, "T must be copy-constructible (std::any requires this).");
            return RObject(std::any(std::forward<T>(pVal)), std::any(), std::move(pDeleter), robjId);
        }
    }


    template<class W>
    inline RObject RObject::create(W&& pWrapper, alloc pAllocOn)
    {
        using _W = traits::std_wrapper<traits::remove_const_n_ref_n_ptr<W>>;
        using _T = _W::baseT;

        const std::size_t typeId = detail::TypeId<_T>::get();
        const std::size_t typePtrId = detail::TypeId<_T*>::get();
        const std::size_t wrapperId = _W::id();
        const auto& typeStr = detail::TypeId<_T>::toString();
        const auto& conversions = detail::ReflectCast<_T>::getConversions();
        const auto& robjId = detail::RObjectId(pAllocOn, rtl::IsPointer::Yes, typeId, typePtrId, wrapperId, typeStr, conversions);

        if constexpr (_W::type == Wrapper::Unique) {
            auto rawPtr = static_cast<const _T*>(pWrapper.get());
            return RObject(std::any(rawPtr), std::any(std::unique_ptr<_T>(std::move(pWrapper))), nullptr, robjId);
        }
        else if constexpr (_W::type == Wrapper::Weak || _W::type == Wrapper::Shared) {
            auto rawPtr = static_cast<const _T*>(pWrapper.get());
            return RObject(std::any(rawPtr), std::any(std::forward<W>(pWrapper)), nullptr, robjId);
        }
        else {
            auto obj = pWrapper.value();
            return RObject(std::any(obj), std::any(std::forward<W>(pWrapper)), nullptr, robjId);
        }
    }
}