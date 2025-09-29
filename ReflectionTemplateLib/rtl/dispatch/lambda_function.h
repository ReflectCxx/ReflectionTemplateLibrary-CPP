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
#include "rtl_function.h"
#include "functor_function.h"
#include "erased_function.h"

namespace rtl::dispatch
{
    template<class ...signature_ts>
    struct lambda_function: public lambda_base
    {
        template<class return_t>
        using hopper_t = rtl::function<return_t(signature_ts...)>;

        erase::erased_function<signature_ts...>* m_erasure;

        lambda_function(const functor& p_functor, erase::erased_function<signature_ts...>* p_erasure) noexcept
            : lambda_base(p_functor)
            , m_erasure(p_erasure)
        { }

        template<class return_t>
        constexpr const hopper_t<return_t> get_hopper(const std::size_t p_returnId = 0) const
        {
            if (p_returnId == 0 || p_returnId == m_functor.m_returnId) [[likely]]
            {
                auto fptr = static_cast<const function_ptr<return_t, signature_ts...>&>(m_functor).f_ptr();
                return hopper_t<return_t>(fptr);
            }
            return hopper_t<return_t>();
        }
    };
}