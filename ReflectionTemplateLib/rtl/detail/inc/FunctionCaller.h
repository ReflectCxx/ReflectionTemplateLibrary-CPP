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

#include "rtl_forward_decls.h"

namespace rtl::detail
{		
    template<class ..._signature>
    struct ErasedCaller
    {
        const Function* m_function;

        template<class ..._args>
        rtl::Return call(_args&&...) const noexcept;

        template<class ..._args>
        constexpr rtl::Return operator()(_args&&...params) const noexcept;
    };
}


namespace rtl::detail
{
    template<class ..._signature>
    struct HopFunction
    {
        const dispatch::lambda_function<_signature...>* m_lambda = nullptr;

        template<class _returnType>
        constexpr const function<_returnType(_signature...)> returnT() const;
    };


    template<>
    struct Hopper<>
    {
        const std::vector<FunctorId>& m_functorIds;

        template<class ..._signature>
        constexpr const HopFunction<_signature...> argsT() const;
    };
}