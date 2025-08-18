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

namespace rtl::access
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
        const access::Function& m_function;

        FunctionCaller(const access::Function& pFunction);

    public:

        template<class ..._args>
        std::pair<error, access::RObject> call(_args&&...) const noexcept;

        friend access::Function;
    };
}