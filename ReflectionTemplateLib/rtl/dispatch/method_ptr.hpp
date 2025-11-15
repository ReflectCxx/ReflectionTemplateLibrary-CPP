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

#include "method_ptr.h"
#include "fn_signature_rec.h"
#include "aware_return_n_target.h"

namespace rtl::dispatch
{
	template<class record_t, class return_t, class ...signature_t>
	void method_ptr<record_t, return_t, signature_t...>::init_lambda()
	{
		//if constexpr (std::is_void_v<return_t>) {
		//	m_erased_return.
		//}
		//else {
		//	//	fn.set_method_rhop(aware_return<return_t, signature_t..>::get_lambda_any_return())
		//}

		functor::m_lambdas = std::vector<lambda*>(2);
		functor::m_lambdas[index::erased_return] = (&m_erased_return);
		functor::m_lambdas[index::erased_target] = (&m_erased_target);
	}
}