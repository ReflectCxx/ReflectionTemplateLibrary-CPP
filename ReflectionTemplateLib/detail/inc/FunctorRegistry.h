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

namespace rtl {
	struct Return;
}


namespace rtl::detail
{
	class functor_hop {};
}


namespace rtl::detail
{
	template<class return_t, class ...signature_ts>
	class functor_registry : public functor_hop
	{
		using functor_t = return_t(*)(signature_ts...);

		std::vector<std::pair<functor_t, std::size_t>> m_functors;

	public:

		functor_t operator[](std::size_t index) {
			return m_functors[index].first;
		}

		void push(functor_t fptr, std::size_t lambda_index) {
			m_functors.emplace_back(fptr, lambda_index);
		}

		std::size_t find(functor_t fptr)
		{
			//linear search, efficient for small set.
			for (const auto& itr : m_functors) {
				if (itr.first == fptr) {
					//functor already registered, return its 'index'.
					return itr.second;
				}
			}
			//functor is not already registered, return '-1'.
			return rtl::index_none;
		}
	};
}


namespace rtl::detail
{
	template<class record_t, class return_t, class ...signature_ts>
	class method_registry : public functor_hop
	{
		using functor_t = return_t(record_t::*)(signature_ts...);

		std::vector<std::pair<functor_t, std::size_t>> m_functors;

	public:

		functor_t operator[](std::size_t index) {
			return m_functors[index].first;
		}

		void push(functor_t fptr, std::size_t lambda_index) {
			m_functors.emplace_back(fptr, lambda_index);
		}

		std::size_t find(functor_t fptr)
		{
			//linear search, efficient for small set.
			for (const auto& itr : m_functors) {
				if (itr.first == fptr) {
					//functor already registered, return its 'index'.
					return itr.second;
				}
			}
			//functor is not already registered, return '-1'.
			return rtl::index_none;
		}
	};
}


namespace rtl::detail
{
	template<class record_t, class return_t, class ...signature_ts>
	class const_method_registry : public functor_hop
	{
		using functor_t = return_t(record_t::*)(signature_ts...) const;

		std::vector<std::pair<functor_t, std::size_t>> m_functors;

	public:

		functor_t operator[](std::size_t index) {
			return m_functors[index].first;
		}

		void push(functor_t fptr, std::size_t lambda_index) {
			m_functors.emplace_back(fptr, lambda_index);
		}

		std::size_t find(functor_t fptr)
		{
			//linear search, efficient for small set.
			for (const auto& itr : m_functors) {
				if (itr.first == fptr) {
					//functor already registered, return its 'index'.
					return itr.second;
				}
			}
			//functor is not already registered, return '-1'.
			return rtl::index_none;
		}
	};
}
