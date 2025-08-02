#pragma once

#include "RObjectBuilder.h"
#include "RObject.hpp"

namespace rtl::detail {

    inline const std::size_t RObjectBuilder::reflectedInstanceCount()
    {
        return access::RObject::m_rtlOwnedRObjectInstanceCount;
    }

    template<class T, alloc _allocOn, traits::enable_if_std_wrapper<T>>
    inline access::RObject RObjectBuilder::build(T&& pVal)
    {
        return access::RObject::createWithWrapper(std::forward<T>(pVal));
    }

    template<class T, alloc _allocOn, traits::enable_if_not_std_wrapper<T>>
    inline access::RObject RObjectBuilder::build(T&& pVal)
    {
        if constexpr (std::is_pointer_v<std::remove_reference_t<T>> && _allocOn == alloc::Heap) {
            return access::RObject::create<T, alloc::Heap>(std::forward<T>(pVal));
        }
        else {
            return access::RObject::create<T, _allocOn>(std::forward<T>(pVal));
        }
    }
}