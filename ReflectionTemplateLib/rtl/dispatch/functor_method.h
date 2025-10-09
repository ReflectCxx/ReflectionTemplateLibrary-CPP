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
	template<class record_t, class return_t, class ...signature_t>
	struct method_ptr : public functor
	{
		using functor_t = return_t(record_t::*)(signature_t...);

		[[nodiscard]] constexpr auto f_ptr() const
		{
			return m_functor;
		}

		constexpr bool is_same(functor_t fptr) const
		{
			return (fptr == m_functor);
		}

		method_ptr(functor_t fptr) :m_functor(fptr)
		{
			m_qualifier = detail::methodQ::NonConst;
			
			m_recordId = detail::TypeId<record_t>::get();
			m_returnId = detail::TypeId<return_t>::get();

			m_is_any_ncref = (traits::is_nonconst_ref_v<signature_t> || ...);
			m_normal_signId = detail::TypeId<traits::normal_sign_id_t<signature_t...>>::get();
			m_strict_signId = detail::TypeId<traits::strict_sign_id_t<signature_t...>>::get();

			m_returnStr = detail::TypeId<return_t>::toString();
			m_recordStr = detail::TypeId<record_t>::toString();
			m_signatureStr = detail::TypeId<signature_t...>::toString();
		}

	private:

		const functor_t m_functor;
	};
}