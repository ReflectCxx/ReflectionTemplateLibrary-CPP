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
#include <inc/Method.h>
#include <detail/inc/HopBuilderMethod.hpp>

namespace rtl
{
    template<class recordT, class ...signatureT> requires (!std::is_const_v<recordT>)
    inline constexpr detail::HopBuilder<detail::member::NonConst, recordT> Method::targetT() const
    {
        return detail::HopBuilder<detail::member::NonConst, recordT>{ *this };
    }

    template<class recordT, class ...signatureT> requires (std::is_const_v<recordT>)
    inline constexpr detail::HopBuilder<detail::member::Const, std::remove_const_t<recordT>> Method::targetT() const
    {
        return detail::HopBuilder<detail::member::Const, std::remove_const_t<recordT> >{ *this };
    }

    template<class ...signatureT>
    inline constexpr const detail::InitFunctionHop<detail::member::Static, signatureT...> Method::argsT() const
    {
        return detail::HopBuilder<detail::member::Static>{ getFunctorsMeta() }.argsT<signatureT...>();
    }

    /*  @method: hasSignature<...>()
    @params: template params, <_arg0, ..._args> (expects at least one args- _args0)
    @return: bool
    * checks if the member-function functor associated with this 'Method', takes template specified arguments set or not.
*/  template<class ..._args>
    inline bool Method::hasSignature() const
    {
        if (getMemberKind() == detail::member::Static) {
            return Function::hasSignature<_args...>();
        }
        else {
            return hasSignatureId(traits::uid<traits::strict_sign_id_t<_args...>>::value);
        }
    }
}