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

#include "aware_method.h"
#include "lambda_method.h"
#include "aware_method_const.h"

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

        const dispatch::lambda_method<record_t, signature_ts...>& push(const dispatch::functor& p_functor) const
        {
            m_erasure_cache.push_back(erase::aware_method<record_t, return_t, signature_ts...>());
            erase::erased_method<record_t, signature_ts...>* erasure = &m_erasure_cache.back();

            m_cache.push_back(dispatch::lambda_method<record_t, signature_ts...>(p_functor, erasure));
            p_functor.m_lambda = &m_cache.back();

            m_erasure_cache.back().m_method = m_cache.back().template get_hopper<return_t>();

            return m_cache.back();
        }

        lambda_method(lambda_method&&) = delete;
        lambda_method(const lambda_method&) = delete;
        lambda_method& operator=(lambda_method&&) = delete;
        lambda_method& operator=(const lambda_method&) = delete;

    private:

        // No reallocation occurs; original objects stay intact
        mutable std::list<dispatch::lambda_method<record_t, signature_ts...>> m_cache;
        mutable std::list<erase::aware_method<record_t, return_t, signature_ts...>> m_erasure_cache;

        lambda_method() = default;
    };
}