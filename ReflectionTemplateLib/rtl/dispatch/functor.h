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

#include "dispatch_interface.h"

namespace rtl::dispatch
{
	template<class return_t, class ...signature_ts>
	struct functor: public functor_hop
	{
		using fptr_t = return_t(*)(signature_ts...);

		fptr_t get() const
		{
			return m_functor;
		}

		functor(fptr_t fptr) :m_functor(fptr)
		{
			m_returnId = detail::TypeId<return_t>::get();
			m_signatureId = detail::TypeId<std::tuple<signature_ts...>>::get();
		}

	private:

		const fptr_t m_functor;
	};
}