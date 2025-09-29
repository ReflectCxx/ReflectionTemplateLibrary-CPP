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

#include "erase_method.h"

namespace rtl::detail 
{
    template<class _recordType>
    struct ErasedInvoker
    {
        const Method& m_method;

        const _recordType& m_target;

        template<class ..._args>
        constexpr error call_v(_args&&...params) const noexcept
        {
            auto functorId = m_method.getLambdaById(detail::TypeId<std::tuple<traits::raw_t<_args>... >>::get());
            if (functorId) [[likely]] {
                functorId->template get_lambda_method<_recordType, _args...>()->m_erasure->hop_v(m_target, std::forward<_args>(params)...);
            }
            return error::None;
        }

        template<class ..._args>
        constexpr std::any call_r(_args&&...params) const noexcept
        {
            auto functorId = m_method.getLambdaById(detail::TypeId<std::tuple<traits::raw_t<_args>... >>::get());
            if (functorId) [[likely]] {
                return functorId->template get_lambda_method<_recordType, _args...>()->m_erasure->hop_r(m_target, std::forward<_args>(params)...);
            }
            return std::any();
        }
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