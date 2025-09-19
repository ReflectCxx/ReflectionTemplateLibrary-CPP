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

namespace rtl::dispatch
{
    template<class ...signature_ts>
    struct hopper_ctor
    {
        template<class record_t>
        static Return cloner(const lambda_hop&, signature_ts&&...) noexcept
        {
            return { error::EmptyRObject, RObject{} };
        }

        template<class record_t>
        static Return constructor(const lambda_hop&, signature_ts&&...) noexcept
        {
            return { error::EmptyRObject, RObject{} };
        }
    };
}