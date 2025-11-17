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

#include "functor.h"

namespace rtl::dispatch
{
    template<fn_void fn_void_v, class...signature_t>
    struct functor_cast
    {
        const functor& m_functor;
        
        template<erase erase_v>
        constexpr auto to_method()
        {
            if constexpr (erase_v == erase::t_method)
            {
                using lambda_t = function_lambda<fn_void_v, erase::t_method, signature_t...>;
                return static_cast<lambda_t&>(*m_functor.m_lambdas[functor::index::erased_method]);
            }
        }

        template<erase erase_v, class known_t>
        constexpr auto to_method()
        {
            if constexpr (erase_v == erase::t_return)
            {
                using target_t = known_t;
                using lambda_t = method_lambda<fn_void_v, erase::t_ctor, target_t, signature_t...>;
                return static_cast<lambda_t&>(*m_functor.m_lambdas[functor::index::erased_return]);
            }
            else if constexpr (erase_v == erase::t_target)
            {
                using return_t = known_t;
                using lambda_t = method_lambda<fn_void_v, erase::t_return, return_t, signature_t...>;
                return static_cast<lambda_t&>(*m_functor.m_lambdas[functor::index::erased_target]);
            }
        }

        template<erase erase_v>
        constexpr auto to_function()
        {
            if constexpr (erase_v == erase::t_ctor)
            {
                using lambda_t = function_lambda<fn_void_v, erase::t_ctor, signature_t...>;
                return static_cast<lambda_t&>(*m_functor.m_lambdas[functor::index::erased_ctor]);
            }
            else if constexpr (erase_v == erase::t_return)
            {
                using lambda_t = function_lambda<fn_void_v, erase::t_return, signature_t...>;
                return static_cast<lambda_t&>(*m_functor.m_lambdas[functor::index::erased_return]);
            }
        }
    };
}