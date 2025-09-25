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

#include "lambda.h"
#include "function_ptr.h"
#include "rtl_function.h"

namespace rtl::dispatch
{
    template<class ...signature_ts>
    struct lambda_function: public lambda_base
    {
        template<class return_t>
        using hopper_t = function<return_t(signature_ts...)>;

        lambda_function(const functor& p_functor) noexcept
            :lambda_base(p_functor)
        { }

        template<class return_t>
        constexpr const hopper_t<return_t> get_hopper(const std::size_t p_returnId = 0) const
        {
            if (p_returnId == 0 || p_returnId == m_functor.m_returnId) [[likely]]
            {
                return hopper_t<return_t> {
                    static_cast<const function_ptr<return_t, signature_ts...>&>(m_functor).f_ptr()
                };
            }
            return hopper_t<return_t>();
        }
    };
}