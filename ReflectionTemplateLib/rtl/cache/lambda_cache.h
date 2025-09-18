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

#include "lambda.h"

namespace rtl::dispatch
{
    template<class ...signature_ts>
    struct lambda_cache
    {
        static lambda_cache& get() 
        {
            static lambda_cache instance;
            return instance;
        }

        template<class return_t>
        const lambda<signature_ts...>& push_function(const functor_hop* fptr_hopper)
        {
            m_cache.push_back(lambda<signature_ts...>::template create_function<return_t>(fptr_hopper));

            const lambda<signature_ts...>& lambda_hop = m_cache.back();
            
            fptr_hopper->set_lambda(&lambda_hop);
            
            return lambda_hop;
        }

        lambda_cache(lambda_cache&&) = delete;
        lambda_cache(const lambda_cache&) = delete;
        lambda_cache& operator=(lambda_cache&&) = delete;
        lambda_cache& operator=(const lambda_cache&) = delete;

    private:

        // No reallocation occurs; original objects stay intact
        std::list<lambda<signature_ts...>> m_cache;

        lambda_cache() {}
    };
}