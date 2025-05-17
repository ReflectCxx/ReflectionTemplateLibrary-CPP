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
    inline const bool RObject::isa()
    {
        return (m_typeId == rtl::detail::TypeId<T>::get());
    }


    template <class T>
    inline std::optional<std::reference_wrapper<T>> RObject::ref() noexcept
    {
        return isa<T>() ? std::any_cast<T&>(m_object) : std::nullopt;
    }


    template <alloc _allocOn, class T>
    inline static RObject RObject::create(T&& pVal)
    {
        const auto& typeId = rtl::detail::TypeId<T>::get();
        const auto& typeStr = typeid(T).name();
        return std::move(RObject(std::any(pVal), typeId, typeStr, _allocOn));
    }
}