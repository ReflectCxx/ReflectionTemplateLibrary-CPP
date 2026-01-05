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
    template<class ...signatureT>
    inline constexpr const detail::InitFunctionHop<detail::member::None, signatureT...> Function::argsT() const
    {
        return detail::HopBuilder<detail::member::None>{ m_functorsMeta }.argsT<signatureT...>();
    }


/*  @method: hasSignature<...>()
    @param: set of arguments, explicitly specified as template parameter.
    @return: bool, if the functor associated with this object is of certain signature or not.
    * a single 'Function' object can be associated with multiple overloads of same function.
    * the set of arguments passed is checked against all registered overloads, returns true if matched with any one.
*/  template<class ..._args>
    inline constexpr bool Function::hasSignature() const
    {
        return hasSignatureId(traits::uid<traits::strict_sign_id_t<_args...>>::value);
    }


/*  @method: hasSignId()
    @param: const std::size_t& (signatureId to be found)
    @return: the index of the functor in the functor-table.
    * a 'Function' object may be associated with multiple functors in case of overloads.
    * every overload will have unique 'FunctorId', contained by one 'Function' object.
    * given signatureId is compared against the signatureId of all overloads registered.
*/  inline const std::size_t Function::hasSignId(const std::size_t pSignatureId) const
    {
        //simple linear-search, efficient for small set of elements.
        for (const auto& functorId : m_functorIds) {
            if (functorId.getSignatureId() == pSignatureId) [[likely]] {
                return functorId.m_lambdaIndex;
            }
        }
        return rtl::index_none;
    }


    inline bool Function::hasSignatureId(const traits::uid_t pSignatureId) const
    {
        //simple linear-search, efficient for small set of elements.
        for (const auto& functorId : m_functorIds) {
            if (functorId.get_functor().get_strict_sign_id() == pSignatureId) [[likely]] {
                return true;
            }
        }
        return false;
    }


    inline const detail::FunctorId* Function::hasFunctorId(const std::size_t pSignatureId) const
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