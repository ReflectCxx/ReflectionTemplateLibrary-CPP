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

#include "functor.h"

namespace rtl::dispatch
{
    template<class ...signature_t>
    struct forward_call
    {
        constexpr operator bool() const noexcept {

            return !( m_init_err != error::None || m_functors.empty() ||
                     (m_functors.size() == 1 && m_functors[0] == nullptr) );
        }

        constexpr bool must_bind_refs() const noexcept {

            return ( m_functors[detail::call_by::value] == nullptr && 
                     m_functors.size() > detail::call_by::ncref );
        }

        template<class ...args_t>
        [[gnu::hot]] [[gnu::flatten]]
        constexpr Return operator()(args_t&&...params) const noexcept
        {
            if (must_bind_refs()) [[unlikely]] {
                return { error::ExplicitRefBindingRequired, RObject{} };
            }
            auto index = ( m_functors[detail::call_by::value] != nullptr ? 
                           detail::call_by::value : detail::call_by::cref );

            return m_hopper[index](*m_functors[index], std::forward<args_t>(params)...);
        }

        template<class ...args_t>
        [[gnu::hot]] [[gnu::flatten]]
        constexpr Return perfect_forward(const traits::uid_t p_sign_id, args_t&&...params) const noexcept
        {
            for (int index = 0; index < m_functors.size(); index++)
            {
                if (m_functors[index] != nullptr &&
                    m_functors[index]->get_strict_sign_id() == p_sign_id) {

                    return m_hopper[index](*m_functors[index], std::forward<args_t>(params)...);
                }
            }
            return { error::RefBindingMismatch, RObject{} };
        }

        GETTER(error, _init_error, m_init_err)

    private:

        using lambda_t = std::function<Return(const functor&, signature_t...)>;

        error m_init_err = error::InvalidCaller;

        std::vector<lambda_t> m_hopper = {};
        std::vector<const functor*> m_functors = {};

        GETTER_REF(std::vector<lambda_t>, _hopper, m_hopper)
        GETTER_REF(std::vector<const functor*>, _overloads, m_functors)

        void set_init_error(error p_err) {
            m_init_err = p_err;
        }

        template<detail::member, class ...>
        friend struct detail::HopFunction;

        template<class, class ...>
        friend struct detail::HopMethod;
	};
}