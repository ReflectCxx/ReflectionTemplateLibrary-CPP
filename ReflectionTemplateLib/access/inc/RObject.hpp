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
    inline const bool RObject::isa() const
    {
        return (m_typeId == rtl::detail::TypeId<T>::get());
    }


    template <class T>
    inline std::optional<std::reference_wrapper<T>> RObject::get() noexcept
    {
        return isa<T>() ? std::optional<std::reference_wrapper<T>>(std::any_cast<T&>(m_object)) : std::nullopt;
    }


    template<class _asType>
    inline const bool RObject::canBeClonedAs() const
    {
        const auto& typeId = rtl::detail::TypeId<_asType>::get();
        return (getConverterIndex(typeId) != -1);
    }


    template<alloc _allocOn, std::size_t N>
    inline RObject RObject::create(const char(&pStr)[N])
    {
        return create<_allocOn>(std::string(pStr));
    }


    template <alloc _allocOn, class T>
    inline RObject RObject::create(T&& pVal)
    {
        const auto& typeId = rtl::detail::TypeId<T>::get();
        const auto& typeStr = rtl::detail::TypeId<T>::toString();
        const auto& conversions = rtl::detail::RObjectConverter<T>::getConversions();

        return std::move(RObject(std::any(pVal), typeId, typeStr, _allocOn, conversions));
    }


    template<class _asType>
    inline std::optional<RObject> RObject::clone() const
    {
        const auto& toTypeId = rtl::detail::TypeId<_asType>::get();

        if (toTypeId == m_typeId) 
        {
            const auto& objValue = as<_asType>();
            if (m_allocatedOn == alloc::Heap) {
                return std::optional<RObject>(RObject::create<alloc::Heap>(objValue));
            }
            else {
                return std::optional<RObject>(RObject::create<alloc::Stack>(objValue));
            }
        }

        const auto& index = getConverterIndex(toTypeId);
        if (index != -1) {
            return std::optional<RObject>(std::move(m_converters[index].second(*this)));
        }

        return std::nullopt;
    }
}