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

namespace rtl::cache
{
    template<class ...signature_ts>
    struct function_ptr
    {
        using functor_t = dispatch::functor<signature_ts...>;

        static const function_ptr& instance()
        {
            static function_ptr instance_;
            return instance_;
        }

        template<class return_t>
        const dispatch::functor_hop* push(return_t(*fptr)(signature_ts...), std::size_t lambda_index) const
        {
            using voidfn_t = typename dispatch::functor<signature_ts...>::voidfn_t;

            auto functor = functor_t(reinterpret_cast<voidfn_t>(fptr), detail::TypeId<return_t>::get());
            m_cache.emplace_back(std::make_pair(functor , lambda_index));
            return &(m_cache.back().first);
        }

        template<class return_t>
        std::pair<const dispatch::functor_hop*, std::size_t> find(return_t(*fptr)(signature_ts...)) const
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

        function_ptr(function_ptr&&) = delete;
        function_ptr(const function_ptr&) = delete;
        function_ptr& operator=(function_ptr&&) = delete;
        function_ptr& operator=(const function_ptr&) = delete;

    private:

        // No reallocation occurs; original objects stay intact
        mutable std::list<std::pair<const functor_t, std::size_t>> m_cache;

        function_ptr() {}
    };
}