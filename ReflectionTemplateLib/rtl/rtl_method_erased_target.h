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
    template<class return_t, class ...signature_t> requires (!std::is_same_v<return_t, Return>)
    struct method<RObject, return_t(signature_t...)>
    {
        using cond_ret_t = std::conditional_t<std::is_void_v<return_t>, std::nullptr_t, return_t>;

        using hopper_t = dispatch::forward_call<std::pair<error, std::optional<cond_ret_t>>, const RObject&, signature_t...>;

        struct invoker
        {
            const hopper_t& fn;
            const error init_err;
            const RObject& target;

            template<class ...args_t> 
                requires (sizeof...(args_t) == sizeof...(signature_t))
            [[nodiscard]] [[gnu::hot]] [[gnu::flatten]]
            constexpr std::pair<error, std::optional<cond_ret_t>> operator()(args_t&&...params) const noexcept
            {
                if (init_err != error::None) [[unlikely]] {
                    return { init_err, std::nullopt };
                }

                auto&& ret_v = fn(target, std::forward<args_t>(params)...);
                if constexpr (std::is_void_v<return_t>) {
                    ret_v.second = std::nullopt;
                }
                return ret_v;
            }
        };

        template<class ...fwd_args_t>
        struct perfect_fwd
        {
            const hopper_t& fn;
            const error init_err;
            const RObject& target;
            
            template<class ...args_t>
            [[nodiscard]] [[gnu::hot]] [[gnu::flatten]]
            constexpr std::pair<error, std::optional<cond_ret_t>> operator()(args_t&&...params) const noexcept
            {
                if (init_err != error::None) [[unlikely]] {
                    return { init_err, std::nullopt };
                }

                auto sign_id = traits::uid<traits::strict_sign_id_t<fwd_args_t...>>::value;
                auto&& ret_v = fn.perfect_forward(sign_id, target, std::forward<args_t>(params)...);
                if constexpr (std::is_void_v<return_t>) {
                    ret_v.second = std::nullopt;
                }
                return ret_v;
            }
        };

        constexpr const error validate(const hopper_t& pHopper, const RObject& p_target) const
        {
            if (pHopper.get_init_error() != error::None) {
                return pHopper.get_init_error();
            }
            else if (p_target.isEmpty()) {
                return error::EmptyRObject;
            }
            else if (pHopper.get_record_id() != p_target.getTypeId()) {
                return error::TargetTypeMismatch;
            }
            else return error::None;
        }

        constexpr invoker operator()(RObject& p_target) const noexcept {
            return invoker{ m_non_const_hops, validate(m_non_const_hops, p_target), p_target };
        }

        constexpr invoker operator()(RObject&& p_target) const noexcept {
            return invoker{ m_non_const_hops, validate(m_non_const_hops, p_target), p_target };
        }

        constexpr invoker operator()(const RObject& p_target) const noexcept {
            return invoker{ m_const_hops, validate(m_const_hops, p_target), p_target };
        }

        template<class ...args_t>
            requires (std::is_same_v<traits::normal_sign_id_t<args_t...>, std::tuple<signature_t...>>)
        constexpr const perfect_fwd<args_t...> bind(RObject& p_target) const noexcept {
            return perfect_fwd<args_t...>{ m_non_const_hops, validate(m_non_const_hops, p_target), p_target };
        }

        template<class ...args_t>
            requires (std::is_same_v<traits::normal_sign_id_t<args_t...>, std::tuple<signature_t...>>)
        constexpr const perfect_fwd<args_t...> bind(RObject&& p_target) const noexcept {
            return perfect_fwd<args_t...>{ m_non_const_hops, validate(m_non_const_hops, p_target), p_target };
        }

        template<class ...args_t>
            requires (std::is_same_v<traits::normal_sign_id_t<args_t...>, std::tuple<signature_t...>>)
        constexpr const perfect_fwd<args_t...> bind(const RObject& p_target) const noexcept {
            return perfect_fwd<args_t...>{ m_const_hops, validate(m_const_hops, p_target), p_target };
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