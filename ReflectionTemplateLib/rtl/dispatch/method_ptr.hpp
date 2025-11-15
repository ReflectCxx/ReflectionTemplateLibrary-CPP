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

namespace rtl::dispatch
{
	template<class return_t, class ...signature_t>
	void rtl::dispatch::function_ptr<return_t, signature_t...>::init_erased_fn()
	{
		erased_fn = func_et();
		m_lambdas.push_back(&std::get<func_et>(erased_fn));
	}

	template<class return_t, class ...signature_t>
	void function_ptr<return_t, signature_t...>::init_erased_ctor()
	{
		erased_fn = ctor_et();
		m_lambdas.push_back(&std::get<ctor_et>(erased_fn));
	}
}