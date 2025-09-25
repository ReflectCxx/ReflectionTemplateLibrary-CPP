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


namespace rtl
{
    template<class record_t, class return_t, class... signature_ts>
    struct method<return_t(record_t::*)(signature_ts...) const>
    {
        using fptr_t = return_t(record_t::*)(signature_ts...) const;

        const fptr_t m_functor = nullptr;

        constexpr auto f_ptr() const {
            return m_functor;
        }

        constexpr operator bool() const {
            return (m_functor != nullptr);
        }

        template<class ...args_t>
        [[nodiscard]] constexpr decltype(auto) operator()(record_t& target, args_t&&...params) const noexcept(noexcept_v<args_t...>)
        {
            static_assert(is_args_t_ok<args_t...>, "Argument types don't match the expected signature.");
            return (target.*m_functor)(std::forward<args_t>(params)...);
        }

    private:

        template<class ...args_t>
        static constexpr bool is_args_t_ok = std::is_same_v<std::tuple<traits::raw_t<args_t>...>, std::tuple<signature_ts...>>;

        template<class ...args_t>
        static constexpr bool noexcept_v = noexcept((std::declval<record_t>().*std::declval<fptr_t>())(std::declval<args_t>()...));
    };
}