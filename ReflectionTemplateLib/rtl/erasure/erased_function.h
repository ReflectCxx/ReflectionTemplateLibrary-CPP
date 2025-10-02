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

#include "RObjectId.h"
#include "erasure.h"

namespace rtl::erase
{
    template<class ...signature_ts>
    struct erased_function : erasure_base
    {
        constexpr void hop_v(signature_ts&&...params) const noexcept
        {
            (*hopper_v)(this, std::forward<signature_ts>(params)...);
        }

        ForceInline std::any hop_r(signature_ts&&...params) const noexcept
        {
            return (*hopper_r)(this, std::forward<signature_ts>(params)...);
        }

        constexpr void hop_v(const RObject& p_robj, signature_ts&&...params) const noexcept
        {
            (*hopper_robj_v)(this, p_robj, std::forward<signature_ts>(params)...);
        }

        ForceInline std::any hop_r(const RObject& p_robj, signature_ts&&...params) const noexcept
        {
            return (*hopper_robj_r)(this, p_robj, std::forward<signature_ts>(params)...);
        }

    protected:

        using this_t = erased_function<signature_ts...>;

        using functor_vt = void(*)(const this_t*, signature_ts&&...);

        using functor_rt = std::any(*)(const this_t*, signature_ts&&...);

        using func_ro_vt = void(*)(const this_t*, const RObject&, signature_ts&&...);

        using func_ro_rt = std::any(*)(const this_t*, const RObject&, signature_ts&&...);

        functor_vt hopper_v = nullptr;

        functor_rt hopper_r = nullptr;

        func_ro_vt hopper_robj_v = nullptr;

        func_ro_rt hopper_robj_r = nullptr;

        erased_function(const dispatch::functor& p_functor, const detail::RObjectId& p_robj_id) noexcept
            : erasure_base(p_functor, p_robj_id)
        { }
    };
}