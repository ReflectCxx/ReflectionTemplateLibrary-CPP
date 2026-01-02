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

#include <string>
#include <vector>
#include <optional>

#include "functor.h"

namespace rtl
{
	struct type_meta
	{
		type_meta(const dispatch::functor& p_functor)
			: m_functor(p_functor)
		{ }

		type_meta() = default;
		type_meta(type_meta&&) = default;
		type_meta(const type_meta&) = default;
		type_meta& operator=(type_meta&&) = default;
		type_meta& operator=(const type_meta&) = default;

		GETTER_BOOL(_empty, !m_functor.has_value())
		GETTER_BOOL(_void, m_functor->get().m_is_void)
		GETTER_BOOL(_any_arg_ncref, m_functor->get().m_is_any_arg_ncref)

		GETTER(std::string, _record_str, m_functor->get().m_record_str)
		GETTER(std::string, _return_str, m_functor->get().m_return_str)
		GETTER_CREF(std::vector<std::size_t>, _args_id_arr, m_functor->get().m_args_type_ids)
		
		GETTER(traits::uid_t, _return_id, m_functor->get().m_return_id)
		GETTER(traits::uid_t, _record_id, m_functor->get().m_record_id)
		GETTER(traits::uid_t, _normal_args_id, m_functor->get().m_normal_args_id)
		GETTER(traits::uid_t, _strict_args_id, m_functor->get().m_strict_args_id)
		
		GETTER(detail::member, _member_kind, m_functor->get().m_member_kind)
		
		GETTER_CREF(dispatch::functor, _functor, m_functor->get())

		template<class return_t, class ...signature_t>
		static type_meta add_function(return_t(*p_fptr)(signature_t...),
									  traits::uid_t p_record_uid, detail::member p_member_kind);

		template<class record_t, class return_t, class ...signature_t>
		static type_meta add_method(return_t(record_t::* p_fptr)(signature_t...), std::size_t p_index);

		template<class record_t, class return_t, class ...signature_t>
		static type_meta add_method(return_t(record_t::* p_fptr)(signature_t...) const, std::size_t p_index);

		template<detail::member mem_kind, class record_t, class return_t, class ...signature_t>
		static type_meta add_constructor();

	private:

		using functor_t = std::optional<std::reference_wrapper<const dispatch::functor>>;

		functor_t m_functor = std::nullopt;

		constexpr void set_record_str(const std::string& p_record_str) {
			m_functor->get().m_record_str = p_record_str;
		}

		constexpr void set_namespace_str(const std::string& p_ns_str) {
			m_functor->get().m_namespace_str = p_ns_str;
		}

		friend detail::CxxReflection;
	};
}