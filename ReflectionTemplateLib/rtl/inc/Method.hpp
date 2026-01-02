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
        return detail::DefaultInvoker<_signature...>{ this, &pTarget };
    }


    template<class ..._signature>
    inline const detail::NonConstInvoker<_signature...> Method::bind(constCast<RObject>&& pTarget) const
    {
        return detail::NonConstInvoker<_signature...>{ this, &pTarget.m_target };
    }


    template<class recordT, class ...signatureT> requires (!std::is_const_v<recordT>)
    inline constexpr detail::Hopper<detail::member::NonConst, recordT> Method::targetT() const
    {
        return detail::Hopper<detail::member::NonConst, recordT>{ getRecordTypeId(), getFunctorsMeta() };
    }


    template<class recordT, class ...signatureT> requires (std::is_const_v<recordT>)
    inline constexpr detail::Hopper<detail::member::Const, std::remove_const_t<recordT>> Method::targetT() const
    {
        return detail::Hopper<detail::member::Const, std::remove_const_t<recordT> >{ getRecordTypeId(), getFunctorsMeta() };
    }


    template<class ...signatureT>
    inline constexpr const detail::HopFunction<detail::member::Static, signatureT...> Method::argsT() const
    {
        return detail::Hopper<detail::member::Static>{ getFunctorsMeta() }.argsT<signatureT...>();
    }


    /*  @method: hasSignature<...>()
    @params: template params, <_arg0, ..._args> (expects at least one args- _args0)
    @return: bool
    * checks if the member-function functor associated with this 'Method', takes template specified arguments set or not.
*/  template<class ..._args>
    inline bool Method::hasSignature() const
    {
        switch (getMemberKind())
        {
            case detail::member::Static: {
                return Function::hasSignature<_args...>();
            }
            case detail::member::NonConst: {
                using Container = detail::MethodContainer<detail::member::NonConst, _args...>;
                return (hasSignId(Container::getContainerId()) != -1);
            }
            case detail::member::Const: {
                using Container = detail::MethodContainer<detail::member::Const, _args...>;
                return (hasSignId(Container::getContainerId()) != -1);
            }
        }
        return false;
    }
}