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

#include "function_ptr.h"
#include "aware_return.h"
#include "aware_constructor.h"

namespace rtl::dispatch
{
	template<class return_t, class ...signature_t>
	template<class record_t>
	void function_ptr<return_t, signature_t...>::init_lambda_ctor()
	{
		m_lambda = ctor_t();
		ctor_t& fn = m_lambda.template emplace<ctor_t>();

		fn.set_hop(aware_constructor<record_t, signature_t...>::get_allocator());

		functor::m_lambdas = std::vector<lambda*>(1);
		functor::m_lambdas[index::erased_ctor] = (&fn);
	}


	template<class return_t, class ...signature_t>
	void rtl::dispatch::function_ptr<return_t, signature_t...>::init_lambda()
	{
		m_lambda = func_t();
		func_t& fn = m_lambda.template emplace<func_t>();

		if constexpr (fn_void_v == fn_void::yes) {
			fn.set_hop(aware_return<return_t, signature_t...>::get_lambda_void());
		}
		else {
			fn.set_hop(aware_return<return_t, signature_t...>::get_lambda_any_return());
		}

		functor::m_lambdas = std::vector<lambda*>(1);
		functor::m_lambdas[index::erased_return] = (&fn);
	}
}
