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

#include "functor.h"

namespace rtl::dispatch
{
	template<class return_t, class ...signature_t>
	struct function_ptr: public functor
	{
		using functor_t = return_t(*)(signature_t...);

		constexpr auto f_ptr() const {
			return m_functor;
		}

		constexpr bool is_same(functor_t fptr) const {
			return (fptr == m_functor);
		}

		function_ptr(functor_t fptr, traits::uid_t p_record_uid, detail::member member_kind) 
			: m_functor(fptr)
		{
			m_record_id = p_record_uid;
			m_is_void = std::is_void_v<return_t>;
			m_return_id = traits::uid<return_t>::value;
			
			m_member_kind = member_kind;
			m_is_any_arg_ncref = (traits::is_nonconst_ref_v<signature_t> || ...);
			m_normal_args_id = traits::uid<traits::normal_sign_id_t<signature_t...>>::value;
			m_strict_args_id = traits::uid<traits::strict_sign_id_t<signature_t...>>::value;
			
			m_return_str = detail::TypeId<return_t>::toString();
			m_signature_str = detail::TypeId<signature_t...>::toString();
		}

	private:

		const functor_t m_functor;
	};
}