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
    FORCE_INLINE const detail::DefaultInvoker<_signature...> Method::bind(const RObject& pTarget) const
    {
        return detail::DefaultInvoker<_signature...>{ this, &pTarget };
    }


    template<class ..._signature>
    FORCE_INLINE const detail::NonConstInvoker<_signature...> Method::bind(constCast<RObject>&& pTarget) const
    {
        return detail::NonConstInvoker<_signature...>{ this, &pTarget.m_target };
    }


    template<class _recordType, class ..._signature>
    inline constexpr detail::Hopper<_recordType> Method::lambda() const
    {
        return detail::Hopper<_recordType>{ getFunctorIds() };
    }


/*  @method: invokeCtor()
    @params: variable arguments.
    @return: RStatus
    * calls the constructor with given arguments.
*/  template<class ..._args>
    inline Return Method::invokeCtor(alloc pAllocType, const detail::FunctorId& pClonerId, _args&& ...params) const
    {
        using Container = detail::FunctorContainer<alloc, detail::FunctorId, std::remove_reference_t<_args>...>;

        const detail::FunctorId* functorId = hasFunctorId(Container::getContainerId());
        if (functorId != nullptr) [[likely]] {
            return Container::template forwardCall<_args...>(*functorId, pAllocType, pClonerId, std::forward<_args>(params)...);
        }
        return { error::SignatureMismatch, RObject{} };
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
            case detail::methodQ::None: {
                return Function::hasSignature<_args...>();
            }
            case detail::methodQ::NonConst: {
                using Container = detail::MethodContainer<detail::methodQ::NonConst, _args...>;
                return (hasSignatureId(Container::getContainerId()) != -1);
            }
            case detail::methodQ::Const: {
                using Container = detail::MethodContainer<detail::methodQ::Const, _args...>;
                return (hasSignatureId(Container::getContainerId()) != -1);
            }
        }
        return false;
    }
}