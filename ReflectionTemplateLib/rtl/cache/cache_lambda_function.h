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
#include "erase_return.h"

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

        std::pair<const dispatch::lambda_base*, const dispatch::erasure_base*> push(const dispatch::functor& p_functor) const
        {
            using erase_ret_t = dispatch::erase_return<traits::normal_sign_t<signature_t>...>;
            m_erasure_cache.emplace_back(erase_ret_t());

            erase_ret_t& eb = m_erasure_cache.back();
            eb.template init_base<false, return_t, signature_t...>();

            m_cache.push_back(dispatch::lambda_function<signature_t...>(p_functor, eb));
            return { &m_cache.back(), &eb };
        }

        lambda_function(lambda_function&&) = delete;
        lambda_function(const lambda_function&) = delete;
        lambda_function& operator=(lambda_function&&) = delete;
        lambda_function& operator=(const lambda_function&) = delete;

    private:

        // No reallocation occurs; original objects stay intact
        mutable std::list<dispatch::lambda_function<signature_t...>> m_cache;
        mutable std::list<dispatch::erase_return<traits::normal_sign_t<signature_t>...>> m_erasure_cache;

        lambda_function() = default;
    };
}