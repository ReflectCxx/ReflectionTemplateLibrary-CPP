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

#include <detail/inc/RObjectId.h>
#include <dispatch/function_ptr.h>
#include <dispatch/aware_return.h>
#include <dispatch/aware_constructor.h>

namespace rtl::dispatch
{
    template<class return_t, class ...signature_t>
    template<detail::member mem_kind, class record_t>
    void function_ptr<return_t, signature_t...>::init_lambda()
    {
        m_lambda = ctor_t();
        ctor_t& fn = m_lambda.template emplace<ctor_t>();
        if constexpr (mem_kind == detail::member::DefaultCtor) {
            m_functor = &aware_constructor<record_t>::default_ctor;
		}
        else {
            fn.init(&aware_constructor<record_t, signature_t...>::overloaded_ctor);
		}

        functor::m_lambdas = std::vector<lambda*>(1);
        functor::m_lambdas[index::erased_ctor] = (&fn);
    }


    template<class return_t, class ...signature_t>
    void function_ptr<return_t, signature_t...>::init_lambda()
    {
        m_lambda = func_t();
        func_t& fn = m_lambda.template emplace<func_t>();

        fn.init(&aware_return<return_t, signature_t...>::get_lambda_any_return);

        functor::m_lambdas = std::vector<lambda*>(1);
        functor::m_lambdas[index::erased_return] = (&fn);
    }
}