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

#include "erasure.h"
#include "rtl_traits.h"
#include "rtl_function.h"
#include "rtl_errors.h"
#include <type_traits>

namespace rtl::erase
{
    template<class return_t, class ...signature_ts>
    struct function_return : public erasure_base<signature_ts...>
    {
        rtl::function<return_t(signature_ts...)> m_function;

        function_return()
        {
            erasure_base<signature_ts...>::v_hop = vhop;
            erasure_base<signature_ts...>::r_hop = rhop;
        }

        FORCE_INLINE static void vhop(erasure_base<signature_ts...>* p_this, signature_ts&&...params)
        {
            if constexpr (std::is_void_v<return_t>)
            {
                auto this_p = static_cast<function_return<return_t, signature_ts...>*>(p_this);
                this_p->m_function(std::forward<signature_ts>(params)...);
            }
        }

        FORCE_INLINE static std::any rhop(erasure_base<signature_ts...>* p_this, signature_ts&&...params)
        {
            if constexpr (!std::is_void_v<return_t>)
            {
                auto this_p = static_cast<function_return<return_t, signature_ts...>*>(p_this);
                auto&& ret_v = this_p->m_function(std::forward<signature_ts>(params)...);
                return std::any(std::forward<decltype(ret_v)>(ret_v));
            }
            else return std::any();
        }
    };
}