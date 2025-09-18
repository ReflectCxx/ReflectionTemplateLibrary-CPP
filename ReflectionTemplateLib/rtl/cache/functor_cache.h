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
    template<class ...signature_ts>
    struct functor_cache
    {
        using functor_t = functor<signature_ts...>;

        static const functor_cache& instance()
        {
            static functor_cache instance_;
            return instance_;
        }

        template<class return_t>
        const functor_hop* push(return_t(*fptr)(signature_ts...), std::size_t lambda_index) const
        {
            using voidfn_t = typename functor<signature_ts...>::voidfn_t;

            auto functor = functor_t(reinterpret_cast<voidfn_t>(fptr), detail::TypeId<return_t>::get());
            m_cache.emplace_back(std::make_pair(functor , lambda_index));
            return &(m_cache.back().first);
        }

        template<class return_t>
        std::pair<const functor_hop*, std::size_t> find(return_t(*fptr)(signature_ts...)) const
        {
            for (auto& itr : m_cache)
            {
                const auto& functor = itr.first;
                if (functor.template is_same<return_t>(fptr)) {
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
        mutable std::list<std::pair<functor_t, std::size_t>> m_cache;

        functor_cache() {}
    };
}