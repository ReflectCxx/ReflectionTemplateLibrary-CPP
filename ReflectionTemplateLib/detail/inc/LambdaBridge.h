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

#include "FunctorId.h"
#include "FunctorRegistry.h"

namespace rtl {
	struct Return;
}

namespace rtl::detail::bridge
{
	template<class ...signature_ts>
	struct lambda_def
	{
		template<class return_t>
		static auto get() 
		{
			return [](const FunctorId& functorId, signature_ts&&...params)
			{

			};
		}
	};
}