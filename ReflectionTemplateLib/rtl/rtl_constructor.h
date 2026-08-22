/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#pragma once

#include <dispatch/functor.h>
#include <inc/RObject.hpp>

namespace rtl
{
    template<class ...signature_t>
    class constructor
    {
        using lambda_t = std::function<Return(alloc, signature_t...)>;

        error m_init_err = error::InvalidCaller;

        std::vector<lambda_t> m_hop = {};

        std::vector<const dispatch::functor*> m_functors = {};

        GETTER_REF(std::vector<lambda_t>, _hop, m_hop)
        GETTER_REF(std::vector<const dispatch::functor*>, _overloads, m_functors)

        void set_init_error(error p_err) {
            m_init_err = p_err;
        }

    public:

        GETTER(rtl::error, _init_error, m_init_err)

        constexpr operator bool() const noexcept {
            return !(m_init_err != error::None || m_functors.empty() ||
                     (m_functors.size() == 1 && m_functors[0] == nullptr));
        }

        constexpr bool must_bind_refs() const noexcept {
            return (m_functors[detail::call_by::value] == nullptr &&
                    (m_functors.size() > detail::call_by::ncref || m_functors[detail::call_by::cref]->is_any_arg_ncref()));
        }

        template<class ...args_t>
            requires (sizeof...(args_t) == sizeof...(signature_t))
        constexpr Return operator()(alloc p_alloc_on, args_t&&...params) const noexcept
        {
            if (!(*this)) [[unlikely]] {
                return { m_init_err, RObject{} };
            }

            if (must_bind_refs()) [[unlikely]] {
                return { error::ExplicitRefBindingRequired, RObject{} };
            }

            auto index = (m_functors[detail::call_by::value] != nullptr ? detail::call_by::value : detail::call_by::cref);
            return m_hop[index](p_alloc_on, std::forward<args_t>(params)...);
        }

        template<class ...fwd_args_t>
        struct perfect_fwd
        {
            const constructor<signature_t...>& fn;
            
            template<class ...args_t>
            [[nodiscard]] [[gnu::hot]] [[gnu::flatten]]
            constexpr Return operator()(alloc p_alloc_on, args_t&&...params) const noexcept
            {
                if (!fn) [[unlikely]] {
                    return { fn.m_init_err, RObject{} };
                }

                auto signature_id = traits::uid<traits::strict_sign_id_t<fwd_args_t...>>::value;
                for (int index = 0; index < fn.m_functors.size(); index++)
                {
                    if (fn.m_functors[index] != nullptr &&
                        signature_id == fn.m_functors[index]->get_strict_sign_id()) {
                        return fn.m_hop[index](p_alloc_on, std::forward<args_t>(params)...);
                    }
                }
                return { error::RefBindingMismatch, RObject{} };
            }
        };

        template<class ...args_t>
            requires (std::is_same_v<traits::normal_sign_id_t<args_t...>, std::tuple<signature_t...>>)
        constexpr const perfect_fwd<args_t...> bind() const noexcept {
            return perfect_fwd<args_t...>{ *this };
        }

        friend Record;

        static_assert((!std::is_reference_v<signature_t> && ...),
            "rtl::function<...>: any type cannot be specified as reference here");
    };
}