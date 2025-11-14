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

#include <variant>

#include "fn_meta.h"

namespace rtl::dispatch
{
	template<class record_t, class...args_t>
	struct method_er_return : fn_lambda
	{
		using lambda_vt = std::function<void(const fn_meta&, const record_t&, traits::normal_sign_t<args_t>...)>;
		using lambda_rt = std::function<std::any(const fn_meta&, const record_t&, traits::normal_sign_t<args_t>...)>;

		const lambda_vt& get_method_vhop() const {
			return std::get<lambda_vt>(m_lambda);
		}

		const lambda_rt& get_method_rhop() const {
			return std::get<lambda_rt>(m_lambda);
		}

	private:

		std::variant<lambda_vt, lambda_rt> m_lambda;

		void set_method_vhop(const lambda_vt& lambda) {
			m_lambda = lambda;
		}

		void set_method_rhop(const lambda_rt& lambda) {
			m_lambda = lambda;
		}
	};
}


namespace rtl::dispatch
{
	template<class return_t, class...args_t>
	struct method_er_target : fn_lambda
	{
		using lambda_vt = std::function<void(const fn_meta&, const rtl::RObject&, traits::normal_sign_t<args_t>...)>;
		using lambda_rt = std::function<return_t(const fn_meta&, const rtl::RObject&, traits::normal_sign_t<args_t>...)>;

		const lambda_vt& get_method_vhop() const {
			return std::get<lambda_vt>(m_lambda);
		}

		const lambda_rt& get_method_rhop() const {
			return std::get<lambda_rt>(m_lambda);
		}

	private:

		std::variant<lambda_vt, lambda_rt> m_lambda;

		void set_method_vhop(const lambda_vt& lambda) {
			m_lambda = lambda;
		}

		void set_method_rhop(const lambda_rt& lambda) {
			m_lambda = lambda;
		}
	};
}