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

#include "functor.h"
#include "erasure_base.h"

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

		GETTER(std::string, _record_str, m_functor->get().m_recordStr)
		GETTER(std::string, _return_str, m_functor->get().m_returnStr)
		GETTER_CREF(std::vector<std::size_t>, _args_id_arr, m_functor->get().m_argumentsId)
		
		GETTER(traits::uid_t, _record_id, m_functor->get().m_recordId)
		GETTER(traits::uid_t, _normal_args_id, m_functor->get().m_normal_signId)
		GETTER(traits::uid_t, _strict_args_id, m_functor->get().m_strict_signId)
		
		GETTER(detail::member, _method_qual, m_functor->get().m_member_kind)
		
		GETTER_CREF(dispatch::lambda_base, _lambda, *(m_functor->get().m_lambda))
		GETTER_CREF(dispatch::erasure_base, _erasure_base, *(m_functor->get().m_erasure))

		template<class return_t, class ...signature_t>
		static type_meta add_function(return_t(*pFunctor)(signature_t...), detail::member pMemberType, std::size_t p_index);

		template<class record_t, class return_t, class ...signature_t>
		static type_meta add_method(return_t(record_t::* pFunctor)(signature_t...), std::size_t p_index);

		template<class record_t, class return_t, class ...signature_t>
		static type_meta add_method(return_t(record_t::* pFunctor)(signature_t...) const, std::size_t p_index);

		template<class ..._signature>
		using lambda_fn_t = dispatch::lambda_function<_signature...>;

		template<class rec_t, class ..._signature>
		using lambda_mth_t = dispatch::lambda_method<rec_t, _signature...>;

		template<class ...args_t>
		constexpr const lambda_fn_t<args_t...>* get_lambda_function(std::size_t p_argsId = 0) const;

		template<class record_t, class ...args_t>
		constexpr const lambda_mth_t<record_t, args_t...>* get_lambda_method(std::size_t p_recordId = 0, std::size_t p_argsId = 0) const;

	private:

		using functor_t = std::optional<std::reference_wrapper<const dispatch::functor>>;

		functor_t m_functor = std::nullopt;
	};
}