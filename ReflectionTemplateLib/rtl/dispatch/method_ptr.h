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
	template<class record_t, class ...signature_ts>
	struct method_ptr : public functor
	{
		using voidfn_t = void(record_t::*)(signature_ts...);

		template<class return_t>
		decltype(auto) get(std::size_t returnId) const
		{
			using fptr_t = return_t(record_t::*)(signature_ts...);
			if (returnId == m_returnId)
			{
				return reinterpret_cast<fptr_t>(m_functor);
			}
			return static_cast<fptr_t>(nullptr);
		}

		template<class return_t>
		bool is_same(return_t(record_t::* fptr)(signature_ts...)) const
		{
			return (m_functor == reinterpret_cast<voidfn_t>(fptr));
		}

		method_ptr(voidfn_t fptr, std::size_t returnId) :m_functor(fptr)
		{
			m_returnId = returnId;
			m_signatureId = detail::TypeId<std::tuple<signature_ts...>>::get();
		}

	private:

		const voidfn_t m_functor;
	};
}