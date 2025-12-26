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
    template<class ...signature_t>
    struct function<Return(signature_t...)> : public dispatch::reflect_fn<signature_t...>
    {
        using base_t = dispatch::reflect_fn<signature_t...>;

        template<class ...args_t>
            requires (sizeof...(args_t) == sizeof...(signature_t))
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
            const function<Return(signature_t...)>& fn;
            
            template<class ...args_t>
            [[nodiscard]] [[gnu::hot]] [[gnu::flatten]]
            constexpr Return operator()(args_t&&...params) const noexcept
            {
                if (!fn) [[unlikely]] {
                    return { fn.m_init_err, RObject{} };
                }

                auto signature_id = traits::uid<traits::strict_sign_id_t<fwd_args_t...>>::value;
                for (int index = 0; index < fn.m_functors.size(); index++)
                {
                    if (fn.m_functors[index] != nullptr &&
                        fn.m_functors[index]->get_strict_sign_id() == signature_id) {

                        return fn.m_hopper[index](*fn.m_functors[index], std::forward<args_t>(params)...);
                    }
                }
                return { error::RefBindingMismatch, RObject{} };
            }
        };

        template<class ...args_t>
            requires (std::is_same_v<traits::normal_sign_id_t<args_t...>, std::tuple<signature_t...>>)
        constexpr const perfect_fwd<args_t...> bind() const noexcept;

        template<detail::member, class ...>
        friend struct detail::HopFunction;

        static_assert((!std::is_reference_v<signature_t> && ...),
            "rtl::function<...>: any type cannot be specified as reference here");
    };
}


namespace rtl
{
    template<class ...signature_t>
    struct static_method<Return(signature_t...)> : function<Return(signature_t...)>
    { 
        template<detail::member, class ...>
        friend struct detail::HopFunction;
    };
}