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

#include "LambdaRegistry.h"


namespace rtl::detail
{
    template<methodQ>
    struct lambda_cache;
}

namespace rtl::detail
{
    template<>
    struct lambda_cache<methodQ::None>
    {
        template<class ...signature_ts>
        static lambda_registry<methodQ::None, signature_ts...>& get()
        {
            static lambda_registry<methodQ::None, signature_ts...> registry;
            return registry;
        }
    };


    template<>
    struct lambda_cache<methodQ::Const>
    {
        template<class ...signature_ts>
        static lambda_registry<methodQ::Const, signature_ts...>& get()
        {
            static lambda_registry<methodQ::Const, signature_ts...> registry;
            return registry;
        }
    };


    template<>
    struct lambda_cache<methodQ::NonConst>
    {
        template<class ...signature_ts>
        static lambda_registry<methodQ::NonConst, signature_ts...>& get()
        {
            static lambda_registry<methodQ::NonConst, signature_ts...> registry;
            return registry;
        }
    };
}