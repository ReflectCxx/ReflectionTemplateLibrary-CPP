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
#include "fn_signature.h"
#include "aware_return.h"
#include "aware_constructor.h"

namespace rtl::dispatch
{
	template<class return_t, class ...signature_t>
	void rtl::dispatch::function_ptr<return_t, signature_t...>::init_lambda()
	{
		erased_fn = func_t();
		func_t& fn = std::get<func_t>(erased_fn);

		if constexpr (std::is_void_v<return_t>) {
		//	fn.set_method_vhop(aware_return<return_t, signature_t..>::get_lambda_void())
		}
		else {
		//	fn.set_method_rhop(aware_return<return_t, signature_t..>::get_lambda_any_return())
		}
		functor::m_lambdas = std::vector<lambda*>(1);
		functor::m_lambdas[index::erased_return] = (&fn);
	}

	template<class return_t, class ...signature_t>
	template<class record_t>
	void function_ptr<return_t, signature_t...>::init_lambda_ctor()
	{
		erased_fn = ctor_t();
		ctor_t& fn = std::get<ctor_t>(erased_fn);

		fn.set_ctor_hop(aware_constructor<record_t, signature_t...>::get_allocator());

		functor::m_lambdas = std::vector<lambda*>(1);
		functor::m_lambdas[index::erased_ctor] = (&fn);
	}
}