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

#include "fn_meta.h"

namespace rtl::dispatch
{
	template<class...args_t>
	struct fn_signature : fn_meta
	{
		using lambda_vt = std::function<void(const fn_meta&, traits::normal_sign_t<args_t>...)>;

		using lambda_rt = std::function<std::any(const fn_meta&, traits::normal_sign_t<args_t>...)>;

		using lambda_ctor_t = std::function<Return(alloc, traits::normal_sign_t<args_t>...)>;

		using lambda_mth_vt = std::function<void(const lambda_base&, const RObject&, traits::normal_sign_t<args_t>...)>;

		using lambda_mth_rt = std::function<std::any(const lambda_base&, const RObject&, traits::normal_sign_t<args_t>...)>;

		constexpr lambda_vt get_function_vhop() const {
			return fn_vhop;
		}

		constexpr lambda_rt get_function_rhop() const {
			return fn_rhop;
		}
		
		constexpr lambda_ctor_t get_ctor_hop() const {
			return ctor_hop;
		}

		constexpr lambda_mth_vt get_method_vhop() const {
			return mth_vhop;
		}

		constexpr lambda_mth_rt get_method_rhop() const {
			return mth_rhop;
		}

	private:

		lambda_vt fn_vhop = nullptr;
		lambda_rt fn_rhop = nullptr;

		lambda_mth_vt mth_vhop = nullptr;
		lambda_mth_rt mth_rhop = nullptr;
		lambda_ctor_t ctor_hop = nullptr;

		fn_lambda* erased_return = nullptr;
		fn_lambda* erased_target = nullptr;

		constexpr void set_function_vhop(const lambda_vt& lambda) const {
			fn_vhop = lambda;
		}

		constexpr void set_function_rhop(const lambda_rt& lambda) const {
			fn_rhop = lambda;
		}

		constexpr void set_ctor_hop(const lambda_ctor_t& lambda) const {
			ctor_hop = lambda;
		}

		constexpr void set_method_vhop(const lambda_mth_vt& lambda) const {
			mth_vhop = lambda;
		}

		constexpr void set_method_rhop(const lambda_mth_rt& lambda) const {
			mth_rhop = lambda;
		}
	};
}