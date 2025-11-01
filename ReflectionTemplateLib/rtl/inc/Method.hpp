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
    ForceInline const detail::DefaultInvoker<_signature...> Method::bind(const RObject& pTarget) const
    {
        return detail::DefaultInvoker<_signature...>{ this, &pTarget };
    }


    template<class ..._signature>
    ForceInline const detail::NonConstInvoker<_signature...> Method::bind(constCast<RObject>&& pTarget) const
    {
        return detail::NonConstInvoker<_signature...>{ this, &pTarget.m_target };
    }


    template<class recordT, class ...signatureT>
    inline constexpr detail::Hopper<detail::member::None, recordT> Method::targetT() const
    {
        return detail::Hopper<detail::member::None, recordT>{ getFunctorsMeta() };
    }

    template<class ...signatureT>
    constexpr const detail::HopFunction<detail::member::Static, signatureT...> Method::argsT() const
    {
        return detail::Hopper<detail::member::Static>{ getFunctorsMeta() }.argsT<signatureT...>();
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
            case detail::member::Static: {
                return Function::hasSignature<_args...>();
            }
            case detail::member::NonConst: {
                using Container = detail::MethodContainer<detail::member::NonConst, _args...>;
                return (hasSignatureId(Container::getContainerId()) != -1);
            }
            case detail::member::Const: {
                using Container = detail::MethodContainer<detail::member::Const, _args...>;
                return (hasSignatureId(Container::getContainerId()) != -1);
            }
        }
        return false;
    }
}