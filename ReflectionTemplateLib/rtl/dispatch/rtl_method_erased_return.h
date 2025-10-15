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

#include "rtl_traits.h"
#include "rtl_forward_decls.h"
#include "lambda_base.h"

namespace rtl
{
    template<class record_t, class ...signature_t>
    struct method<record_t, Return(signature_t...)>
    {
        enum call_by
        {
            value = 0,
            cref = 1,   //const ref.
            ncref = 2   //non-const ref.
        };

        struct invoker
        {
            const record_t& target;
            const method<record_t, Return(signature_t...)>& mt;

            template<class ...args_t> requires (sizeof...(args_t) == sizeof...(signature_t))
            [[nodiscard]] [[gnu::hot]] [[gnu::flatten]]
            constexpr Return operator()(args_t&&...params) const noexcept
            {
                if (!mt) [[unlikely]] {
                    return { error::InvalidCaller, RObject{} };
                }

                if (mt.must_bind_refs()) [[unlikely]] {
                    return { error::ExplicitRefBindingRequired, RObject{} };
                }

                auto index = (mt.m_lambdas[call_by::value] != nullptr ? call_by::value : call_by::cref);
                if (mt.m_lambdas[index]->is_void())
                {
                    mt.m_vhop[index] (*(mt.m_lambdas[index]), target, std::forward<args_t>(params)...);
                    return { error::None, RObject{} };
                }
                else
                {
                    return { error::None,
                             RObject{ mt.m_rhop[index] (*(mt.m_lambdas[index]), target, std::forward<args_t>(params)...),
                                      mt.m_lambdas.back()->get_return_id(), nullptr
                            }
                    };
                }
            }
        };

        template<class ...fwd_args_t>
        struct perfect_fwd
        {
            const record_t& target;
            const method<record_t, Return(signature_t...)>& mt;

            template<class ...args_t>
            [[nodiscard]] [[gnu::hot]] [[gnu::flatten]]
            constexpr Return operator()(args_t&&...params) const noexcept
            {
                if (!mt) [[unlikely]] {
                    return { error::InvalidCaller, RObject{} };
                }

                auto signature_id = traits::uid<traits::strict_sign_id_t<fwd_args_t...>>::value;
                for (int index = 0; index < mt.m_lambdas.size(); index++)
                {
                    if (mt.m_lambdas[index] != nullptr)
                    {
                        if (signature_id == mt.m_lambdas[index]->get_strict_sign_id())
                        {
                            if (mt.m_lambdas[index]->is_void())
                            {
                                mt.m_vhop[index] (*mt.m_lambdas[index], target, std::forward<args_t>(params)...);
                                return { error::None, RObject{} };
                            }
                            else
                            {
                                return { error::None,
                                         RObject{ mt.m_rhop[index] (*mt.m_lambdas[index], target, std::forward<args_t>(params)...),
                                                  mt.m_lambdas.back()->get_return_id(), nullptr
                                        }
                                };
                            }
                        }
                    }
                }
                return { error::RefBindingMismatch, RObject{} };
            }
        };

        constexpr invoker operator()(const record_t& p_target) const noexcept {
            return invoker{ p_target, *this };
        }

        template<class ...args_t>
        requires (std::is_same_v<traits::normal_sign_id_t<args_t...>, std::tuple<signature_t...>>)
        constexpr const perfect_fwd<args_t...> bind(const record_t& p_target) const noexcept {
            return perfect_fwd<args_t...>{ p_target, *this };
        }

        constexpr operator bool() const noexcept {
            return !(m_lambdas.empty() || (m_lambdas.size() == 1 && m_lambdas[0] == nullptr));
        }

        constexpr bool must_bind_refs() const noexcept {
            return (m_lambdas[call_by::value] == nullptr &&
                   (m_lambdas.size() > call_by::ncref || m_lambdas[call_by::cref]->is_any_ncref()));
        }

    private:

        using lambda_vt = std::function<void(const dispatch::lambda_base&, const record_t&, signature_t...)>;

        using lambda_rt = std::function<std::any(const dispatch::lambda_base&, const record_t&, signature_t...)>;

        std::vector<lambda_rt> m_rhop = {};

        std::vector<lambda_vt> m_vhop = {};

        std::vector<const dispatch::lambda_base*> m_lambdas = {};

        GETTER_REF(std::vector<lambda_rt>, _rhop, m_rhop)
        GETTER_REF(std::vector<lambda_vt>, _vhop, m_vhop)
        GETTER_REF(std::vector<const dispatch::lambda_base*>, _overloads, m_lambdas)

        template<class, class ...>
        friend struct detail::HopMethod;

        static_assert((!std::is_reference_v<signature_t> && ...),
                      "rtl::method<...>: any type cannot be specified as reference here.");
    };
}