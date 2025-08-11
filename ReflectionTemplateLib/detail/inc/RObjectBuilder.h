#pragma once

#include "rtl_traits.h"

namespace rtl::access {
    class RObject;
}

namespace rtl::detail
{
    class RObjectBuilder
    {
        using Cloner = std::function<access::RObject(error&, const access::RObject&, rtl::alloc)>;

        template <class T>
        static Cloner buildCloner();

    public:

        RObjectBuilder() = delete;
        RObjectBuilder(const RObjectBuilder&) = delete;

        static const std::size_t reflectedInstanceCount();

        template <class T, rtl::alloc _allocOn>
        static access::RObject build(T&& pVal, const bool pIsConstCastSafe);
    };
}


namespace rtl
{
    inline const std::size_t getReflectedHeapInstanceCount()
    {
        return detail::RObjectBuilder::reflectedInstanceCount();
    }

    template <class T>
    inline access::RObject reflect(T&& pVal)
    {
        return detail::RObjectBuilder::build<T, alloc::Stack>(std::forward<T>(pVal), false);
    }

    template<class T, std::size_t N>
    inline access::RObject reflect(T(&pArr)[N])
    {
        if constexpr (std::is_same_v<traits::raw_t<T>, char>) {
            return detail::RObjectBuilder::build<std::string_view, alloc::Stack>(std::string_view(pArr, N - 1), false);
        }
        else {
            return detail::RObjectBuilder::build<std::vector<T>, alloc::Stack>(std::vector(pArr, pArr + N), false);
        }
    }
}