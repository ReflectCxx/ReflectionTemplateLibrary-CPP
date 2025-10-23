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
    template<class record_t, class return_t, class... signature_t>
    requires (!std::is_same_v<record_t, RObject> || !std::is_same_v<return_t, Return>)
    struct method<const record_t, return_t(signature_t...)>
    {
        using fptr_t = return_t(record_t::*)(signature_t...) const;

        constexpr auto f_ptr() const {
            return m_functor;
        }

        constexpr operator bool() const {
            return (m_functor != nullptr);
        }

        struct invoker
        {
            fptr_t functor;
            const record_t& target;

            template<class ...args_t>
            requires (sizeof...(args_t) == sizeof...(signature_t))
            [[nodiscard]] [[gnu::hot]]
            constexpr decltype(auto) operator()(args_t&&...params) const noexcept
            {
                return (target.*functor)(std::forward<args_t>(params)...);
            }
        };

        [[gnu::hot]]
        constexpr const invoker operator()(const record_t& p_target) const noexcept {
            return invoker{ m_functor, p_target };
        }

        method(fptr_t p_functor) : m_functor(p_functor)
        { }

        method() = default;
        method(method&&) = default;
        method(const method&) = default;

        method& operator=(method&&) = default;
        method& operator=(const method&) = default;

    private:

        fptr_t m_functor = nullptr;
    };
}