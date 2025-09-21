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
    struct lambda_method
    {
        static const lambda_method& instance()
        {
            static const lambda_method instance_;
            return instance_;
        }

        const dispatch::lambda_method<record_t, signature_ts...>& push(const dispatch::functor& fptr) const
        {
            m_cache.push_back(dispatch::lambda_method<record_t, signature_ts...>(fptr));
            fptr.m_lambda = &m_cache.back();
            return m_cache.back();
        }

        lambda_method(lambda_method&&) = delete;
        lambda_method(const lambda_method&) = delete;
        lambda_method& operator=(lambda_method&&) = delete;
        lambda_method& operator=(const lambda_method&) = delete;

    private:

        // No reallocation occurs; original objects stay intact
        mutable std::list<dispatch::lambda_method<record_t, signature_ts...>> m_cache;

        lambda_method() = default;
    };
}