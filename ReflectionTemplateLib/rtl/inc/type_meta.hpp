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

#include "type_meta.h"

#include "lambda_base.h"
#include "erasure_base.h"

#include "cache_method_ptr.h"
#include "cache_function_ptr.h"
#include "cache_method_ptr_const.h"

#include "cache_lambda_method.h"
#include "cache_lambda_function.h"

#include "aware_constructor.h"

namespace rtl
{
	template<class ...args_t>
	inline constexpr const type_meta::lambda_fn_t<args_t...>* type_meta::get_lambda_function(std::size_t p_argsId) const
	{
		return m_functor->get().m_lambda->to_function<args_t...>(p_argsId);
	}

	template<class record_t, class ...args_t>
	inline constexpr const type_meta::lambda_mth_t<record_t, args_t...>* type_meta::get_lambda_method(std::size_t p_recordId, std::size_t p_argsId) const
	{
		return m_functor->get().m_lambda->to_method<record_t, args_t...>(p_recordId, p_argsId);
	}

	template<class return_t, class ...signature_t>
	inline type_meta type_meta::add_function(return_t(*p_fptr)(signature_t...), traits::uid_t p_record_uid, detail::member p_member_kind, std::size_t p_index)
	{
		auto& fc = cache::function_ptr<return_t, signature_t...>::instance();
		auto& lc = cache::lambda_function<return_t, signature_t...>::instance();

		auto& functor = fc.push(p_fptr, p_record_uid, p_member_kind, p_index);
		auto [lambda, elambda] = lc.push(functor);
		
		functor.set_lambda(lambda);
		functor.set_erasure(elambda);

		return type_meta(functor);
	}

	template<class record_t, class return_t, class ...signature_t>
	inline type_meta type_meta::add_method(return_t(record_t::* p_fptr)(signature_t...), std::size_t p_index)
	{
		auto& fc = cache::method_ptr<record_t, return_t, signature_t...>::instance();
		auto& lc = cache::lambda_method<record_t, return_t, signature_t...>::instance();

		auto& functor = fc.push(p_fptr, p_index);
		auto [lambda, elambda] = lc.push(functor);

		functor.set_lambda(lambda);
		functor.set_erasure(elambda);

		return type_meta(functor);
	}

	template<class record_t, class return_t, class ...signature_t>
	inline type_meta type_meta::add_method(return_t(record_t::* p_fptr)(signature_t...) const, std::size_t p_index)
	{
		auto& fc = cache::method_ptr<const record_t, return_t, signature_t...>::instance();
		auto& lc = cache::lambda_method<record_t, return_t, signature_t...>::instance();

		auto& functor = fc.push(p_fptr, p_index);
		auto [lambda, elambda] = lc.push(functor);
		
		functor.set_lambda(lambda);
		functor.set_erasure(elambda);

		return type_meta(functor);
	}


	template<class record_t, class ...signature_t>
	inline type_meta type_meta::add_ctor()
	{
		if constexpr (sizeof...(signature_t) == 0)
		{
			auto& fc = cache::function_ptr<Return, signature_t...>::instance();
			auto& lc = cache::lambda_function<Return, signature_t...>::instance();

			auto fptr = &(dispatch::aware_constructor<record_t>::allocator);

			//auto& functor = fc.push(fptr, p_record_uid, p_member_kind, p_index);
			//auto [lambda, elambda] = lc.push(functor);

			//functor.set_lambda(lambda);
			//functor.set_erasure(elambda);
		}

		return type_meta();
	}
}