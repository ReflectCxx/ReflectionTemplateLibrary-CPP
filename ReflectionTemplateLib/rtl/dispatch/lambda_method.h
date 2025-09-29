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
#include "rtl_method.h"
#include "erased_method.h"
#include "functor_method.h"
#include "rtl_method_const.h"


namespace rtl::dispatch
{
    template<class record_t, class ...signature_ts>
    struct lambda_method : public lambda_base
    {
        template<class return_t>
        using hopper_t = rtl::method<return_t (record_t::*)(signature_ts...)>;

        template<class return_t>
        using hopper_ct = rtl::method<return_t (record_t::*)(signature_ts...) const>;

        erase::erased_method<record_t, signature_ts...>* m_erasure;

        lambda_method(const functor& p_functor, erase::erased_method<record_t, signature_ts...>* p_erasure) noexcept
            : lambda_base(p_functor)
            , m_erasure(p_erasure)
        { }

        template<class return_t> requires (std::is_const_v<record_t> == false)
        constexpr const hopper_t<return_t> get_hopper(std::size_t p_returnId = 0) const
        {
            if (p_returnId == 0 || p_returnId == m_functor.m_returnId) [[likely]]
            {
                auto fptr = static_cast<const method_ptr<record_t, return_t, signature_ts...>&>(m_functor).f_ptr();
                return hopper_t<return_t>(fptr);
            }
            return hopper_t<return_t>();
        }

        template<class return_t> requires (std::is_const_v<record_t> == true)
        constexpr const hopper_ct<return_t> get_hopper(std::size_t p_returnId = 0) const
        {
            if (p_returnId == 0 || p_returnId == m_functor.m_returnId) [[likely]]
            {
                auto fptr = static_cast<const method_ptr<record_t, return_t, signature_ts...>&>(m_functor).f_ptr();
                return hopper_ct<return_t>(fptr);
            }
            return hopper_ct<return_t>();
        }
    };
}