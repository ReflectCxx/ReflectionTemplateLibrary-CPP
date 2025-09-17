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

#include "lambda.h"

namespace rtl::detail
{
    template<class ...signature_ts>
    struct lambda_cache
    {
        static lambda_cache& get() {
            static lambda_cache instance;
            return instance;
        }

        std::pair<std::size_t, const lambda_hop*> push(const dispatch::lambda<signature_ts...>& lambda_hop) 
        {
            m_cache.push_back(lambda_hop);
            return { (m_cache.size() - 1), &m_cache.back() };
        }

        lambda_cache(lambda_cache&&) = delete;
        lambda_cache(const lambda_cache&) = delete;
        lambda_cache& operator=(lambda_cache&&) = delete;
        lambda_cache& operator=(const lambda_cache&) = delete;

    private:

        // No reallocation occurs; original objects stay intact
        std::deque<const dispatch::lambda<signature_ts...>> m_cache;
        lambda_cache() {}
    };
}