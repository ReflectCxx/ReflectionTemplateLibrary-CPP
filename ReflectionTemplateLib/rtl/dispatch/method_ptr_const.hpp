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

#include "method_lambda.h"
#include "method_ptr_const.h"
#include "aware_return_n_target_const.h"

namespace rtl::dispatch
{
	template<class record_t, class return_t, class ...signature_t>
	void method_ptr<const record_t, return_t, signature_t...>::init_lambda()
	{
        if constexpr (fn_void_v == fn_void::yes)
        {
            {
                //const auto& fn = aware_return_n_target<const record_t, return_t, signature_t...>::e_return_a_target_fnv();
                //m_erased_return.set_hop(fn);
            } {
                //const auto& fn = aware_return_n_target<const record_t, return_t, signature_t...>::e_target_a_return_fnv();
                //m_erased_target.set_hop(fn);
            }
        }
        else
        {
            {
                //const auto& fn = aware_return_n_target<const record_t, return_t, signature_t...>::e_return_a_target_fnr();
                //m_erased_return.set_hop(fn);
            } {
                //const auto& fn = aware_return_n_target<const record_t, return_t, signature_t...>::e_target_a_return_fnr();
                //m_erased_target.set_hop(fn);
            }
        }

        functor::m_lambdas = std::vector<lambda*>(2);
        functor::m_lambdas[index::erased_return] = (&m_erased_return);
        functor::m_lambdas[index::erased_target] = (&m_erased_target);
	}
}