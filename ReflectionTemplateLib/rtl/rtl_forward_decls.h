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

namespace rtl 
{
    struct Return;

    class RObject;

    class Function;

    class Method;

    class CxxMirror;

    struct type_meta;

    template<class return_t, class ...signature_t>
    struct function;

    template<class record_t, class return_t, class ...signature_t>
    struct method;

    namespace detail
    {
        struct FunctorId;

        struct RObjectId;

        template<class ..._signature>
        class FunctorContainer;

        template<bool is_bind_v, class ..._signature>
        struct ErasedCaller;

        template<class _recordType>
        struct ErasedInvoker;

        template<class _derivedType>
        class SetupMethod;

        template<class _recordType = std::nullptr_t>
        struct Hopper;

        template<class ..._signature>
        struct HopFunction;
    }

    namespace cache
    {
        template<class return_t, class ...signature_t>
        struct lambda_function;

        template<class record_t, class return_t, class ...signature_t>
        struct lambda_method;
    }

    namespace dispatch
    {
        struct functor;

        struct lambda_base;

        struct erasure_base;

        template<class ...signature_t>
        struct lambda_function;

        template<class record_t, class ...signature_t>
        struct lambda_method;

        template<class return_t, class ...signature_t>
        struct function_ptr;

        template<class record_t, class return_t, class ...signature_t>
        struct method_ptr;

        template<class record_t, class return_t, class ...signature_t>
        struct const_method_ptr;

        template<class ...signature_t>
        struct erase_return;

        template<class return_t, class ...signature_t>
        struct aware_return;

        template<class ...signature_t>
        struct erase_return_n_target;

        template<class record_t, class ...signature_t>
        struct erase_return_aware_target;

        template<class return_t, class ...signature_t>
        struct erase_target_aware_return;

        template<class record_t, class return_t, class ...signature_t>
        struct aware_return_n_target;
    }
}