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

namespace rtl 
{
    template<class ..._signature>
    inline const detail::FunctionCaller<_signature...> Function::bind() const noexcept
    {
        return detail::FunctionCaller<_signature...>{ this };
    }

    template<class ..._signature>
    const Function::HopBuilder<_signature...> Function::args_t() const
    {
        for (auto& functorId : m_functorIds)
        {
            if (functorId.m_lambda->is_signature<_signature...>()) [[likely]] {
                return { functorId.get_lambda_function<_signature...>() };
            }
        }
        return HopBuilder<_signature...>();
    }


    template<class ..._signature>
    template<class _returnType>
    inline constexpr const function_hop<_returnType(_signature...)> Function::HopBuilder<_signature...>::return_t() const
    {
        if (m_lambda != nullptr && m_lambda->template is_returning<_returnType>()) {
            return m_lambda->template get_hopper<_returnType>();
        }
        return function_hop<_returnType(_signature...)>();
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


/*  @method: operator()()
    @param: variadic arguments.
    @return: Return, possible error & return value of from the reflected call.
    * if the arguments did not match with any overload, returns RObject with error::SignatureMismatch
    * providing optional syntax, Function::call() does the exact same thing.
*/  template<class ..._args>
    inline Return Function::operator()(_args&& ...params) const noexcept
    {
        return detail::FunctionCaller<>{ this }.call(std::forward<_args>(params)...);
    }


/*  @method: hasSignatureId()
    @param: const std::size_t& (signatureId to be found)
    @return: the index of the functor in the functor-table.
    * a 'Function' object may be associated with multiple functors in case of overloads.
    * every overload will have unique 'FunctorId', contained by one 'Function' object.
    * given signatureId is compared against the signatureId of all overloads registered.
*/  FORCE_INLINE const std::size_t Function::hasSignatureId(const std::size_t pSignatureId) const
    {
        //simple linear-search, efficient for small set of elements.
        for (const auto& functorId : m_functorIds) {
            if (functorId.getSignatureId() == pSignatureId) [[likely]] {
                return functorId.getLambdaIndex();
            }
        }
        return rtl::index_none;
    }


    FORCE_INLINE const detail::FunctorId* Function::hasFunctorId(const std::size_t pSignatureId) const
    {
        //simple linear-search, efficient for small set of elements.
        for (const auto& functorId : m_functorIds) {
            if (functorId.getSignatureId() == pSignatureId) [[likely]] {
                return &functorId;
            }
        }
        return nullptr;
    }
}
