/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


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

    template<class ...signature_t>
    class constructor;

    template<class return_t, class ...signature_t>
    class function;

    template<class record_t, class return_t, class ...signature_t>
    struct method;

    template<class record_t, class return_t, class ...signature_t>
    struct const_method;

    template<class return_t, class ...signature_t>
    struct static_method;

    namespace builder 
    {
        struct ReflectionBuilder;
    }

    namespace detail
    {
        enum call_by {
            value = 0,
            cref = 1,   //const ref.
            ncref = 2   //non-const ref.
        };

        struct FunctorId;

        struct RObjectId;

        class CxxReflection;

        template<member, class record_t = std::nullptr_t>
        struct HopBuilder;

        template<member, class record_t, class ...signature_t>
        struct InitMethodHop;

        template<member, class ...signature_t>
        struct InitFunctionHop;
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