/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#pragma once

#include <dispatch/functor.h>

namespace rtl::dispatch
{
    template<class...signature_t>
    struct functor_cast
    {
        const functor& m_functor;

        constexpr auto to_method()
        {
            using lambda_t = function_lambda<erase::t_method, signature_t...>;
            return static_cast<lambda_t&>(*m_functor.m_lambdas[functor::index::erased_method]);
        }

        template<erase erase_v, class known_t>
        constexpr auto to_method()
        {
            using lambda_t = method_lambda<erase_v, known_t, signature_t...>;
            if constexpr (erase_v == erase::t_return)
            {
                return static_cast<lambda_t&>(*m_functor.m_lambdas[functor::index::erased_return]);
            }
            else if constexpr (erase_v == erase::t_target)
            {
                return static_cast<lambda_t&>(*m_functor.m_lambdas[functor::index::erased_target]);
            }
        }

        template<erase erase_v>
        constexpr auto to_function()
        {
            using lambda_t = function_lambda<erase_v, signature_t...>;
            if constexpr (erase_v == erase::t_ctor)
            {
                return static_cast<lambda_t&>(*m_functor.m_lambdas[functor::index::erased_ctor]);
            }
            else if constexpr (erase_v == erase::t_return)
            {
                return static_cast<lambda_t&>(*m_functor.m_lambdas[functor::index::erased_return]);
            }
        }
    };
}