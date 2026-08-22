/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#pragma once

#include <variant>
#include <dispatch/functor.h>
#include <dispatch/function_lambda.h>

namespace rtl::dispatch
{
	template<class return_t, class ...signature_t>
	struct function_ptr: functor
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
			
			m_signature_str = detail::TypeId<return_t>::toString() + " (" +
                              detail::TypeId<signature_t...>::toString() + ")";
		}

	private:

		using ctor_t = function_lambda<erase::t_ctor, signature_t...>;
		using func_t = function_lambda<erase::t_return, signature_t...>;

		functor_t m_functor = nullptr;
		std::variant<ctor_t, func_t> m_lambda;

		void init_lambda();

		template<detail::member, class record_t>
		void init_lambda();

		template<class, class ...>
		friend struct cache::function_ptr;
	};
}