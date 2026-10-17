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

#include <dispatch/functor.h>

namespace rtl::dispatch
{
    template<class return_t, class ...signature_t>
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
        constexpr return_t operator()(args_t&&...params) const noexcept
        {
            if (must_bind_refs()) [[unlikely]] {
                if constexpr (std::is_same_v<return_t, Return>) {
                    return { error::ExplicitRefBindingRequired, RObject{} };
                }
                else {
                    return { error::ExplicitRefBindingRequired, std::nullopt };
                }
            }
            auto index = ( m_functors[detail::call_by::value] != nullptr ? 
                           detail::call_by::value : detail::call_by::cref );

            return m_hopper[index](*m_functors[index], std::forward<args_t>(params)...);
        }

        template<class ...args_t>
        [[gnu::hot]] [[gnu::flatten]]
        constexpr return_t perfect_forward(const traits::uid_t p_sign_id, args_t&&...params) const noexcept
        {
            for (int index = 0; index < m_functors.size(); index++)
            {
                if (m_functors[index] != nullptr &&
                    m_functors[index]->get_strict_sign_id() == p_sign_id) {

                    return m_hopper[index](*m_functors[index], std::forward<args_t>(params)...);
                }
            }
            if constexpr (std::is_same_v<return_t, Return>) {
                return { error::RefBindingMismatch, RObject{} };
            }
            else {
                return { error::RefBindingMismatch, std::nullopt };
            }
        }

        constexpr const error get_init_error() const {
            return m_init_err;
        }

        constexpr const traits::uid_t get_record_id() const {
            return m_record_id;
        }

    private:

        using lambda_t = std::function<return_t(const functor&, signature_t...)>;

        error m_init_err = error::InvalidCaller;
        traits::uid_t m_record_id = traits::uid<>::none;

        std::vector<lambda_t> m_hopper = {};
        std::vector<const functor*> m_functors = {};

        constexpr std::vector<lambda_t>& get_hopper() {
            return m_hopper;
        }

        constexpr std::vector<const functor*>& get_overloads() {
            return m_functors;
        }

        void set_init_error(error p_err) {
            m_init_err = p_err;
        }

        constexpr void set_record_id(const traits::uid_t p_recid) {
            m_record_id = p_recid;
        }

        template<detail::member, class...>
        friend struct detail::InitFunctionHop;

        template<detail::member, class, class...>
        friend struct detail::InitMethodHop;
	};
}