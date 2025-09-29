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
#include "aware_function.h"

namespace rtl::cache
{
    template<class return_t, class ...signature_ts>
    struct lambda_function
    {
        static const lambda_function& instance() 
        {
            static const lambda_function instance_;
            return instance_;
        }

        const dispatch::lambda_function<signature_ts...>& push(const dispatch::functor& p_functor) const
        {
            m_erasure_cache.push_back(erase::aware_function<return_t, signature_ts...>());
            erase::erased_function<signature_ts...>* erasure = &m_erasure_cache.back();

            m_cache.push_back(dispatch::lambda_function<signature_ts...>(p_functor, erasure));
            p_functor.m_lambda = &m_cache.back();
            
            (m_erasure_cache.back()).m_function = m_cache.back().template get_hopper<return_t>();
            return m_cache.back();
        }

        lambda_function(lambda_function&&) = delete;
        lambda_function(const lambda_function&) = delete;
        lambda_function& operator=(lambda_function&&) = delete;
        lambda_function& operator=(const lambda_function&) = delete;

    private:

        // No reallocation occurs; original objects stay intact
        mutable std::list<dispatch::lambda_function<signature_ts...>> m_cache;
        mutable std::list<erase::aware_function<return_t, signature_ts...>> m_erasure_cache;

        lambda_function() = default;
    };
}