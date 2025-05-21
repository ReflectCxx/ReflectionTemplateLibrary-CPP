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
        return RObject(std::any(std::forward<T>(pVal)), typeId, typeStr, _allocOn, conversions);
    }


    template <alloc _allocOn, class T>
    inline RObject RObject::reflect(T&& pVal)
    {
        if constexpr (is_string_like<std::decay_t<T>>::value) {
            return create<_allocOn>(std::string(pVal));
        }
        else {
            return create<_allocOn>(pVal);
        }
    }


    template<class _asType>
    const std::size_t RObject::getTypeId()
    {
        if constexpr (std::is_same_v<_asType, char>) 
        {
            // Special case: char → const char* view if underlying type is std::string
            if (m_typeId == rtl::detail::TypeId<std::string>::get()) {
                return rtl::detail::TypeId<const char*>::get();
            }
            else {
                return rtl::detail::TypeId<_asType>::get();
            }
        }
        else {
            return rtl::detail::TypeId<_asType>::get();
        }
    }


    template <class _asType>
    inline const _asType* RObject::view()
    {
        static_assert(!std::is_const_v<_asType>, "RObject::view<T>() requires T to be a non-const, non-pointer, non-reference type.");
        static_assert(!std::is_pointer_v<_asType>, "RObject::view<T>() requires T to be a non-pointer type. Use T, not T*.");
        static_assert(!std::is_reference_v<_asType>, "RObject::view<T>() requires T to be a non-reference type. Use T, not T& or T&&.");

        const auto& toTypeId = getTypeId<_asType>();
        if (toTypeId == m_typeId) {
            return &as<const _asType>();
        }

        const auto& index = getConverterIndex(toTypeId);
        if (index != -1) {
            const auto& converted = m_converters[index].second(m_object);
            const _asType* viewPtr = std::any_cast<const _asType*>(converted);
            return viewPtr;
        }
        return nullptr;
    }
}