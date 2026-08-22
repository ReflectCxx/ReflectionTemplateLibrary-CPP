/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#pragma once

#include <list>
#include <dispatch/method_ptr.hpp>

namespace rtl::cache
{
    template<class record_t, class return_t, class ...signature_t>
    struct method_ptr
    {
        using method_t = dispatch::method_ptr<record_t, return_t, signature_t...>;

        using functor_t = return_t(record_t::*)(signature_t...);

        static const method_ptr& instance()
        {
            static const method_ptr instance_;
            return instance_;
        }

        const dispatch::functor& push(functor_t fptr) const
        {
            m_cache.emplace_back(method_t(fptr));
            method_t& fn = m_cache.back();
            fn.init_lambda();
            return fn;
        }

        const dispatch::functor* find(functor_t fptr) const
        {
            for (auto& functor : m_cache)
            {
                if (functor.is_same(fptr)) {
                    return &functor;
                }
            }
            return nullptr;
        }

        method_ptr(method_ptr&&) = delete;
        method_ptr(const method_ptr&) = delete;
        method_ptr& operator=(method_ptr&&) = delete;
        method_ptr& operator=(const method_ptr&) = delete;

    private:

        // No reallocation occurs; original objects stay intact
        mutable std::list<method_t> m_cache;

        method_ptr() = default;
    };
}