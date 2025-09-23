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

#include "forward_decls.h"

#include "RObject.h"

namespace rtl::detail
{		
    template<class ..._signature>
    struct FunctionCaller
    {
        const Function* m_function;

    public:

        template<class ..._args>
        rtl::Return call(_args&&...) const noexcept;

        template<class ..._args>
        constexpr rtl::Return operator()(_args&&...params) const noexcept;

        friend Function;
    };
}


namespace rtl::detail
{
    template<>
    struct Hopper<std::nullptr_t>
    {
        const std::vector<FunctorId>& m_functorIds;

        template<class ..._signature>
        struct Build
        {
            const dispatch::lambda_function<_signature...>* m_lambda = nullptr;

            template<class _returnType>
            constexpr const function<_returnType(_signature...)> returnT() const;
        };

        template<class ..._signature>
        const Build<_signature...> argsT() const;
    };
}
