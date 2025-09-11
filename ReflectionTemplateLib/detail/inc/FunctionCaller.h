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

#include "RObject.h"

namespace rtl
{
    class Function;
}

namespace rtl::detail
{		
    template<class ..._signature>
    struct FunctionCaller
    {
        //the function to be called.
        const Function* m_function;

    public:

        template<class ..._args>
        rtl::Return call(_args&&...) const;

        template<class ..._args>
        constexpr rtl::Return operator()(_args&&...params) const
        {
            return call(std::forward<_args>(params)...);
        }

        friend Function;
    };
}
