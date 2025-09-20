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

#include "functor.h"

namespace rtl::dispatch
{
	template<class record_t, class return_t, class ...signature_ts>
	struct const_method_ptr : public functor
	{
		using functor_t = return_t(record_t::*)(signature_ts...) const;

		constexpr functor_t get() const
		{
			return m_functor;
		}

		constexpr bool is_same(functor_t fptr) const
		{
			return (fptr == m_functor);
		}

		const_method_ptr(functor_t fptr) :m_functor(fptr)
		{
			m_returnId = detail::TypeId<traits::raw_t<return_t>>::get();
			m_signatureId = detail::TypeId<std::tuple<traits::raw_t<signature_ts>...>>::get();
		}

	private:

		const functor_t m_functor;
	};
}