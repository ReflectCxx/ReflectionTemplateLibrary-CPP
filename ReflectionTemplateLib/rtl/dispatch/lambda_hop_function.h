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

#include "lambda_hop.h"

namespace rtl::dispatch
{
    template<class ...signature_ts>
    struct lambda_hop_function: public lambda_hop
    {
        lambda_hop_function(const functor*) noexcept;

        template<class return_t, class...args_t>
        decltype(auto) dispatch(args_t&&...) const noexcept;
    };
}