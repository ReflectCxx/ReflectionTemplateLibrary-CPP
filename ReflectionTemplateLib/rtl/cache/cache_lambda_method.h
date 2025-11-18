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
#include "aware_return_n_target.h"
#include "aware_return_n_target_const.h"

namespace rtl::cache
{
    template<class record_t, class return_t, class ...signature_t>
    struct lambda_method
    {
        static const lambda_method& instance()
        {
            static const lambda_method instance_;
            return instance_;
        }

        const dispatch::lambda_base* push(const dispatch::functor& p_functor) const
        {
            m_cache.push_back(dispatch::lambda_method<record_t, signature_t...>(p_functor));
            return &m_cache.back();
        }

        lambda_method(lambda_method&&) = delete;
        lambda_method(const lambda_method&) = delete;
        lambda_method& operator=(lambda_method&&) = delete;
        lambda_method& operator=(const lambda_method&) = delete;

    private:

        // No reallocation occurs; original objects stay intact
        mutable std::list<dispatch::lambda_method<record_t, signature_t...>> m_cache;
        
        lambda_method() = default;
    };
}