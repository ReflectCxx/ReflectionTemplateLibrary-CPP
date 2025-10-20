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

#include "Function.h"
#include "FunctionCaller.hpp"
#include "RObject.h"
#include "rtl_constants.h"
#include "lambda_base.h"


namespace rtl 
{
    template<class ..._signature>
    inline constexpr const detail::ErasedCaller<true, _signature...> Function::bind() const noexcept
    {
        return detail::ErasedCaller<true, _signature...>{ (*this) };
    }

    template<class ...signatureT>
    inline constexpr const detail::HopFunction<signatureT...> Function::argsT() const
    {
        return detail::Hopper<>{ m_functorsMeta }.argsT<signatureT...>();
    }


/*  @method: hasSignature<...>()
    @param: set of arguments, explicitly specified as template parameter.
    @return: bool, if the functor associated with this object is of certain signature or not.
    * a single 'Function' object can be associated with multiple overloads of same function.
    * the set of arguments passed is checked agains all registered overloads, returns true if matched with any one.
*/  template<class ..._args>
    inline bool Function::hasSignature() const
    {
        //hasSignatureId() returns the index of the 'lambda' in functor-container, which cannot be '-1'.
        return (hasSignatureId(detail::FunctorContainer<_args...>::getContainerId()) != -1);
    }


/*  @method: hasSignatureId()
    @param: const std::size_t& (signatureId to be found)
    @return: the index of the functor in the functor-table.
    * a 'Function' object may be associated with multiple functors in case of overloads.
    * every overload will have unique 'FunctorId', contained by one 'Function' object.
    * given signatureId is compared against the signatureId of all overloads registered.
*/  ForceInline const std::size_t Function::hasSignatureId(const std::size_t pSignatureId) const
    {
        //simple linear-search, efficient for small set of elements.
        for (const auto& functorId : m_functorIds) {
            if (functorId.getSignatureId() == pSignatureId) [[likely]] {
                return functorId.getLambdaIndex();
            }
        }
        return rtl::index_none;
    }


    ForceInline const detail::FunctorId* Function::hasFunctorId(const std::size_t pSignatureId) const
    {
        //simple linear-search, efficient for small set of elements.
        for (const auto& functorId : m_functorIds) {
            if (functorId.getSignatureId() == pSignatureId) [[likely]] {
                return &functorId;
            }
        }
        return nullptr;
    }


    inline constexpr std::optional<type_meta> Function::getLambdaByStrictId(const std::size_t pSignatureId) const
    {
        //simple linear-search, efficient for small set of elements.
        for (const auto& functorMeta : m_functorsMeta) {
            if (pSignatureId == functorMeta.get_strict_args_id()) [[likely]] {
                return { functorMeta };
            }
        }
        return std::nullopt;
    }


    ForceInline std::pair<std::optional<type_meta>, bool> Function::getLambdaByNormalId(const std::size_t pSignatureId) const
    {
        std::optional<type_meta> functorMeta = getLambdaByStrictId(pSignatureId);
        if (functorMeta) {
            return { functorMeta, false };
        }

        std::size_t index = rtl::index_none;
        for (int i = 0; i < m_functorsMeta.size(); i++)
        {
            if (pSignatureId == m_functorsMeta[i].get_normal_args_id()) [[likely]] {
                if (index == rtl::index_none) {
                    index = i;
                }
                else return { std::nullopt, true };
            }
        }

        if (index != rtl::index_none)
        {
            auto isAnyNonConstRefInArgsT = (m_functorsMeta[index].is_any_arg_ncref());
            return { (isAnyNonConstRefInArgsT ? std::nullopt : std::make_optional(m_functorsMeta[index])), isAnyNonConstRefInArgsT };
        }
        return { std::nullopt, false };
    }
}