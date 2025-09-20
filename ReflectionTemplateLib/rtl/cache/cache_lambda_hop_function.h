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

#include "lambda_hop_function.h"

namespace rtl::cache
{
    template<class ...signature_ts>
    struct lambda_hop_function
    {
        static const lambda_hop_function& instance() 
        {
            static const lambda_hop_function instance_;
            return instance_;
        }

        template<class return_t>
        const dispatch::lambda_hop_function<signature_ts...>& push(const dispatch::functor* fptr) const
        {
            auto lambda = dispatch::lambda_hop_function<signature_ts...>::template create<return_t>(fptr);
            m_cache.push_back(lambda);
            fptr->set_lambda(&m_cache.back());
            return m_cache.back();
        }

        lambda_hop_function(lambda_hop_function&&) = delete;
        lambda_hop_function(const lambda_hop_function&) = delete;
        lambda_hop_function& operator=(lambda_hop_function&&) = delete;
        lambda_hop_function& operator=(const lambda_hop_function&) = delete;

    private:

        // No reallocation occurs; original objects stay intact
        mutable std::list<dispatch::lambda_hop_function<signature_ts...>> m_cache;

        lambda_hop_function() = default;
    };
}