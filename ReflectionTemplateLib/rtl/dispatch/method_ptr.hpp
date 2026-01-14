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

#include <dispatch/method_ptr.h>
#include <dispatch/aware_return_n_target.h>

namespace rtl::dispatch
{
    template<class record_t, class return_t, class ...signature_t>
    void method_ptr<record_t, return_t, signature_t...>::init_lambda()
    {
        using lambda_t = aware_return_n_target<record_t, return_t, signature_t...>;

        m_erased_method.init(&lambda_t::erased_return_and_target);
        m_erased_target.init(&lambda_t::erased_target_aware_return);
        m_erased_return.init(&lambda_t::erased_return_aware_target);

        functor::m_lambdas = std::vector<lambda*>(3);
        functor::m_lambdas[index::erased_return] = (&m_erased_return);
        functor::m_lambdas[index::erased_target] = (&m_erased_target);
        functor::m_lambdas[index::erased_method] = (&m_erased_method);
    }
}