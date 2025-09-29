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

#include "erase_function.h"
#include "rtl_function.h"

namespace rtl::erase
{
    template<class return_t, class ...signature_ts>
    struct return_function : public function<signature_ts...>
    {
        using base_t = function<signature_ts...>;

        using this_t = return_function<return_t, signature_ts...>;

        rtl::function<return_t(signature_ts...)> m_function;

        return_function()
        {
            base_t::v_hop = hop_v;
            base_t::r_hop = hop_r;
        }

        FORCE_INLINE static void hop_v(base_t* p_this, signature_ts&&...params)
        {
            if constexpr (std::is_void_v<return_t>)
            {
                auto this_p = static_cast<this_t*>(p_this);
                this_p->m_function(std::forward<signature_ts>(params)...);
            }
        }

        FORCE_INLINE static std::any hop_r(base_t* p_this, signature_ts&&...params)
        {
            if constexpr (!std::is_void_v<return_t>)
            {
                auto this_p = static_cast<this_t*>(p_this);
                auto&& ret_v = this_p->m_function(std::forward<signature_ts>(params)...);

                if constexpr (std::is_reference_v<return_t>)
                {
                    return std::any(&ret_v);
                }
                else
                {
                    return std::any(std::forward<decltype(ret_v)>(ret_v));
                }
            }
            else return std::any();
        }
    };
}