#pragma once

#include <optional>

#include "RObject.h"
#include "RObjectConverters.hpp"

namespace rtl::access {

    template<class T>
    inline const T& RObject::as() const
    {
        return std::any_cast<const T&>(m_object);
    }


    inline const bool RObject::isReflecting() const
    {
        return (m_object.has_value());
    }


    template<class T>
    inline const bool RObject::isReflecting() const
    {
        const auto& typeId = rtl::detail::TypeId<T>::get();
        return (typeId == m_typeId || getConverterIndex(typeId) != -1);
    }


    template <class T>
    inline RObject RObject::reflect(T&& pVal)
    {
        if constexpr (is_string_like<std::decay_t<T>>::value) {
            return create(std::string(pVal));
        }
        else {
            return create(pVal);
        }
    }


    template <class T>
    inline RObject RObject::create(T&& pVal)
    {
        using _type = remove_const_and_reference<T>;
        const auto& typeId = rtl::detail::TypeId<_type>::get();
        const auto& typeStr = rtl::detail::TypeId<_type>::toString();
        const auto& conversions = rtl::detail::RObjectConverter<_type>::getConversions();
        return RObject(std::any(std::forward<T>(pVal)), typeId, typeStr, conversions);
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
        if (index != -1) {
            const std::any& converted = m_converters[index].second(m_object);
            if (converted.has_value()) {
                const auto& viewCopy = std::any_cast<const _asType&>(converted);
                return std::optional<rtl::cref_view<_asType>>(std::in_place, _asType(viewCopy));

            }
        }
        return std::nullopt;
    }
}