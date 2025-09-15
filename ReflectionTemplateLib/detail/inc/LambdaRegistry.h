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

#include <tuple>
#include <vector>
#include <functional>

#include "TypeId.h"
#include "Constants.h"
#include "FunctorRegistry.h"


namespace rtl::detail
{
	class lambda_hop {
	public:

		std::size_t m_signatureId = TypeId<>::None;
		std::vector<std::size_t> m_argsId;
	};
}


namespace rtl::detail
{
    template<methodQ, class ..._signature>
    class lambda_registry;

    template<class ...signature_ts>
    class lambda_registry<methodQ::None, signature_ts...> : public lambda_hop
    {
        using lambda_t = std::function<Return(const FunctorId&, signature_ts...)>;

        std::vector<lambda_t> lambda_table;

        std::vector<functor_hop*> m_functors;

    public:

        lambda_registry() 
        {
            m_signatureId = TypeId<std::tuple<signature_ts...>>::get();
            TypeId<signature_ts...>::get(m_argsId);
        }

        GETTER_CREF(std::vector<lambda_t>, , lambda_table)

        void push(const lambda_t& lambda) 
        {
            lambda_table.push_back(lambda);
        }

        Return operator()(std::size_t index, signature_ts&&...params)
        {
            return lambda_table[index](m_functors[index], index, std::forward<signature_ts>(params)...);
        }
    };


    template<class ...signature_ts>
    class lambda_registry<methodQ::NonConst, signature_ts...> : public lambda_hop
    {
        using lambda_t = std::function <Return(const FunctorId&, const RObject&, signature_ts...)>;

        std::vector<lambda_t> lambda_table;

        std::vector<functor_hop*> m_functors;

    public:

        lambda_registry() 
        {
            m_signatureId = TypeId<std::tuple<signature_ts...>>::get();
            TypeId<signature_ts...>::get(m_argsId);
        }

        GETTER_CREF(std::vector<lambda_t>, , lambda_table)

        void push(const lambda_t& lambda)
        {
            lambda_table.push_back(lambda);
        }

        Return operator()(std::size_t index, signature_ts&&...params)
        {
            return lambda_table[index](m_functors[index], index, std::forward<signature_ts>(params)...);
        }
    };


    template<class ...signature_ts>
    class lambda_registry<methodQ::Const, signature_ts...> : public lambda_hop
    {
        using lambda_t = std::function <Return(const FunctorId&, const RObject&, signature_ts...)>;

        std::vector<lambda_t> lambda_table;

        std::vector<functor_hop*> m_functors;

    public:

        lambda_registry()
        {
            m_signatureId = TypeId<std::tuple<signature_ts...>>::get();
            TypeId<signature_ts...>::get(m_argsId);
        }

        GETTER_CREF(std::vector<lambda_t>, , lambda_table)

        void push(const lambda_t& lambda)
        {
            lambda_table.push_back(lambda);
        }

        Return operator()(std::size_t index, signature_ts&&...params)
        {
            return lambda_table[index](m_functors[index], index, std::forward<signature_ts>(params)...);
        }
    };
}