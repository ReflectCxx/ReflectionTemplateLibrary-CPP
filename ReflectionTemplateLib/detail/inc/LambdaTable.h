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

#include <vector>
#include <functional>

#include "Constants.h"

namespace rtl {

	class RObject;
	struct Return;
}

namespace rtl::detail
{
	class lambda_table { };
}


namespace rtl::detail
{
	template<class ...signature_ts>
	class functors : public lambda_table
	{
		using lambda_t = std::function <Return(signature_ts...)>;

		std::vector<lambda_t> m_lambdaTable;

	public:

		GETTER_CREF(std::vector<lambda_t>, , m_lambdaTable)

		void pushBack(const lambda_t& pLambda) {
			m_lambdaTable.push_back(pLambda);
		}
	};


	template<class ...signature_ts>
	class const_functors : public lambda_table
	{
		using lambda_t = std::function <Return(const RObject&, signature_ts...)>;

		std::vector<lambda_t> m_lambdaTable;

	public:

		GETTER_CREF(std::vector<lambda_t>, , m_lambdaTable)

		void pushBack(const lambda_t& pLambda) {
			m_lambdaTable.push_back(pLambda);
		}
	};


	template<class ...signature_ts>
	class nonconst_functors : public lambda_table
	{
		using lambda_t =  std::function <Return(const RObject&, signature_ts...)>;
		
		std::vector<lambda_t> m_lambdaTable;

	public:

		GETTER_CREF(std::vector<lambda_t>, , m_lambdaTable)

		void pushBack(const lambda_t& pLambda) {
			m_lambdaTable.push_back(pLambda);
		}
	};
}