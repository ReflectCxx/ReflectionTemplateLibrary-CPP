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
	struct method_ptr<const record_t, return_t, signature_t...> : public functor
	{
		using functor_t = return_t(record_t::*)(signature_t...) const;

		constexpr auto f_ptr() const {
			return m_functor;
		}

		constexpr bool is_same(functor_t fptr) const {
			return (fptr == m_functor);
		}

		method_ptr(functor_t fptr) :m_functor(fptr)
		{
			m_qualifier = detail::methodQ::Const;

			m_returnId = traits::uid<return_t>::value;
			m_is_void = (m_returnId == traits::uid<void>::value);
			m_recordId = traits::uid<const record_t>::value;

			m_is_any_ncref = (traits::is_nonconst_ref_v<signature_t> || ...);
			m_normal_signId = traits::uid<traits::normal_sign_id_t<signature_t...>>::value;
			m_strict_signId = traits::uid<traits::strict_sign_id_t<signature_t...>>::value;

			m_returnStr = detail::TypeId<return_t>::toString();
			m_recordStr = detail::TypeId<record_t>::toString();
			m_signatureStr = detail::TypeId<signature_t...>::toString();
		}

	private:

		const functor_t m_functor;
	};
}