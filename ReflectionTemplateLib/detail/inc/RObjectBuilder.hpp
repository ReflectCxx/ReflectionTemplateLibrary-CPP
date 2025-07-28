#pragma once

#include <cassert>

#include "RObjectBuilder.h"
#include "RObject.hpp"
#include "rtl_traits.h"

namespace rtl::detail
{
    template<class T>
    inline access::RObject RObjectBuilder::build(std::shared_ptr<T>&& pVal, const std::function<void()>& pDeleter, rtl::alloc pAllocOn)
    {
        return access::RObject::create(std::forward<std::shared_ptr<T>>(pVal), pAllocOn);
    }


    template<class T>
    inline access::RObject RObjectBuilder::build(std::unique_ptr<T>&& pVal, const std::function<void()>& pDeleter, rtl::alloc pAllocOn)
    {
        return access::RObject::create(std::forward<std::unique_ptr<T>>(pVal), pAllocOn);
    }


    template<class T, std::size_t N>
    inline access::RObject RObjectBuilder::build(T(&pArr)[N], const std::function<void()>& pDeleter, alloc pAllocOn)
    {
        if constexpr (std::is_same_v<traits::base_t<T>, char>) 
        {
            return build(std::string_view(pArr, N - 1), nullptr, rtl::alloc::None);
        }
        else
        {
            return build(std::vector(pArr, pArr + N), nullptr, rtl::alloc::None);
        }
    }


    template<class T>
    inline access::RObject RObjectBuilder::build(T&& pVal, const std::function<void()>& pDeleter, alloc pAllocOn)
    {
        if (std::is_pointer_v<std::remove_reference_t<T>> && pDeleter && pAllocOn == alloc::Heap)
        {
            m_reflectedInstanceCount.fetch_add(1);
            std::shared_ptr<void>&& deleter = std::shared_ptr<void>(static_cast<void*>(&m_reflectedInstanceCount),
            [=] (void*) {
                pDeleter();
                m_reflectedInstanceCount.fetch_sub(1);
                assert(m_reflectedInstanceCount >= 0 && "instance count can't be less than zero. memory leak alert!");
            });

            return access::RObject::create(std::forward<T>(pVal), std::move(deleter), pAllocOn);
        }
        else
        {
            if constexpr (std::is_bounded_array_v<std::remove_reference_t<T>>) {
                return access::RObject::create(std::forward<T>(pVal), std::shared_ptr<void>(), pAllocOn);
            }
            else {
                return access::RObject::create(std::forward<T>(pVal), std::shared_ptr<void>(), pAllocOn);
            }
        }
    }
}