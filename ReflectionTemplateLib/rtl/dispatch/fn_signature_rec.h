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
	template<class record_t, class...args_t>
	struct fn_signature_target : fn_lambda
	{
		using lambda_vt = std::function<void(const fn_meta&, const record_t&, traits::normal_sign_t<args_t>...)>;
		using lambda_rt = std::function<std::any(const fn_meta&, const record_t&, traits::normal_sign_t<args_t>...)>;

		constexpr lambda_vt get_method_vhop() const {
			return vhop;
		}

		constexpr lambda_rt get_method_rhop() const {
			return rhop;
		}

	private:

		lambda_vt vhop = nullptr;
		lambda_rt rhop = nullptr;

		constexpr void set_method_vhop(const lambda_vt& lambda) const {
			vhop = lambda;
		}

		constexpr void set_method_rhop(const lambda_rt& lambda) const {
			rhop = lambda;
		}
	};
}


namespace rtl::dispatch
{
	template<class return_t, class...args_t>
	struct fn_signature_return : fn_lambda
	{
		using lambda_vt = std::function<void(const fn_meta&, const rtl::RObject&, traits::normal_sign_t<args_t>...)>;
		using lambda_rt = std::function<return_t(const fn_meta&, const rtl::RObject&, traits::normal_sign_t<args_t>...)>;

		constexpr lambda_vt get_method_vhop() const {
			return vhop;
		}

		constexpr lambda_rt get_method_rhop() const {
			return rhop;
		}

	private:

		lambda_vt vhop = nullptr;
		lambda_rt rhop = nullptr;

		constexpr void set_method_vhop(const lambda_vt& lambda) const {
			vhop = lambda;
		}

		constexpr void set_method_rhop(const lambda_rt& lambda) const {
			rhop = lambda;
		}
	};
}