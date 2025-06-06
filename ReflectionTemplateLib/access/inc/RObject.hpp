#pragma once

#include <optional>

#include "RObject.h"
#include "ReflectCast.h"

namespace rtl::access {

    template<class T>
    inline const T& RObject::as() const
    {
        return std::any_cast<const T&>(m_object);
    }


    template<class T>
    inline const bool RObject::canReflectAs() const
    {
        const auto& typeId = rtl::detail::TypeId<T>::get();
        return (typeId == m_typeId || getConverterIndex(typeId) != -1);
    }


    template <class T>
    inline RObject RObject::reflect(T&& pVal)
    {
        if constexpr (is_string_like<std::decay_t<T>>::value) {
            return create(std::string(std::forward<T>(pVal)));
        }
        else {
            return create(std::forward<T>(pVal));
        }
    }


    template <class T>
    inline RObject RObject::create(T&& pVal)
    {
        using _T = remove_const_n_ref_n_ptr<T>;
        const auto& typeId = rtl::detail::TypeId<_T>::get();
        const auto& typeStr = rtl::detail::TypeId<_T>::toString();
        const auto& conversions = rtl::detail::ReflectCast<_T>::getConversions();
        if constexpr (std::is_pointer_v<remove_const_n_reference<T>>) {
            return RObject(std::any(static_cast<const _T*>(pVal)), typeId, typeStr, conversions, rtl::IsPointer::Yes);
        }
        else {
            return RObject(std::any(std::in_place_type<_T>, _T(pVal)), typeId, typeStr, conversions, rtl::IsPointer::No);
        }
    }


    template <class _asType>
    inline std::optional<rtl::cref_view<_asType>> RObject::view() const
    {
        const auto& toTypeId = rtl::detail::TypeId<_asType>::get();
        if (toTypeId == m_typeId) {
            const auto& viewRef = as<_asType>();
            return std::optional<rtl::cref_view<_asType>>(std::in_place, viewRef);
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
                    return std::optional<rtl::cref_view<_asType>>(std::in_place, viewRef);
                }
                else /*if (converted == rtl::Converted::ByValue)*/ {
                    return std::optional<rtl::cref_view<_asType>>(std::in_place, _asType(viewRef));
                }
            }
            else {
                //handle rtl::Converted::NoDefined/BadAnyCast
            }
        }
        return std::nullopt;
    }
}