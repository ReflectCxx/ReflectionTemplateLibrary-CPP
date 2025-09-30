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
#include "RObjectId.h"
#include "rtl_forward_decls.h"

namespace rtl::erase
{
    template<class record_t, class ...signature_ts>
    struct erased_method
    {
        constexpr void hop_v(const record_t& p_target, signature_ts&&...params) const noexcept
        {
            (*hopper_v)(this, p_target, std::forward<signature_ts>(params)...);
        }

        ForceInline std::any hop_r(const record_t& p_target, signature_ts&&...params) const noexcept
        {
            return (*hopper_r)(this, p_target, std::forward<signature_ts>(params)...);
        }

        GETTER(detail::RObjectId, _robject_id, robj_id);

    protected:

        using this_t = erased_method<record_t, signature_ts...>;

        using functor_vt = void(*)(const this_t*, const record_t& , signature_ts&&...);

        using functor_rt = std::any(*)(const this_t*, const record_t& , signature_ts&&...);

        functor_vt hopper_v = nullptr;

        functor_rt hopper_r = nullptr;

        detail::RObjectId robj_id;
    };
}