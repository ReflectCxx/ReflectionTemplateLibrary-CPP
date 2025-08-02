#pragma once

#include "rtl_traits.h"

namespace rtl::access {
    class RObject;
}

namespace rtl::detail
{
    struct RObjectBuilder
    {
        RObjectBuilder() = delete;
        RObjectBuilder(const RObjectBuilder&) = delete;

        static const std::size_t reflectedInstanceCount();

        template<class T, rtl::alloc _allocOn = alloc::None, traits::enable_if_std_wrapper<T> = 0>
        static access::RObject build(T&& pVal);

        template<class T, rtl::alloc _allocOn = alloc::None, traits::enable_if_not_std_wrapper<T> = 0>
        static access::RObject build(T&& pVal);
    };
}


namespace rtl
{
    template <class T>
    inline access::RObject reflect(T&& pVal)
    {
        return detail::RObjectBuilder::build(std::forward<T>(pVal));
    }

    template<class T, std::size_t N>
    inline access::RObject reflect(T(&pArr)[N])
    {
        if constexpr (std::is_same_v<traits::base_t<T>, char>) {
            return detail::RObjectBuilder::build<std::string_view, alloc::None>(std::string_view(pArr, N - 1));
        }
        else {
            return detail::RObjectBuilder::build<std::vector<T>, alloc::None>(std::vector(pArr, pArr + N));
        }
    }

    inline const std::size_t getReflectedHeapInstanceCount() 
    {
        return detail::RObjectBuilder::reflectedInstanceCount();
    }
}