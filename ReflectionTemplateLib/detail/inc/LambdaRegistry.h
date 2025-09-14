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

#include "LambdaBridge.h"

#include <vector>
#include <functional>

#include "Constants.h"
#include "FunctorRegistry.h"

namespace rtl {

	class RObject;
	struct Return;
}


namespace rtl::detail
{
	class lambda_hop { };
}


namespace rtl::detail
{
	template<class ...signature_ts>
	class lambda_registry : public lambda_hop
	{
		using lambda_t = std::function<Return(signature_ts...)>;

		std::vector<lambda_t> m_lambdas;

		std::vector<functor_hop*> m_functors;

	public:

		GETTER_CREF(std::vector<lambda_t>, , m_lambdas)

		void push(const lambda_t& pLambda) {
			m_lambdas.push_back(pLambda);
		}

		Return operator()(std::size_t index, signature_ts&&...params)
		{
			return m_lambdas[index](m_functors[index], index, std::forward<signature_ts>(params)...);
		}
	};



	template<class ...signature_ts>
	class const_functors : public lambda_hop
	{
		using lambda_t = std::function <Return(const RObject&, signature_ts...)>;

		std::vector<lambda_t> m_lambdas;

	public:

		GETTER_CREF(std::vector<lambda_t>, , m_lambdas)

		void pushBack(const lambda_t& pLambda) {
			m_lambdas.push_back(pLambda);
		}
	};


	template<class ...signature_ts>
	class nonconst_functors : public lambda_hop
	{
		using lambda_t =  std::function <Return(const RObject&, signature_ts...)>;
		
		std::vector<lambda_t> m_lambdas;

	public:

		GETTER_CREF(std::vector<lambda_t>, , m_lambdas)

		void pushBack(const lambda_t& pLambda) {
			m_lambdas.push_back(pLambda);
		}
	};
}