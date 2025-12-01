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

#include "RObjectId.h"
#include "function_ptr.h"
#include "aware_return.h"
#include "aware_constructor.h"

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

        if constexpr (fn_void_v == fn_void::yes) {
            fn.init(&aware_return<return_t, signature_t...>::get_lambda_void);
        }
        else {
            fn.init(&aware_return<return_t, signature_t...>::get_lambda_any_return);
        }

        functor::m_lambdas = std::vector<lambda*>(1);
        functor::m_lambdas[index::erased_return] = (&fn);

        constexpr static bool isConstCastSafe = (!traits::is_const_v<return_t>);
        m_robject_id = detail::RObjectId::create<return_t, alloc::Stack>(isConstCastSafe);
    }
}