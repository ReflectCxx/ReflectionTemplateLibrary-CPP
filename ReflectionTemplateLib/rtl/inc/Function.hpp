/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#pragma once

#include <inc/Function.h>
#include <detail/inc/HopBuilderFunction.hpp>

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


    inline bool Function::hasSignatureId(const traits::uid_t pSignatureId) const
    {
        //simple linear-search, efficient for small set of elements.
        for (const auto& fnMeta : m_functorsMeta) {
            if (fnMeta.get_strict_args_id() == pSignatureId) [[likely]] {
                return true;
            }
        }
        return false;
    }
}