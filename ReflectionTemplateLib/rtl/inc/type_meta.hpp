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

#include "cache_method_ptr.h"
#include "cache_function_ptr.h"
#include "cache_method_ptr_const.h"

#include "cache_lambda_method.h"
#include "cache_lambda_function.h"

namespace rtl
{
	template<class return_t, class ...signature_t>
	inline type_meta type_meta::add_function(return_t(*p_fptr)(signature_t...), traits::uid_t p_record_uid, detail::member p_member_kind, std::size_t p_index)
	{
		auto& fc = cache::function_ptr<return_t, signature_t...>::instance();
		auto& lc = cache::lambda_function<return_t, signature_t...>::instance();

		auto& functor = fc.push(p_fptr, p_record_uid, p_member_kind, p_index);
		auto lambda = lc.push(functor);
		
		functor.set_lambda(lambda);

		return type_meta(functor);
	}


	template<class record_t, class return_t, class ...signature_t>
	inline type_meta type_meta::add_method(return_t(record_t::* p_fptr)(signature_t...), std::size_t p_index)
	{
		auto& fc = cache::method_ptr<record_t, return_t, signature_t...>::instance();
		auto& lc = cache::lambda_method<record_t, return_t, signature_t...>::instance();

		auto& functor = fc.push(p_fptr, p_index);
		auto lambda = lc.push(functor);

		functor.set_lambda(lambda);
		
		return type_meta(functor);
	}


	template<class record_t, class return_t, class ...signature_t>
	inline type_meta type_meta::add_method(return_t(record_t::* p_fptr)(signature_t...) const, std::size_t p_index)
	{
		auto& fc = cache::method_ptr<const record_t, return_t, signature_t...>::instance();
		auto& lc = cache::lambda_method<record_t, return_t, signature_t...>::instance();

		auto& functor = fc.push(p_fptr, p_index);
		auto lambda = lc.push(functor);
		
		functor.set_lambda(lambda);

		return type_meta(functor);
	}


	template<class record_t, class ...signature_t>
	inline type_meta type_meta::add_constructor(std::size_t p_index)
	{
		if constexpr (sizeof...(signature_t) == 0) {
			auto& fc = cache::function_ptr<Return, alloc>::instance();
			auto& functor = fc.template push_ctor<detail::member::DefaultCtor, record_t>(traits::uid<record_t>::value, p_index);
			return type_meta(functor);
		}
		else {
			auto& fc = cache::function_ptr<Return, signature_t...>::instance();
			auto& functor = fc.template push_ctor<detail::member::UserCtor, record_t>(traits::uid<record_t>::value, p_index);
			return type_meta(functor);
		}
	}
}