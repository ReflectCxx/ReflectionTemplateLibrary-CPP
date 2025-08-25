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

namespace rtl {

    //forward decls
    class Method;
}

namespace rtl::detail {

    template<class ..._signature>
    class DefaultInvoker
    {
        //the method to be called.
        const Method& m_method;

        //the object on which, the method needs to be called.
        const RObject& m_target;

        DefaultInvoker(const Method& pMethod, const RObject& pTarget);

        template<class ..._invokSignature>
        struct Invoker {

            template<class ..._args>
            static RObject invoke(error& pError, const Method& pMethod, const RObject& pTarget, _args&&...);
        };

    public:

        template<class ..._args>
        std::pair<error, RObject> call(_args&&...) const noexcept;

        friend Method;
    };


    template<class ..._signature>
    class NonConstInvoker
    {
        //the method to be called.
        const Method& m_method;

        //the object on which, the method needs to be called.
        const RObject& m_target;

        NonConstInvoker(const Method& pMethod, const RObject& pTarget);

        template<class ..._invokSignature>
        struct Invoker {

            template<class ..._args>
            static RObject invoke(error& pError, const Method& pMethod, const RObject& pTarget, _args&&...);
        };

    public:

        template<class ..._args>
        std::pair<error, RObject> call(_args&&...) const noexcept;

        friend Method;
    };
}