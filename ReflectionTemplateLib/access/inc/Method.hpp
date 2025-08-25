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
#include "Method.h"
#include "MethodInvoker.hpp"

namespace rtl
{
    template<class ..._signature>
    inline const detail::DefaultInvoker<_signature...> Method::bind(const RObject& pTarget) const
    {
        return detail::DefaultInvoker<_signature...>(*this, pTarget);
    }


    template<class ..._signature>
    inline const detail::NonConstInvoker<_signature...> Method::bind(constCast<RObject>&& pTarget) const
    {
        return detail::NonConstInvoker<_signature...>(*this, const_cast<RObject&>(pTarget.m_target));
    }


/*  @method: invokeCtor()
    @params: variable arguments.
    @return: RStatus
    * calls the constructor with given arguments.
*/  template<class ..._args>
    inline std::pair<error, RObject> Method::invokeCtor(alloc&& pAllocType, _args&& ...params) const
    {
        return Function::bind().call<alloc, _args...>(std::forward<alloc>(pAllocType), std::forward<_args>(params)...);
    }


/*  @method: hasSignature<...>()
    @params: template params, <_arg0, ..._args> (expects at least one args- _args0)
    @return: bool
    * checks if the member-function functor associated with this 'Method', takes template specified arguments set or not.
*/  template<class ..._args>
    inline bool Method::hasSignature() const
    {
        switch (getQualifier())
        {
        case methodQ::None: {
            return Function::hasSignature<_args...>();
        }
        case methodQ::NonConst: {
            using Container = detail::MethodContainer<methodQ::NonConst, _args...>;
            return (hasSignatureId(Container::getContainerId()) != -1);
        }
        case methodQ::Const: {
            using Container = detail::MethodContainer<methodQ::Const, _args...>;
            return (hasSignatureId(Container::getContainerId()) != -1);
        }
        }
        return false;
    }
}