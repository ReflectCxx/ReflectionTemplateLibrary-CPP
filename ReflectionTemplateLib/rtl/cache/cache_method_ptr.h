/*************************************************************************
 *                                                                       *
 *  Reflection Template Library (RTL) - Modern C++ Reflection Framework  *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP          *
 *                                                                       *
 *  Copyright (c) 2025 Neeraj Singh <reflectcxx@outlook.com>             *
 *  SPDX-License-Identifier: MIT                                         *
 *                                                                       *
 *************************************************************************/


#pragma once

#include <list>

#include "method_ptr.h"

namespace rtl::cache
{
    template<class record_t, class return_t, class ...signature_ts>
    struct method_ptr
    {
        using functor_t = dispatch::method_ptr<record_t, return_t, signature_ts...>;

        static const method_ptr& instance()
        {
            static const method_ptr instance_;
            return instance_;
        }

        const dispatch::functor* push(return_t(record_t::* fptr)(signature_ts...), std::size_t lambda_index) const
        {
            m_cache.emplace_back(std::make_pair(fptr, lambda_index));
            return &(m_cache.back().first);
        }

        std::pair<const dispatch::functor*, std::size_t> find(return_t(record_t::* fptr)(signature_ts...)) const
        {
            for (auto& itr : m_cache)
            {
                const auto& functor = itr.first;
                if (functor.is_same(fptr)) {
                    return { &itr.first, itr.second };
                }
            }
            return { nullptr, rtl::index_none };
        }

        method_ptr(method_ptr&&) = delete;
        method_ptr(const method_ptr&) = delete;
        method_ptr& operator=(method_ptr&&) = delete;
        method_ptr& operator=(const method_ptr&) = delete;

    private:

        // No reallocation occurs; original objects stay intact
        mutable std::list<std::pair<const functor_t, std::size_t>> m_cache;

        method_ptr() = default;
    };
}