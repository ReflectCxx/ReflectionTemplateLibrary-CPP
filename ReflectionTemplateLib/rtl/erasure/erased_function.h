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
#include "rtl_forward_decls.h"
#include "rtl_typeid.h"

namespace rtl::erase
{
    template<class ...signature_ts>
    struct erased_function
    {
        constexpr void hop_v(signature_ts&&...params) const noexcept
        {
            (*hopper_v)(this, std::forward<signature_ts>(params)...);
        }

        ForceInline std::any hop_r(signature_ts&&...params) const noexcept
        {
            return (*hopper_r)(this, std::forward<signature_ts>(params)...);
        }

        GETTER(detail::RObjectId, _robject_id, robj_id);

    protected:

        using this_t = erased_function<signature_ts...>;

        using functor_vt = void(*)(const this_t*, signature_ts&&...);

        using functor_rt = std::any(*)(const this_t*, signature_ts&&...);

        functor_vt hopper_v = nullptr;

        functor_rt hopper_r = nullptr;

        detail::RObjectId robj_id;
    };
}