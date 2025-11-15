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
#include "rtl_forward_decls.h"

namespace rtl::dispatch
{
	template<class...args_t>
	struct function_lambda<erase::t_ctor, args_t...> : lambda
	{
		using lambda_t = std::function<Return(alloc, traits::normal_sign_t<args_t>...)>;

		const lambda_t& get_ctor_hop() const {
			return m_lambda;
		}

	private:

		lambda_t m_lambda;

		void set_ctor_hop(const lambda_t& lambda) {
			m_lambda = lambda;
		}

		template<class, class ...>
		friend struct dispatch::function_ptr;
	};
}


namespace rtl::dispatch
{
	template<class...args_t>
	struct function_lambda<erase::t_return, args_t...> : lambda
	{
		using lambda_vt = std::function<void(const functor&, traits::normal_sign_t<args_t>...)>;
		using lambda_rt = std::function<std::any(const functor&, traits::normal_sign_t<args_t>...)>;

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

		template<class, class ...>
		friend struct dispatch::function_ptr;
	};
}