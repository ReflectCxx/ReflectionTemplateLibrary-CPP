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
    // TODO: Needs to be well tested, special case return-type 'void' (which does not returns std::nullopt for now)
    template<class return_t, class ...signature_t> requires (!std::is_same_v<return_t, Return>)
    struct method<RObject, return_t(signature_t...)> 
        : public dispatch::forward_call<std::pair<error, std::optional<return_t>>, const RObject&, signature_t...>
    {
        using hopper_t = dispatch::forward_call<std::pair<error, std::optional<return_t>>, const RObject&, signature_t...>;

        struct invoker
        {
            const hopper_t& fn;
            const error init_err;
            const RObject& target;

            template<class ...args_t> 
                requires (sizeof...(args_t) == sizeof...(signature_t))
            [[nodiscard]] [[gnu::hot]] [[gnu::flatten]]
            constexpr std::pair<error, std::optional<return_t>> operator()(args_t&&...params) const noexcept
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
            constexpr std::pair<error, std::optional<return_t>> operator()(args_t&&...params) const noexcept
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

        constexpr const error validate(const RObject& p_target) const
        {
            if (hopper_t::get_init_error() != error::None) {
                return hopper_t::get_init_error();
            }
            else if (p_target.isEmpty()) {
                return error::EmptyRObject;
            }
            else if (m_record_id != p_target.getTypeId()) {
                return error::TargetTypeMismatch;
            }
            else return error::None;
        }

        constexpr invoker operator()(RObject& p_target) const noexcept {
            return invoker{ *this, validate(p_target), p_target };
        }

        constexpr invoker operator()(RObject&& p_target) const noexcept {
            return invoker{ *this, validate(p_target), p_target };
        }

        template<class ...args_t>
            requires (std::is_same_v<traits::normal_sign_id_t<args_t...>, std::tuple<signature_t...>>)
        constexpr const perfect_fwd<args_t...> bind(RObject& p_target) const noexcept {
            return perfect_fwd<args_t...>{ *this, validate(p_target), p_target};
        }

        template<class ...args_t>
            requires (std::is_same_v<traits::normal_sign_id_t<args_t...>, std::tuple<signature_t...>>)
        constexpr const perfect_fwd<args_t...> bind(RObject&& p_target) const noexcept {
            return perfect_fwd<args_t...>{ *this, validate(p_target), p_target};
        }
    private:

        traits::uid_t m_record_id = traits::uid<>::none;

        constexpr void set_record_id(const traits::uid_t p_recid) {
            m_record_id = p_recid;
        }

        template<detail::member, class, class ...>
        friend struct detail::InitMethodHop;

        static_assert((!std::is_reference_v<signature_t> && ...),
            "rtl::method<...>: any type cannot be specified as reference here.");
    };
}