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
#include "Function.h"
#include "FunctionCaller.h"
#include "FunctorContainer.h"

namespace rtl::detail
{
    template<class ..._signature>
    template<class ..._args>
    FORCE_INLINE Return FunctionCaller<_signature...>::call(_args&&...params) const noexcept
    {
        using Container = std::conditional_t<sizeof...(_signature) == 0,
                                             FunctorContainer<std::remove_reference_t<_args>...>,
                                             FunctorContainer<_signature...>>;

        const detail::FunctorId* functorId = m_function->hasFunctorId(Container::getContainerId());
        if (functorId != nullptr) [[likely]] {
            return Container::template forwardCall<_args...>(*functorId, std::forward<_args>(params)...);
        }
        return { error::SignatureMismatch, RObject{} };
    }


    template<class ..._signature>
    template<class ..._args>
    constexpr inline rtl::Return FunctionCaller<_signature...>::operator()(_args&&...params) const noexcept
    {
        return call(std::forward<_args>(params)...);
    }
}


namespace rtl::detail
{
    template<class ..._signature>
    inline constexpr const HopFunction<_signature...> Hopper<>::argsT() const
    {
        const auto argsId = TypeId<std::tuple<traits::raw_t<_signature...>>>::get();
        for (auto& functorId : m_functorIds)
        {
            auto lambda = functorId.get_lambda_function<_signature...>(argsId);
            if (lambda != nullptr) {
                return { lambda };
            }
        }
        return HopFunction<_signature...>();
    }


    template<class ..._signature>
    template<class _returnType>
    inline constexpr 
        const function<_returnType(_signature...)> 
                       HopFunction<_signature...>::returnT() const
    {
        const auto retId = TypeId<void>::get();
        if (m_lambda != nullptr) [[likely]] {
            return m_lambda->template get_hopper<_returnType>(retId);
        }
        return function<_returnType(_signature...)>();
    }
}