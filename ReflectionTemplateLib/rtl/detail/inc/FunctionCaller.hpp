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
    template<bool is_binding_v, class ..._signature>
    template<class ..._args>
    ForceInline Return ErasedCaller<is_binding_v, _signature...>::call(_args&&...params) const noexcept
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
    template<class ...args_t>
    inline constexpr const HopFunction<args_t...> Hopper<>::argsT() const
    {
        auto strictArgsId = traits::uid<traits::strict_sign_id_t<args_t...>>::value;
        auto normalArgsId = traits::uid<traits::normal_sign_id_t<args_t...>>::value;

        const dispatch::lambda_function<args_t...>* lambda = nullptr;
        std::vector<const dispatch::lambda_base*> refOverloads = { nullptr };

        for (auto& functorId : m_functorIds)
        {
            if (!lambda && strictArgsId == functorId.m_lambda->get_strict_sign_id()) {
                lambda = &(functorId.m_lambda->to_function<args_t...>());
            }
            if (normalArgsId == functorId.m_lambda->get_normal_sign_id())
            {
                if (normalArgsId == functorId.m_lambda->get_strict_sign_id()) {
                    refOverloads[0] = functorId.m_lambda;
                }
                else if (!functorId.m_lambda->is_any_ncref()) {
                    refOverloads.push_back(functorId.m_lambda);
                }
            }
        }
        for (auto& functorId : m_functorIds)
        {
            if (normalArgsId == functorId.m_lambda->get_normal_sign_id() && functorId.m_lambda->is_any_ncref()) {
                refOverloads.push_back(functorId.m_lambda);
            }
        }
        return { lambda, refOverloads };
    }


    template<class ...args_t>
    template<class return_t> requires (std::is_same_v<return_t, rtl::Return>)
    inline constexpr const function<return_t(args_t...)> HopFunction<args_t...>::returnT() const
    {
        const auto retId = traits::uid<return_t>::value;
        if (m_lambda != nullptr) [[likely]] {
            return m_lambda->template get_hopper<return_t>(retId);
        }
        return function<return_t(args_t...)>();
    }


    template<class ...args_t>
    template<class return_t> requires (!std::is_same_v<return_t, rtl::Return>)
    inline constexpr const function<return_t(args_t...)> HopFunction<args_t...>::returnT() const
    {
        const auto retId = traits::uid<return_t>::value;
        if (m_lambda != nullptr) [[likely]] {
            return m_lambda->template get_hopper<return_t>(retId);
        }
        return function<return_t(args_t...)>();
    }


    template<bool is_binding_v, class ...signatureT>
    template<class ...args_t> requires (is_binding_v == true)
    ForceInline constexpr Return ErasedCaller<is_binding_v, signatureT...>::operator()(args_t&&...params) const noexcept
    {
        auto functorId = m_function.getLambdaByStrictId(traits::uid<traits::strict_sign_id_t<signatureT...>>::value);
        if (functorId) [[likely]]
        {
            const auto& erased = functorId->m_lambda->m_erasure;
            const auto& caller = erased.template to_erased_return<signatureT...>();
            if (functorId->m_lambda->is_void())
            {
                caller.hop_void(std::forward<args_t>(params)...);
                return { error::None, RObject{} };
            }
            else
            {
                return{ error::None,
                        RObject{ caller.hop_return(std::forward<args_t>(params)...),
                                 caller.get_return_id(), nullptr }
                };
            }
        }
        else [[unlikely]] {
            return { error::SignatureMismatch, RObject{} };
        }
    }


    template<bool is_binding_v, class ...signatureT>
    template<class ...args_t> requires (is_binding_v == false)
    ForceInline constexpr Return ErasedCaller<is_binding_v, signatureT...>::operator()(args_t&&...params) const noexcept
    {
        auto functorId = m_function.getLambdaByNormalId(traits::uid<traits::normal_sign_id_t<args_t...>>::value);
        if (functorId.first) [[likely]]
        {
            const auto& erased = functorId.first->m_lambda->m_erasure;
            const auto& caller = erased.template to_erased_return<args_t...>();
            if (functorId.first->m_lambda->is_void())
            {
                caller.hop_void(std::forward<args_t>(params)...);
                return { error::None, RObject{} };
            }
            else
            {
                return{ error::None,
                        RObject{ caller.hop_return(std::forward<args_t>(params)...),
                                 caller.get_return_id(), nullptr }
                };
            }
        }
        else [[unlikely]] {
            return { (functorId.second ? error::ExplicitRefBindingRequired:error::SignatureMismatch), RObject{} };
        }
    }
}