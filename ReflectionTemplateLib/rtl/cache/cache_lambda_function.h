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
#include "aware_hopper.h"

namespace rtl::cache
{
    template<class return_t, class ...signature_t>
    struct lambda_function
    {
        static const lambda_function& instance() 
        {
            static const lambda_function instance_;
            return instance_;
        }

        std::pair<const dispatch::lambda_base*, const dispatch::erased_fnbase*> push(const dispatch::functor& p_functor) const
        {
            m_erasure_cache.push_back(dispatch::aware_hopper<return_t, signature_t...>(p_functor));

            const dispatch::erased_fnbase& eb = m_erasure_cache.back();

            m_cache.push_back(dispatch::lambda_function<signature_t...>(p_functor, eb));

            return { &m_cache.back(), &m_erasure_cache.back() };
        }

        lambda_function(lambda_function&&) = delete;
        lambda_function(const lambda_function&) = delete;
        lambda_function& operator=(lambda_function&&) = delete;
        lambda_function& operator=(const lambda_function&) = delete;

    private:

        // No reallocation occurs; original objects stay intact
        mutable std::list<dispatch::lambda_function<signature_t...>> m_cache;
        mutable std::list<dispatch::aware_hopper<return_t, signature_t...>> m_erasure_cache;

        lambda_function() = default;
    };
}