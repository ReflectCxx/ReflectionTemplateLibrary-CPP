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

#include "method_ptr.h"
#include "method_ptr_const.h"

#include "rtl_method.h"
#include "rtl_method_const.h"


namespace rtl::dispatch
{
    template<class record_t, class ...signature_t>
    struct lambda_method : public lambda_base
    {
        template<class return_t>
        using hopper_t = rtl::method<record_t, return_t(signature_t...)>;

        template<class return_t>
        constexpr decltype(auto) get_functor(std::size_t p_returnId = 0) const
        {
            return static_cast<const method_ptr<record_t, return_t, signature_t...>&>(m_functor).f_ptr();
        }

        template<class return_t> requires (!std::is_const_v<record_t>)
        constexpr const hopper_t<return_t> get_hopper(std::size_t p_returnId = 0) const
        {
            if (p_returnId == 0 || p_returnId == m_functor.m_return_id) [[likely]]
            {
                auto fptr = static_cast<const method_ptr<record_t, return_t, signature_t...>&>(m_functor).f_ptr();
                return hopper_t<return_t>(fptr);
            }
            return hopper_t<return_t>();
        }

        template<class return_t>
        using hopper_ct = rtl::method<const record_t, return_t(signature_t...)>;

        template<class return_t> requires (std::is_const_v<record_t>)
        constexpr const hopper_ct<return_t> get_hopper(std::size_t p_returnId = 0) const
        {
            if (p_returnId == 0 || p_returnId == m_functor.m_return_id) [[likely]]
            {
                auto fptr = static_cast<const method_ptr<const record_t, return_t, signature_t...>&>(m_functor).f_ptr();
                return hopper_ct<return_t>(fptr);
            }
            return hopper_ct<return_t>();
        }

        lambda_method(const functor& p_functor, const erasure_base& p_erasure) noexcept
            : lambda_base(p_functor, p_erasure)
        { }
    };
}