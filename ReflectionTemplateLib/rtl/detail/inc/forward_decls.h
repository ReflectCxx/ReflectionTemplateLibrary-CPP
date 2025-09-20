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

    class Function;

    class Method;

    class CxxMirror;
    
    namespace detail 
    {
        struct FunctorId;

        template<class ..._signature>
        class FunctorContainer;
    }

    namespace dispatch
    {
        struct functor;

        class lambda_hop;

        template<class ...signature_ts>
        class lambda_hop_function;

        template<class record_t, class ...signature_ts>
        class lambda_hop_method;

        template<class ...signature_ts>
        struct function_ptr;

        template<class record_t, class ...signature_ts>
        struct const_method_ptr;

        template<class record_t, class ...signature_ts>
        struct method_ptr;
    }
}