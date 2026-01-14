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

#include <dispatch/forward_call.h>

namespace rtl
{
    template<class record_t, class ...signature_t> requires (!std::is_same_v<record_t, RObject>)
    struct method<record_t, Return(signature_t...)>
    {
        using hopper_t = dispatch::forward_call<Return, const record_t&, signature_t...>;

        struct invoker
        {
            const hopper_t& fn;
            const record_t& target;

            template<class ...args_t> requires (sizeof...(args_t) == sizeof...(signature_t))
            [[nodiscard]] [[gnu::hot]] [[gnu::flatten]]
            constexpr Return operator()(args_t&&...params) const noexcept
            {
                if (!fn) [[unlikely]] {
                    return { fn.get_init_error(), RObject{}};
                }
                return fn(target, std::forward<args_t>(params)...);
            }
        };

        template<class ...fwd_args_t>
        struct perfect_fwd
        {
            const hopper_t& fn;
            const record_t& target;

            template<class ...args_t>
            [[nodiscard]] [[gnu::hot]] [[gnu::flatten]]
            constexpr Return operator()(args_t&&...params) const noexcept
            {
                if (!fn) [[unlikely]] {
                    return { fn.get_init_error(), RObject{}};
                }
                auto sign_id = traits::uid<traits::strict_sign_id_t<fwd_args_t...>>::value;
                return fn.perfect_forward(sign_id, target, std::forward<args_t>(params)...);
            }
        };

        constexpr invoker operator()(record_t& p_target) const noexcept {
            return invoker{ m_non_const_hops, p_target };
        }

        constexpr invoker operator()(record_t&& p_target) const noexcept {
            return invoker{ m_non_const_hops, p_target };
        }

        template<class ...args_t>
        requires (std::is_same_v<traits::normal_sign_id_t<args_t...>, std::tuple<signature_t...>>)
        constexpr const perfect_fwd<args_t...> bind(record_t& p_target) const noexcept {
            return perfect_fwd<args_t...>{ m_non_const_hops, p_target };
        }

        template<class ...args_t>
        requires (std::is_same_v<traits::normal_sign_id_t<args_t...>, std::tuple<signature_t...>>)
        constexpr const perfect_fwd<args_t...> bind(record_t&& p_target) const noexcept {
            return perfect_fwd<args_t...>{ m_non_const_hops, p_target };
        }

        constexpr operator bool() const noexcept {
            return (m_const_hops.operator bool() || m_non_const_hops.operator bool());
        }

        constexpr error get_init_error() const noexcept
        {
            if (m_const_hops.get_init_error() == error::None ||
                m_non_const_hops.get_init_error() == error::None) {
                return error::None;
            }
            return m_non_const_hops.get_init_error();
        }

    private:

        hopper_t m_const_hops;
        hopper_t m_non_const_hops;

        GETTER_REF(hopper_t, _c_hops, m_const_hops)
        GETTER_REF(hopper_t, _nc_hops, m_non_const_hops)

        template<detail::member, class, class ...>
        friend struct detail::InitMethodHop;

        static_assert((!std::is_reference_v<signature_t> && ...),
                      "rtl::method<...>: any type cannot be specified as reference here.");
    };
}