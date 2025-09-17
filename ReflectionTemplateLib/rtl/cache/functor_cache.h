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

#include "functor.h"

namespace rtl::dispatch
{
    template<class return_t, class ...signature_ts>
    struct functor_cache
    {
        using fptr_t = return_t(*)(signature_ts...);
        using functor_t = functor<return_t, signature_ts...>;

        static functor_cache& get()
        {
            static functor_cache instance;
            return instance;
        }

        const functor_hop* push(const functor_t& functor, std::size_t lambda_index)
        {
            m_cache.emplace_back(std::make_pair(functor, lambda_index));
            return &(m_cache.back().first);
        }

        std::pair<const functor_hop*, std::size_t> find(fptr_t fptr)
        {
            for (auto& itr : m_cache)
            {
                const auto& functor = itr.first;
                if (fptr == functor.get()) {
                    return { &itr.first, itr.second };
                }
            }
            return { nullptr, rtl::index_none };
        }

        functor_cache(functor_cache&&) = delete;
        functor_cache(const functor_cache&) = delete;
        functor_cache& operator=(functor_cache&&) = delete;
        functor_cache& operator=(const functor_cache&) = delete;

    private:

        // No reallocation occurs; original objects stay intact
        std::list<std::pair<functor_t, std::size_t>> m_cache;

        functor_cache() {}
    };
}