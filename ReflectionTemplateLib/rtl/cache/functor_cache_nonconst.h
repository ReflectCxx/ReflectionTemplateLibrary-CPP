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

#include <deque>

#include "functor_nonconst.h"

namespace rtl::detail
{
    template<class record_t, class return_t, class ...signature_ts>
    struct functor_cache_nonconst
    {
        using fptr_t = return_t(record_t::*)(signature_ts...);
        using functor_t = typename dispatch::functor_nonconst<record_t, return_t, signature_ts...>;
        
        static functor_cache_nonconst& get()
        {
            static functor_cache_nonconst instance;
            return instance;
        }

        const dispatch::functor_hop* push(const functor_t& functor, std::size_t lambda_index)
        {
            m_cache.emplace_back(std::make_pair(functor, lambda_index));
            return &(m_cache.back().first);
        }

        std::size_t find(fptr_t fptr)
        {
            for (auto& itr : m_cache)
            {
                const auto& functor = itr.first;
                if (fptr == functor.get()) {
                    return itr.second;
                }
            }
            return rtl::index_none;
        }

        functor_cache_nonconst(functor_cache_nonconst&&) = delete;
        functor_cache_nonconst(const functor_cache_nonconst&) = delete;
        functor_cache_nonconst& operator=(functor_cache_nonconst&&) = delete;
        functor_cache_nonconst& operator=(const functor_cache_nonconst&) = delete;

    private:

        // No reallocation occurs; original objects stay intact
        std::deque<std::pair<const functor_t, std::size_t>> m_cache;
        functor_cache_nonconst() {}
    };
}