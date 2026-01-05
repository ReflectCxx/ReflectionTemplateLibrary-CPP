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

#include "forward_call.h"

namespace rtl
{
    template<class record_t, class ...signature_t> requires (!std::is_same_v<record_t, RObject>)
    struct method<record_t, Return(signature_t...)> : public dispatch::forward_call<Return, const record_t&, signature_t...>
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
            return invoker{ *this, p_target};
        }

        constexpr invoker operator()(record_t&& p_target) const noexcept {
            return invoker{ *this, p_target};
        }

        template<class ...args_t>
        requires (std::is_same_v<traits::normal_sign_id_t<args_t...>, std::tuple<signature_t...>>)
        constexpr const perfect_fwd<args_t...> bind(record_t& p_target) const noexcept {
            return perfect_fwd<args_t...>{ *this, p_target };
        }

        template<class ...args_t>
        requires (std::is_same_v<traits::normal_sign_id_t<args_t...>, std::tuple<signature_t...>>)
        constexpr const perfect_fwd<args_t...> bind(record_t&& p_target) const noexcept {
            return perfect_fwd<args_t...>{ *this, p_target };
        }

        constexpr void set_record_id(const traits::uid_t) { }

        static_assert((!std::is_reference_v<signature_t> && ...),
                      "rtl::method<...>: any type cannot be specified as reference here.");
    };
}