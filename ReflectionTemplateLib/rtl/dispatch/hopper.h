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

#include <cassert>

#include "lambda_hop_function.h"
#include "function_ptr.h"

namespace rtl::dispatch
{
    struct hopper
    {
        template<class ret_t, class ...params_t>
        static decltype(auto) dispatch(const lambda_hop& lambda_ref, params_t&&...params) noexcept
        {
        }
    };
}