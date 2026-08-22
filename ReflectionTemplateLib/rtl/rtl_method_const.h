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

#include <rtl_traits.h>

namespace rtl
{
    template<class record_t, class return_t, class... signature_t>
    requires (!std::is_same_v<record_t, RObject> && !std::is_same_v<return_t, Return>)
    struct const_method<record_t, return_t(signature_t...)>
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

        explicit const_method(fptr_t p_functor)
            : m_init_err(error::None)
            , m_functor(p_functor)
        { }

        const_method() = default;
        const_method(const_method&&) = default;
        const_method(const const_method&) = default;

        const_method& operator=(const_method&&) = default;
        const_method& operator=(const const_method&) = default;

        GETTER(rtl::error, _init_error, m_init_err)

    private:

        fptr_t m_functor = nullptr;
        error m_init_err = error::InvalidCaller;

        void set_record_id(const traits::uid_t) {}

        void set_init_error(error p_err) {
            m_init_err = p_err;
        }

        template<detail::member, class, class ...>
        friend struct detail::InitMethodHop;

        static_assert(!std::is_const_v<record_t>, "rtl::const_method<...>: 'record_t' must not be specified as 'const'.");
    };
}