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

#include "lambda_function.h"

namespace rtl::cache
{
    template<class ...signature_ts>
    struct lambda_function
    {
        static const lambda_function& instance() 
        {
            static const lambda_function instance_;
            return instance_;
        }

        template<class return_t>
        const dispatch::lambda<signature_ts...>& push(const dispatch::functor_hop* fptr_hopper) const
        {
            m_cache.push_back(dispatch::lambda<signature_ts...>::template create<return_t>(fptr_hopper));
            const dispatch::lambda<signature_ts...>& lambda_hop = m_cache.back();
            fptr_hopper->set_lambda(&lambda_hop);
            return lambda_hop;
        }

        template<class record_t, class return_t>
        const dispatch::lambda<signature_ts...>& push_method_const(const dispatch::functor_hop* fptr_hopper) const
        {
            m_cache.push_back(dispatch::lambda<signature_ts...>::template create_method_const<record_t, return_t>(fptr_hopper));
            const dispatch::lambda<signature_ts...>& lambda_hop = m_cache.back();
            fptr_hopper->set_lambda(&lambda_hop);
            return lambda_hop;
        }

        lambda_function(lambda_function&&) = delete;
        lambda_function(const lambda_function&) = delete;
        lambda_function& operator=(lambda_function&&) = delete;
        lambda_function& operator=(const lambda_function&) = delete;

    private:

        // No reallocation occurs; original objects stay intact
        mutable std::list<dispatch::lambda<signature_ts...>> m_cache;

        lambda_function() {}
    };
}