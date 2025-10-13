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

#include "lambda_base.h"
#include "rtl_function.h"
#include "function_ptr.h"
#include "erased_hopper.h"

namespace rtl::dispatch
{
    template<class ...signature_t>
    struct lambda_function: public lambda_base
    {
        template<class return_t>
        using hopper_t = rtl::function<return_t(signature_t...)>;

        template<class return_t>
        constexpr decltype(auto) get_functor(const std::size_t p_returnId = 0) const
        {
            return static_cast<const function_ptr<return_t, signature_t...>&>(m_functor).f_ptr();
        }

        template<class return_t>
        constexpr const hopper_t<return_t> get_hopper(const std::size_t p_returnId = 0) const
        {
            if (p_returnId == 0 || p_returnId == m_functor.m_returnId) [[likely]]
            {
                auto fptr = static_cast<const function_ptr<return_t, signature_t...>&>(m_functor).f_ptr();
                return hopper_t<return_t>(fptr);
            }
            return hopper_t<return_t>();
        }

        lambda_function(const functor& p_functor, const erase::erasure_base& p_erasure) noexcept
            : lambda_base(p_functor, p_erasure)
        { }
    };
}