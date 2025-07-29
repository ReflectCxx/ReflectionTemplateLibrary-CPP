#pragma once

#include <atomic>
#include <functional>
#include <memory>

#include "RObject.h"

namespace rtl::detail
{
    class RObjectBuilder
    {
        static std::atomic<std::size_t> m_reflectedInstanceCount;

    public:

        RObjectBuilder() = delete;
        RObjectBuilder(const RObjectBuilder&) = delete;

        static const std::size_t reflectedInstanceCount();

        template<class T, traits::enable_if_std_wrapper<T> = 0>
        static access::RObject build(T&& pVal, const std::function<void()>& pDeleter, rtl::alloc pAllocOn);

        template<class T, std::size_t N>
        static access::RObject build(T(&pArr)[N], const std::function<void()>& pDeleter, rtl::alloc pAllocOn);

        template<class T, traits::enable_if_not_std_wrapper<T> = 0>
        static access::RObject build(T&& pVal, const std::function<void()>& pDeleter, rtl::alloc pAllocOn);
    };
}


namespace rtl
{
    template <class T>
    inline access::RObject reflect(T&& pVal)
    {
        return detail::RObjectBuilder::build(std::forward<T>(pVal), nullptr, alloc::None);
    }

    inline const std::size_t getReflectedHeapInstanceCount() 
    {
        return detail::RObjectBuilder::reflectedInstanceCount();
    }
}