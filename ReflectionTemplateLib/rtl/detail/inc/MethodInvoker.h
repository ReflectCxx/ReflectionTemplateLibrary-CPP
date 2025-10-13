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

#include "rtl_typeid.h"
#include "rtl_forward_decls.h"

namespace rtl::detail
{
    template<class _recordType>
    struct ErasedInvoker
    {
        const Method& m_method;

        const _recordType& m_target;

        template<class ..._args> requires (std::is_same_v<traits::raw_t<_recordType>, RObject> == false)
        constexpr Return operator()(_args&&...params) const noexcept;
        
        template<class ..._args> requires (std::is_same_v<traits::raw_t<_recordType>, RObject> == true)
        constexpr Return operator()(_args&&...params) const noexcept;
    };
}


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

        template<class ..._args>
        Return call(_args&&...) const noexcept;

        template<class ..._args>
        constexpr Return operator()(_args&&...params) const noexcept {
            return call(std::forward<_args>(params)...);
        }
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

        template<class ..._args>
        Return call(_args&&...) const noexcept;

        template<class ..._args>
        constexpr Return operator()(_args&&...params) const noexcept {
            return call(std::forward<_args>(params)...);
        }
    };
}


namespace rtl::detail
{
    template<class recordT, class ...signatureT>
    struct HopMethod
    {
        const dispatch::lambda_method<recordT, signatureT...>* m_lambda = nullptr;

        std::vector<const dispatch::lambda_base*> m_lambdaRefOverloads = {};

        template<class retT> requires (std::is_const_v<recordT> == false)
        constexpr const method<retT(recordT::*)(signatureT...)> returnT() const;

        template<class retT> requires (std::is_const_v<recordT> == true)
        constexpr const method<retT(recordT::*)(signatureT...) const> returnT() const;
    };

    template<class recordT>
    struct Hopper
    {
        const std::vector<FunctorId>& m_functorIds;

        template<class ...signatureT>
        constexpr HopMethod<recordT, signatureT...> argsT() const;
    };
}