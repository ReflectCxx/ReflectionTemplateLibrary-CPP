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
    template<class ...signature_ts>
    struct erasure_base
    {
        using functor_vt = void(*)(erasure_base<signature_ts...>*, signature_ts&&...);
        using functor_rt = std::any(*)(erasure_base<signature_ts...>*, signature_ts&&...);

        functor_vt v_hop = nullptr;
        functor_rt r_hop = nullptr;

        FORCE_INLINE void hop_v(signature_ts&&...params) 
        {
            v_hop(this, std::forward<signature_ts>(params)...);
        }

        FORCE_INLINE std::any hop_r(signature_ts&&...params)
        {
            return r_hop(this, std::forward<signature_ts>(params)...);
        }
    };
}