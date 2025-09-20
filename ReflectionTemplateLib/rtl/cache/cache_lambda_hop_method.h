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

#include "lambda_hop_method.h"


namespace rtl::cache
{
    template<class record_t, class ...signature_ts>
    struct lambda_hop_method
    {
        static const lambda_hop_method& instance()
        {
            static const lambda_hop_method instance_;
            return instance_;
        }

        template<class return_t>
        const dispatch::lambda_hop_method<record_t, signature_ts...>& push(const dispatch::functor* fptr) const
        {
            auto lambda = dispatch::lambda_hop_method<record_t, signature_ts...>::template create<return_t>(fptr);
            m_cache.push_back(lambda);
            fptr->set_lambda(&m_cache.back());
            return m_cache.back();
        }

        lambda_hop_method(lambda_hop_method&&) = delete;
        lambda_hop_method(const lambda_hop_method&) = delete;
        lambda_hop_method& operator=(lambda_hop_method&&) = delete;
        lambda_hop_method& operator=(const lambda_hop_method&) = delete;

    private:

        // No reallocation occurs; original objects stay intact
        mutable std::list<dispatch::lambda_hop_method<record_t, signature_ts...>> m_cache;

        lambda_hop_method() = default;
    };
}