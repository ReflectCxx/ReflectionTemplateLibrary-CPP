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


namespace rtl::detail {

    template<class ..._signature>
    struct DefaultInvoker
    {
        //the method to be called.
        const Method* m_method;

        //the object on which, the method needs to be called.
        const RObject* m_target;

        template<class ..._invokSignature>
        struct Invoker {

            template<class ..._args>
            static Return invoke(const Method& pMethod, const RObject& pTarget, _args&&...);
        };

    public:

        template<class ..._args>
        Return call(_args&&...) const noexcept;

        template<class ..._args>
        constexpr Return operator()(_args&&...params) const noexcept {
            return call(std::forward<_args>(params)...);
        }

        friend Method;
    };


    template<class ..._signature>
    struct NonConstInvoker
    {
        //the method to be called.
        const Method* m_method;

        //the object on which, the method needs to be called.
        const RObject* m_target;

        template<class ..._invokSignature>
        struct Invoker {

            template<class ..._args>
            static Return invoke(const Method& pMethod, const RObject& pTarget, _args&&...);
        };

    public:

        template<class ..._args>
        Return call(_args&&...) const noexcept;

        template<class ..._args>
        constexpr Return operator()(_args&&...params) const noexcept {
            return call(std::forward<_args>(params)...);
        }

        friend Method;
    };
}


namespace rtl::detail
{
    template<class _recordType, class ..._signature>
    struct HopMethod
    {
        const dispatch::lambda_method<_recordType, _signature...>* m_lambda = nullptr;

        template<class _returnType>
        constexpr const method<_returnType(_recordType::*)(_signature...)> returnT() const;
    };

    template<class _recordType>
    struct Hopper
    {
        const std::vector<FunctorId>& m_functorIds;

        template<class ..._signature>
        constexpr HopMethod<_recordType, _signature...> argsT() const;
    };
}