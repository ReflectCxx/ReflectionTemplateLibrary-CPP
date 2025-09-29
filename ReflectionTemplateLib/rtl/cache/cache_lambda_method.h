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

#include "lambda_method.h"
#include "return_method.h"
#include "return_const_method.h"

namespace rtl::cache
{
    template<class record_t, class return_t, class ...signature_ts>
    struct lambda_method
    {
        static const lambda_method& instance()
        {
            static const lambda_method instance_;
            return instance_;
        }

        const dispatch::lambda_method<record_t, signature_ts...>& push(const dispatch::functor& fptr) const
        {
            m_erasure_cache.push_back(erase::return_method<record_t, return_t, signature_ts...>());
            erase::method<record_t, signature_ts...>* erasure = &m_erasure_cache.back();

            m_cache.push_back(dispatch::lambda_method<record_t, signature_ts...>(fptr, erasure));
            fptr.m_lambda = &m_cache.back();

            (m_cache.back()).template init_erasure<return_t>();

            return m_cache.back();
        }

        lambda_method(lambda_method&&) = delete;
        lambda_method(const lambda_method&) = delete;
        lambda_method& operator=(lambda_method&&) = delete;
        lambda_method& operator=(const lambda_method&) = delete;

    private:

        // No reallocation occurs; original objects stay intact
        mutable std::list<dispatch::lambda_method<record_t, signature_ts...>> m_cache;
        mutable std::list<erase::return_method<record_t, return_t, signature_ts...>> m_erasure_cache;

        lambda_method() = default;
    };
}