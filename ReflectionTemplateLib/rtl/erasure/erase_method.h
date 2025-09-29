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

#include <any>
#include "rtl_forward_decls.h"

namespace rtl::erase
{
    template<class record_t, class ...signature_ts>
    struct method
    {
        using this_t = method<record_t, signature_ts...>;

        using functor_vt = void(*)(this_t*, const record_t&, signature_ts&&...);

        using functor_rt = std::any(*)(this_t*, const record_t&, signature_ts&&...);

        functor_vt v_hop = nullptr;

        functor_rt r_hop = nullptr;

        FORCE_INLINE void hop_v(const record_t& p_target, signature_ts&&...params)
        {
            v_hop(this, p_target, std::forward<signature_ts>(params)...);
        }

        FORCE_INLINE std::any hop_r(const record_t& p_target, signature_ts&&...params)
        {
            return r_hop(this, p_target, std::forward<signature_ts>(params)...);
        }
    };
}