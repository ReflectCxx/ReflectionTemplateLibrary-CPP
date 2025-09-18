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

#include "functor_nonconst.h"

namespace rtl::dispatch
{
    template<class record_t, class ...signature_ts>
    struct functor_cache_nonconst
    {
        using functor_t = functor_nonconst<record_t, signature_ts...>;

        static const functor_cache_nonconst& instance()
        {
            static const functor_cache_nonconst instance_;
            return instance_;
        }

        template<class return_t>
        const functor_hop* push(return_t(record_t::* fptr)(signature_ts...), std::size_t lambda_index) const
        {
            using voidfn_t = typename functor_nonconst<record_t, signature_ts...>::voidfn_t;
            auto functor = functor_t(reinterpret_cast<voidfn_t>(fptr), detail::TypeId<return_t>::get());
            m_cache.emplace_back(std::make_pair(functor, lambda_index));
            return &(m_cache.back().first);
        }

        template<class return_t>
        std::pair<const functor_hop*, std::size_t> find(return_t(record_t::* fptr)(signature_ts...)) const
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

        functor_cache_nonconst(functor_cache_nonconst&&) = delete;
        functor_cache_nonconst(const functor_cache_nonconst&) = delete;
        functor_cache_nonconst& operator=(functor_cache_nonconst&&) = delete;
        functor_cache_nonconst& operator=(const functor_cache_nonconst&) = delete;

    private:

        // No reallocation occurs; original objects stay intact
        mutable std::list<std::pair<const functor_t, std::size_t>> m_cache;

        functor_cache_nonconst() {}
    };
}