#pragma once

#include <optional>

#include "RObject.h"

namespace rtl::access {

    template<class T>
    inline T& RObject::as()
    {
        return std::any_cast<T&>(m_object);
    }


    template<class T>
    inline const bool RObject::isReflecting()
    {
        const auto& typeId = rtl::detail::TypeId<T>::get();
        return (typeId == m_typeId || getConverterIndex(typeId) != -1);
    }


    template <alloc _allocOn, class T>
    inline RObject RObject::create(T&& pVal)
    {
        const auto& typeId = rtl::detail::TypeId<remove_const_and_reference<T>>::get();
        const auto& typeStr = rtl::detail::TypeId<remove_const_and_reference<T>>::toString();
        const auto& conversions = rtl::detail::RObjectConverter<remove_const_and_reference<T>>::getConversions();
        return std::move(RObject(std::any(pVal), typeId, typeStr, _allocOn, conversions));
    }


    template<alloc _allocOn, class T, std::size_t N>
    inline RObject RObject::reflect(const T(&pStr)[N])
    {
        if constexpr (!std::is_same_v<T, char>) {
            static_assert(false, "RObject: cannot reflect a c-style array, except char[]. Use containers.");
        }
        else {
            return create<_allocOn>(std::string(pStr));
        }
    }


    template <class _asType>
    inline std::optional<std::reference_wrapper<const _asType>> RObject::view()
    {
        const auto& toTypeId = rtl::detail::TypeId<_asType>::get();
        if (toTypeId == m_typeId) {
            return std::optional<std::reference_wrapper<const _asType>>(as<const _asType>());
        }

        const auto& index = getConverterIndex(toTypeId);
        if (index != -1) {
            const auto& viewObject = m_converters[index].second(m_object);
            const auto& retView = std::any_cast<const _asType&>(viewObject);
            return std::optional<std::reference_wrapper<const _asType>>(retView);
        }

        return std::nullopt;
    }


    template <alloc _allocOn, class T>
    inline RObject RObject::reflect(T pVal)
    {
        if constexpr (std::is_array_v<T>) 
        {
            if constexpr (!std::is_same_v<std::remove_cv_t<std::remove_extent_t<T>>, char>) {
                static_assert(false, "RObject: cannot reflect a c-style array, except char[]. Use containers.");
            }
            else {
                return create<_allocOn>(std::string(pVal));
            }
        }
        else if constexpr (std::is_same_v<T, const char*>) 
        {
            return create<_allocOn>(std::string(pVal));
        }
        else
        {
            return create<_allocOn>(pVal);
        }
    }
}