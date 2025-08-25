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

namespace rtl
{
    class RObject;
    class Function;
}

namespace rtl::detail
{		
    template<class ..._signature>
    class FunctionCaller
    {
        //the function to be called.
        const Function& m_function;

        FunctionCaller(const Function& pFunction);

    public:

        template<class ..._args>
        std::pair<error, RObject> call(_args&&...) const noexcept;

        friend Function;
    };
}