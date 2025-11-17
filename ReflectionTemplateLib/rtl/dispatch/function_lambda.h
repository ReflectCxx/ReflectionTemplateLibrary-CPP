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

#include "rtl_forward_decls.h"

namespace rtl::dispatch
{
	template<class...args_t>
	struct function_lambda<fn_void::no, erase::t_ctor, args_t...> : lambda
	{
		// ditch all std::functions and use fn-pointer directly - what??? Yes!
		using lambda_t = Return(*)(alloc, traits::normal_sign_t<args_t>&&...);

		const lambda_t& get_hop() const {
			return m_lambda;
		}

	private:

		void set_hop(const lambda_t& lambda) {
			m_lambda = lambda;
		}

		lambda_t m_lambda;

		template<class, class ...>
		friend struct dispatch::function_ptr;
	};
}


namespace rtl::dispatch
{
	template<class...args_t>
	struct function_lambda<fn_void::yes, erase::t_return, args_t...> : lambda
	{
		using lambda_t = std::function<void(const lambda_base&, traits::normal_sign_t<args_t>...)>;

		const lambda_t& get_hop() const {
			return m_lambda;
		}

	private:

		void set_hop(const lambda_t& lambda) {
			m_lambda = lambda;
		}

		lambda_t m_lambda;

		template<class, class ...>
		friend struct dispatch::function_ptr;
	};
}


namespace rtl::dispatch
{
	template<class...args_t>
	struct function_lambda<fn_void::no, erase::t_return, args_t...> : lambda
	{
		using lambda_t = std::function<std::any(const lambda_base&, traits::normal_sign_t<args_t>...)>;

		const lambda_t& get_hop() const {
			return m_lambda;
		}

	private:

		void set_hop(const lambda_t& lambda) {
			m_lambda = lambda;
		}

		lambda_t m_lambda;

		template<class, class ...>
		friend struct dispatch::function_ptr;
	};
}


namespace rtl::dispatch
{
	template<class...args_t>
	struct function_lambda<fn_void::yes, erase::t_method, args_t...> : lambda
	{
		using lambda_t = std::function<void(const lambda_base&, const RObject&, traits::normal_sign_t<args_t>...)>;

		const lambda_t& get_hop() const {
			return m_lambda;
		}

	private:

		void set_hop(const lambda_t& lambda) {
			m_lambda = lambda;
		}

		lambda_t m_lambda;

		template<class, class, class ...>
		friend struct dispatch::method_ptr;
	};
}


namespace rtl::dispatch
{
	template<class...args_t>
	struct function_lambda<fn_void::no, erase::t_method, args_t...> : lambda
	{
		using lambda_t = std::function<std::any(const lambda_base&, const RObject&, traits::normal_sign_t<args_t>...)>;

		const lambda_t& get_hop() const {
			return m_lambda;
		}

	private:

		void set_hop(const lambda_t& lambda) {
			m_lambda = lambda;
		}

		lambda_t m_lambda;

		template<class, class, class ...>
		friend struct dispatch::method_ptr;
	};
}