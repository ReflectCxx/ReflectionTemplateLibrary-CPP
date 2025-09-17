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

#include "rtl_constants.h"

namespace rtl 
{
    struct Return;

    class RObject;

    namespace detail 
    {
        struct FunctorId;

        template<class ..._signature>
        class FunctorContainer;
    }

    namespace dispatch
    {
        struct lambda_hop;

        struct functor_hop;
    }
}