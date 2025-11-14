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
#include "fn_signature_rec.h"

namespace rtl::dispatch
{
	template<class record_t, class return_t, class ...signature_t>
	struct method_ptr : functor//, fn_meta
	{
		using functor_t = return_t(record_t::*)(signature_t...);

		constexpr auto f_ptr() const {
			return m_functor;
		}

		constexpr bool is_same(functor_t fptr) const {
			return (fptr == m_functor);
		}

		method_ptr(functor_t fptr): m_functor(fptr)
		{
			m_member_kind = detail::member::NonConst;
			
			m_is_void = std::is_void_v<return_t>;
			m_return_id = traits::uid<return_t>::value;
			m_record_id = traits::uid<record_t>::value;

			m_is_any_arg_ncref = (traits::is_nonconst_ref_v<signature_t> || ...);
			m_normal_args_id = traits::uid<traits::normal_sign_id_t<signature_t...>>::value;
			m_strict_args_id = traits::uid<traits::strict_sign_id_t<signature_t...>>::value;

			m_return_str = detail::TypeId<return_t>::toString();
			m_record_str = detail::TypeId<record_t>::toString();
			m_signature_str = detail::TypeId<signature_t...>::toString();
		}

	private:

		const functor_t m_functor;

		method_er_return<record_t, signature_t...> m_erased_target;
		method_er_target<return_t, signature_t...> m_erased_return;
	};
}