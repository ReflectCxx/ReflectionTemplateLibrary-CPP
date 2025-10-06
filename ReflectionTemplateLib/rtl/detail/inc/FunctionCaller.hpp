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

#include "erased_hopper.h"


namespace rtl::detail
{
    template<class ..._signature>
    template<class ..._args>
    ForceInline Return ErasedCaller<_signature...>::call(_args&&...params) const noexcept
    {
        using Container = std::conditional_t<sizeof...(_signature) == 0,
            FunctorContainer<std::remove_reference_t<_args>...>,
            FunctorContainer<_signature...>>;

        const detail::FunctorId* functorId = m_function.hasFunctorId(Container::getContainerId());
        if (functorId != nullptr) [[likely]] {
            return Container::template forwardCall<_args...>(*functorId, std::forward<_args>(params)...);
        }
        return { error::SignatureMismatch, RObject{} };
    }
}



namespace rtl::detail
{
    template<class ...signatureT>
    template<class ...argsT>
    ForceInline constexpr Return ErasedCaller<signatureT...>::operator()(argsT&&...params) const noexcept
    {
        auto functorId = m_function.getLambdaById(detail::TypeId<traits::fwd_sign_t<argsT...>>::get());
        if (functorId) [[likely]] 
        {
            const auto& erased = functorId->m_lambda->m_erasure;
            const auto& caller = erased.template to_erased_ret_function<argsT...>();
            if(functorId->m_lambda->is_void())
            {
                caller.hop_void(std::forward<argsT>(params)...);
                return { error::None, RObject{} };
            }
            else
            {
                return{ error::None,
                        RObject{ caller.hop_return(std::forward<argsT>(params)...),
                                 caller.get_return_id(), nullptr } 
                    };
            }
        }
        else return { error::SignatureMismatch, RObject{} };
    }
}


namespace rtl::detail
{
    template<class ...signatureT>
    inline constexpr const HopFunction<signatureT...> Hopper<>::argsT() const
    {
        const auto argsId = TypeId<traits::fwd_sign_t<signatureT...>>::get();
        for (auto& functorId : m_functorIds)
        {
            auto lambda = functorId.get_lambda_function<signatureT...>(argsId);
            if (lambda != nullptr) [[likely]] {
                return { lambda };
            }
        }
        return HopFunction<signatureT...>();
    }


    template<class ...args_t>
    template<class return_t>
    inline constexpr const function<return_t(args_t...)> HopFunction<args_t...>::returnT() const
    {
        const auto retId = TypeId<return_t>::get();
        if (m_lambda != nullptr) [[likely]] {
            return m_lambda->template get_hopper<return_t>(retId);
        }
        return function<return_t(args_t...)>();
    }
}