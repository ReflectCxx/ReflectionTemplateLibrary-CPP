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

#include "rtl_forward_decls.h"

namespace rtl::erase
{
    template<class record_t, class ...signature_ts>
    struct erased_method
    {
        constexpr void void_hop(const record_t& p_target, signature_ts&&...params) const noexcept
        {
            (*hop_void)(this, p_target, std::forward<signature_ts>(params)...);
        }

        ForceInline rtl::Return return_hop(const record_t& p_target, signature_ts&&...params) const noexcept
        {
            return (*hop_return)(this, p_target, std::forward<signature_ts>(params)...);
        }

    protected:

        using this_t = erased_method<record_t, signature_ts...>;

        using functor_vt = void(*)(const this_t*, const record_t&, signature_ts&&...);

        using functor_rt = rtl::Return(*)(const this_t*, const record_t&, signature_ts&&...);

        functor_vt hop_void = nullptr;

        functor_rt hop_return = nullptr;
    };
}