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

    template<class functor_t>
    struct function;

    template<class functor_t>
    struct method;

    namespace erase
    {
        template<class ...signature_ts>
        struct erased_function;

        template<class record_t, class ...signature_ts>
        struct erased_method;

        template<class return_t, class ...signature_ts>
        struct aware_function;

        template<class record_t, class return_t, class ...signature_ts>
        struct aware_method;
    }

    namespace detail 
    {
        struct FunctorId;

        template<class ..._signature>
        class FunctorContainer;

        template<class _derivedType>
        class SetupMethod;

        template<class _recordType = std::nullptr_t>
        struct Hopper;
    }

    namespace cache
    {
        template<class return_t, class ...signature_ts>
        struct lambda_function;

        template<class record_t, class return_t, class ...signature_ts>
        struct lambda_method;
    }

    namespace dispatch
    {
        struct functor;

        struct lambda_base;

        template<class ...signature_ts>
        struct lambda_function;

        template<class record_t, class ...signature_ts>
        struct lambda_method;

        template<class return_t, class ...signature_ts>
        struct function_ptr;

        template<class record_t, class return_t, class ...signature_ts>
        struct method_ptr;

        template<class record_t, class return_t, class ...signature_ts>
        struct const_method_ptr;
    }
}