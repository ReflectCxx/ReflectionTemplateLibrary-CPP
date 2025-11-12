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

#include <functional>

#include "erasure_base.h"

namespace rtl::dispatch
{
    template<class ...normal_sign_t>
    struct erase_constructor : public erasure_base
    {
        using lambda_t = std::function<Return(alloc, normal_sign_t...)>;

        GETTER_CREF(lambda_t, _hopper, m_hopper)

    protected:

        lambda_t m_hopper;

        erase_constructor(const lambda_t& p_hop) noexcept
            : m_hopper(p_hop)
        { }
    };
}