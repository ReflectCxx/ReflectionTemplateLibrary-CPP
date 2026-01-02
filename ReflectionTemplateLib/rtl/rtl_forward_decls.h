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

    class Record;

    class Method;

    class CxxMirror;

    struct type_meta;

    template<class return_t, class ...signature_t>
    class function;

    template<class ...signature_t>
    class constructor;

    template<class record_t, class return_t, class ...signature_t>
    struct method;

    template<class record_t, class return_t, class ...signature_t>
    struct const_method;

    template<class return_t, class ...signature_t>
    struct static_method;

    namespace detail
    {
        enum call_by {
            value = 0,
            cref = 1,   //const ref.
            ncref = 2   //non-const ref.
        };

        struct FunctorId;

        struct RObjectId;

        struct SetupFunction;

        struct SetupConstructor;

        class CxxReflection;

        class ReflectionBuilder;

        template<bool is_bind_v, class ...signature_t>
        struct ErasedCaller;

        template<class record_t>
        struct ErasedInvoker;

        template<class _derivedType>
        class SetupMethod;

        template<member, class record_t = std::nullptr_t>
        struct Hopper;

        template<member, class ...signature_t>
        struct HopFunction;

        template<member, class record_t, class ...signature_t>
        struct HopMethod;
    }

    namespace cache
    {
        template<class return_t, class ...signature_t>
        struct function_ptr;

        template<class record_t, class return_t, class ...signature_t>
        struct method_ptr;
    }

    namespace dispatch
    {
        struct functor;

        struct lambda {};

        template<class...signature_t>
        struct functor_cast;

        enum class erase {
            t_ctor,
            t_target,
            t_return,
            t_method
        };

        template<erase, class...signature_t>
        struct function_lambda;

        template<erase, class known_t, class...signature_t>
        struct method_lambda;

        template<class return_t, class ...signature_t>
        struct function_ptr;

        template<class record_t, class return_t, class ...signature_t>
        struct method_ptr;

        template<class return_t, class ...signature_t>
        struct aware_return;

        template<class record_t, class ...signature_t>
        struct aware_constructor;

        template<class record_t, class return_t, class ...signature_t>
        struct aware_return_n_target;
    }
}