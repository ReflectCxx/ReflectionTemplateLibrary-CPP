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

#include <inc/type_meta.h>
#include <dispatch/cache_method_ptr.h>
#include <dispatch/cache_function_ptr.h>
#include <dispatch/cache_method_ptr_const.h>

namespace rtl
{
	template<class return_t, class ...signature_t>
	inline type_meta type_meta::add_function(return_t(*p_fptr)(signature_t...), 
											 traits::uid_t p_record_uid, detail::member p_member_kind)
	{
		auto& fc = cache::function_ptr<return_t, signature_t...>::instance();
		auto& functor = fc.push(p_fptr, p_record_uid, p_member_kind);
		return type_meta(functor);
	}


	template<class record_t, class return_t, class ...signature_t>
	inline type_meta type_meta::add_method(return_t(record_t::* p_fptr)(signature_t...))
	{
		auto& fc = cache::method_ptr<record_t, return_t, signature_t...>::instance();
		auto& functor = fc.push(p_fptr);
		return type_meta(functor);
	}


	template<class record_t, class return_t, class ...signature_t>
	inline type_meta type_meta::add_method(return_t(record_t::* p_fptr)(signature_t...) const)
	{
		auto& fc = cache::method_ptr<const record_t, return_t, signature_t...>::instance();		
		auto& functor = fc.push(p_fptr);
		return type_meta(functor);
	}


	template<detail::member mem_kind, class record_t, class return_t, class ...signature_t>
	inline type_meta type_meta::add_constructor()
	{
		auto& fc = cache::function_ptr<return_t, signature_t...>::instance();
		auto& functor = fc.template push_ctor<mem_kind, record_t>(traits::uid<record_t>::value);
		return type_meta(functor);
	}
}