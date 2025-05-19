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
    inline const T& RObject::as() const
    {
        return std::any_cast<const T&>(m_object);
    }


    template<class T>
    inline const bool RObject::isReflectingType()
    {
        return (m_typeId == rtl::detail::TypeId<T>::get());
    }


    template <class T>
    inline std::optional<T> RObject::getAs()
    {
        return isReflectingType<T>() ? std::optional<T>(std::any_cast<T>(m_object)) : std::nullopt;
    }


    template <class _asType>
    inline std::optional<std::reference_wrapper<_asType>> RObject::viewAs()
    {
        return isReflectingType<_asType>() ? std::optional<std::reference_wrapper<_asType>>(std::any_cast<_asType&>(m_object)) : std::nullopt;
    }


    template<class _asType>
    inline const bool RObject::canBeClonedAs()
    {
        const auto& typeId = rtl::detail::TypeId<_asType>::get();
        return (getConverterIndex(typeId) != -1);
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


    template<class _asType>
    inline std::optional<RObject> RObject::cloneAs()
    {
        const auto& toTypeId = rtl::detail::TypeId<_asType>::get();

        if (toTypeId == m_typeId) 
        {
            const auto& objValue = as<_asType>();
            if (m_allocatedOn == alloc::Heap) {
                return std::optional<RObject>(RObject::reflect<alloc::Heap>(objValue));
            }
            else {
                return std::optional<RObject>(RObject::reflect<alloc::Stack>(objValue));
            }
        }

        const auto& index = getConverterIndex(toTypeId);
        if (index != -1) {
            return std::optional<RObject>(std::move(m_converters[index].second(*this)));
        }
        return std::nullopt;
    }
}