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

#include "lambda.h"
#include "RObjectBuilder.hpp"

namespace rtl::dispatch
{
    template<class ...signature_ts>
    template<class record_t, class return_t>
    inline Return lambda<signature_ts...>::method_const(const lambda_hop&, signature_ts&&...) noexcept
    {
        return { error::EmptyRObject, RObject{} };
    }
}