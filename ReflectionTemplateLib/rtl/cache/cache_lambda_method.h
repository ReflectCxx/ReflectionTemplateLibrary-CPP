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
#include "aware_return_fn_rec.h"
#include "aware_return_fn_rec_const.h"

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

        std::pair<const dispatch::lambda_base*, const dispatch::erase_fn_base*> push(const dispatch::functor& p_functor) const
        {
            m_erasure_cache.push_back(dispatch::aware_return_fn_rec<record_t, return_t, signature_t...>(p_functor));
            
            const dispatch::erase_fn_base& eb = m_erasure_cache.back();

            m_cache.push_back(dispatch::lambda_method<record_t, signature_t...>(p_functor, eb));

            return { &m_cache.back(), &m_erasure_cache.back() };
        }

        lambda_method(lambda_method&&) = delete;
        lambda_method(const lambda_method&) = delete;
        lambda_method& operator=(lambda_method&&) = delete;
        lambda_method& operator=(const lambda_method&) = delete;

    private:

        // No reallocation occurs; original objects stay intact
        mutable std::list<dispatch::lambda_method<record_t, signature_t...>> m_cache;
        mutable std::list<dispatch::aware_return_fn_rec<record_t, return_t, signature_t...>> m_erasure_cache;

        lambda_method() = default;
    };
}