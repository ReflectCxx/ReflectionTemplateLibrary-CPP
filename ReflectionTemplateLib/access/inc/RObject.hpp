#pragma once

#include <optional>
#include <iostream>

#include "RObject.h"
#include "ReflectCast.h"

namespace rtl::access {

    template<class T>
    inline const T& RObject::as() const
    {
        if (m_isPointer == rtl::IsPointer::Yes) {
            return *(std::any_cast<const T*>(m_object));
        }
        else {
            return std::any_cast<const T&>(m_object);
        }
    }


    template<class T>
    inline const bool RObject::canViewAs() const
    {
        static_assert(!std::is_reference_v<T>, "reference views are not supported.");
        static_assert(!std::is_pointer_v<T> || std::is_const_v<std::remove_pointer_t<T>>,
                      "non-const pointers not supported, Only read-only (const) pointer views are supported.");

        if constexpr (std::is_pointer_v<T> && std::is_const_v<std::remove_pointer_t<T>>)
        {
            using _T = remove_const_n_ref_n_ptr<T>;
            const auto& typePtrId = rtl::detail::TypeId<_T*>::get();
            if (typePtrId == m_typePtrId) {
                return true;
            }
        }
        const auto& typeId = rtl::detail::TypeId<T>::get();
        return (typeId == m_typeId || getConverterIndex(typeId) != -1);
    }


    template <class T>
    inline RObject RObject::create(T&& pVal, std::shared_ptr<void>&& pDeleter, const rtl::TypeQ& pTypeQ, const rtl::alloc& pAllocOn)
    {
        using _T = remove_const_n_ref_n_ptr<T>;
        const auto& typeId = rtl::detail::TypeId<_T>::get();
        const auto& typePtrId = rtl::detail::TypeId<_T*>::get();
        const auto& typeStr = rtl::detail::TypeId<_T>::toString();
        const auto& conversions = rtl::detail::ReflectCast<_T>::getConversions();
        if constexpr (std::is_pointer_v<remove_const_n_reference<T>>) {
            return RObject(std::any(static_cast<const _T*>(pVal)), typeId, typePtrId, typeStr,
                           pTypeQ, rtl::IsPointer::Yes, pAllocOn, std::move(pDeleter), conversions);
        }
        else {
            return RObject(std::any(std::forward<T>(pVal)), typeId, typePtrId, typeStr,
                           pTypeQ, rtl::IsPointer::No, pAllocOn, std::move(pDeleter), conversions);
        }
    }


    template <class _asType>
    inline std::optional<rtl::view<_asType>> RObject::view() const
    {
        static_assert(!std::is_reference_v<_asType>, "reference views are not supported.");
        static_assert(!std::is_pointer_v<_asType> || std::is_const_v<std::remove_pointer_t<_asType>>,
                      "non-const pointers not supported, Only read-only (const) pointer views are supported.");

        const auto& toTypeId = rtl::detail::TypeId<_asType>::get();
        if (toTypeId == m_typeId) {
            const auto& viewRef = as<_asType>();
            return std::optional<rtl::view<_asType>>(std::in_place, viewRef);
        }

        if constexpr (std::is_pointer_v<remove_const_n_reference<_asType>>)
        {
            using T = remove_const_n_ref_n_ptr<_asType>;
            const auto& typePtrId = rtl::detail::TypeId<T*>::get();
            if (typePtrId == m_typePtrId) {
                auto& viewRef = as<T>();
                return std::optional<rtl::view<const T*>>(&viewRef);
            }
        }

        const auto& index = getConverterIndex(toTypeId);
        if (index != -1) 
        {
            rtl::ConversionKind conversionKind = rtl::ConversionKind::NotDefined;
            const std::any& viewObj = m_converters[index].second(m_object, m_isPointer, conversionKind);
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