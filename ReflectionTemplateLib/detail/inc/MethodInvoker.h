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

namespace rtl::access {

    //forward decls
    class Method;
}

namespace rtl::detail {

    template<class ..._signature>
    class MethodInvoker
    {
        //the method to be called.
        const access::Method& m_method;

        //the object on which, the method needs to be called.
        const access::RObject& m_target;

        MethodInvoker(const access::Method& pMethod, const access::RObject& pTarget);

        template<class ..._invokSignature>
        struct Invoker {

            template<class ..._args>
            static access::RObject invoke(error& pError, const access::Method& pMethod, const access::RObject& pTarget, _args&&...);
        };

    public:

        template<class ..._args>
        std::pair<error, access::RObject> call(_args&&...) const noexcept;

        friend access::Method;
    };


    template<methodQ _Q, class ..._signature>
    class MethodInvokerQ
    {
        //the method to be called.
        const access::Method& m_method;

        //the object on which, the method needs to be called.
        const access::RObject& m_target;

        MethodInvokerQ(const access::Method& pMethod, const access::RObject& pTarget);

        template<class ..._invokSignature>
        struct Invoker {

            template<class ..._args>
            static access::RObject invoke(error& pError, const access::Method& pMethod, const access::RObject& pTarget, _args&&...);
        };

    public:

        template<class ..._args>
        std::pair<error, access::RObject> call(_args&&...) const noexcept;

        friend access::Method;
    };
}