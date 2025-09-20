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

#include "const_method_ptr.h"

namespace rtl::cache 
{
    template<class record_t, class ...signature_ts>
    struct const_method_ptr
    {
        using functor_t = dispatch::const_method_ptr<record_t, signature_ts...>;

        static const const_method_ptr& instance()
        {
            static const_method_ptr instance_;
            return instance_;
        }

        template<class return_t>
        const dispatch::functor* push(return_t(record_t::* fptr)(signature_ts...) const, std::size_t lambda_index) const
        {
            using voidfn_t = typename dispatch::const_method_ptr<record_t, signature_ts...>::voidfn_t;
            auto functor = functor_t(reinterpret_cast<voidfn_t>(fptr), detail::TypeId<return_t>::get());
            m_cache.emplace_back(std::make_pair(functor, lambda_index));
            return &(m_cache.back().first);

        }

        template<class return_t>
        std::pair<const dispatch::functor*, std::size_t> find(return_t(record_t::* fptr)(signature_ts...) const) const
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

        const_method_ptr(const_method_ptr&&) = delete;
        const_method_ptr(const const_method_ptr&) = delete;
        const_method_ptr& operator=(const_method_ptr&&) = delete;
        const_method_ptr& operator=(const const_method_ptr&) = delete;

    private:

        // No reallocation occurs; original objects stay intact
        mutable std::list<std::pair<const functor_t, std::size_t>> m_cache;

        const_method_ptr() = default;
    };
}