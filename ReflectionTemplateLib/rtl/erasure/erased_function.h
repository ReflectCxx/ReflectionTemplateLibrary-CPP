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

namespace rtl::erase
{
    template<class ...signature_ts>
    struct erased_function
    {
        constexpr void hop(std::optional<std::any>& p_return, signature_ts&&...params) const noexcept
        {
            (*hopper)(this, p_return, std::forward<signature_ts>(params)...);
        }

        GETTER(detail::RObjectId, _robject_id, robj_id);

    protected:

        using this_t = erased_function<signature_ts...>;

        using functor_t = void(*)(const this_t*, std::optional<std::any>&, signature_ts&&...);

        functor_t hopper = nullptr;

        detail::RObjectId robj_id;
    };
}