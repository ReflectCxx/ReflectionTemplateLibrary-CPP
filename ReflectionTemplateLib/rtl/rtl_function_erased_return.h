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
    template<class ...signature_t>
    struct function<Return(signature_t...)> : public dispatch::forward_call<Return, signature_t...>
    {
        using base_t = dispatch::forward_call<Return, signature_t...>;

        template<class ...args_t>
            requires (sizeof...(args_t) == sizeof...(signature_t))
        [[nodiscard]] [[gnu::hot]] [[gnu::flatten]]
        constexpr Return operator()(args_t&&...params) const noexcept
        {
            if (!(*this)) [[unlikely]] {
                return { base_t::get_init_error(), RObject{}};
            }
            return base_t::operator()(std::forward<args_t>(params)...);
        }

        template<class ...fwd_args_t>
        struct perfect_fwd
        {
            const base_t& fn;
            
            template<class ...args_t>
            [[nodiscard]] [[gnu::hot]] [[gnu::flatten]]
            constexpr Return operator()(args_t&&...params) const noexcept
            {
                if (!fn) [[unlikely]] {
                    return { fn.get_init_error(), RObject{}};
                }

                auto sign_id = traits::uid<traits::strict_sign_id_t<fwd_args_t...>>::value;
                return fn.perfect_forward(sign_id, std::forward<args_t>(params)...);
            }
        };

        template<class ...args_t>
            requires (std::is_same_v<traits::normal_sign_id_t<args_t...>, std::tuple<signature_t...>>)
        constexpr const perfect_fwd<args_t...> bind() const noexcept {
            return perfect_fwd<args_t...>{ *this };
        }

        static_assert((!std::is_reference_v<signature_t> && ...),
            "rtl::function<...>: any type cannot be specified as reference here.");
    };
}


namespace rtl
{
    template<class ...signature_t>
    struct static_method<Return(signature_t...)> : function<Return(signature_t...)>
    { };
}