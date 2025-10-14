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
    struct method<record_t, return_t(signature_t...)>
    {
        using fptr_t = return_t (record_t::*)(signature_t...);

        constexpr auto f_ptr() const {
            return m_functor;
        }

        constexpr operator bool() const {
            return (m_functor != nullptr);
        }

        template<class ...args_t>
        [[nodiscard]] constexpr decltype(auto) operator()(record_t& target, args_t&&...params) const noexcept
        {
            return (target.*m_functor)(std::forward<args_t>(params)...);
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