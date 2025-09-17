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

#include <tuple>

#include "dispatch_interface.h"

namespace rtl::dispatch
{
	template<class record_t, class return_t, class ...signature_ts>
	struct functor_nonconst : public functor_hop
	{
		using fptr_t = return_t(record_t::*)(signature_ts...);

		fptr_t get() const
		{
			return m_functor;
		}

		return_t operator()(record_t& pTarget, signature_ts&&...params) const
		{
			return (pTarget.*m_functor)(std::forward<signature_ts>(params)...);
		}

		functor_nonconst(fptr_t fptr) :m_functor(fptr)
		{
			m_returnId = detail::TypeId<return_t>::get();
			m_signatureId = detail::TypeId<std::tuple<signature_ts...>>::get();
		}

	private:

		fptr_t m_functor;
	};
}