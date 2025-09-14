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

#include "Constants.h"
#include "forward_decls.h"


namespace rtl::detail
{
	class functor_hop {};
}


namespace rtl::detail
{
	template<class return_t, class ...signature_ts>
	class functor_registry: public functor_hop
	{
		using functor_t = return_t(*)(signature_ts...);

		std::vector<std::pair<functor_t, std::size_t>> m_functors;

	public:

		const std::vector<std::pair<functor_t, std::size_t>>& get() {
			return m_functors;
		}

		functor_t operator[](std::size_t index) {
			return m_functors[index].first;
		}

		void push(functor_t fptr, std::size_t lambda_index) {
			m_functors.emplace_back(fptr, lambda_index);
		}

		std::pair<std::size_t, std::size_t> find(functor_t fptr)
		{
			//linear search, efficient for small set.
			for (int index = 0; index < m_functors.size(); index++) {
				if (m_functors[index].first == fptr) {
					return { index, m_functors[index].second };
				}
			}
			return { rtl::index_none, rtl::index_none };
		}
	};
}


namespace rtl::detail
{
	template<methodQ, class record_t, class return_t, class ...signature_ts>
	class functor_registry_m;

	template<class record_t, class return_t, class ...signature_ts>
	class functor_registry_m<methodQ::NonConst, record_t, return_t, signature_ts...> : public functor_hop
	{
		using functor_t = return_t(record_t::*)(signature_ts...);

		std::vector<std::pair<functor_t, std::size_t>> m_functors;

	public:

		const std::vector<std::pair<functor_t, std::size_t>>& get() {
			return m_functors;
		}


		functor_t operator[](std::size_t index) {
			return m_functors[index].first;
		}

		void push(functor_t fptr, std::size_t lambda_index) {
			m_functors.emplace_back(fptr, lambda_index);
		}

		std::pair<std::size_t, std::size_t> find(functor_t fptr)
		{
			//linear search, efficient for small set.
			for (int index = 0; index < m_functors.size(); index++) {
				if (m_functors[index].first == fptr) {
					return { index, m_functors[index].second };
				}
			}
			return { rtl::index_none, rtl::index_none };
		}
	};
}


namespace rtl::detail
{
	template<class record_t, class return_t, class ...signature_ts>
	class functor_registry_m<methodQ::Const, record_t, return_t, signature_ts...> : public functor_hop
	{
		using functor_t = return_t(record_t::*)(signature_ts...) const;

		std::vector<std::pair<functor_t, std::size_t>> m_functors;

	public:

		const std::vector<std::pair<functor_t, std::size_t>>& get() {
			return m_functors;
		}

		functor_t operator[](std::size_t index) {
			return m_functors[index].first;
		}

		void push(functor_t fptr, std::size_t lambda_index) {
			m_functors.emplace_back(fptr, lambda_index);
		}

		std::pair<std::size_t, std::size_t> find(functor_t fptr)
		{
			//linear search, efficient for small set.
			for (int index = 0; index < m_functors.size(); index++) {
				if (m_functors[index].first == fptr) {
					return { index, m_functors[index].second };
				}
			}
			return { rtl::index_none, rtl::index_none };
		}
	};
}