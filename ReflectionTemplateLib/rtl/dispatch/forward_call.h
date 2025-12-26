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
    template<class lambda_t>
    struct forward_call
    {
        error m_init_err = error::InvalidCaller;

        std::vector<lambda_t> m_hopper = {};
        std::vector<const functor*> m_functors = {};

        GETTER_REF(std::vector<lambda_t>, _hopper, m_hopper)
        GETTER_REF(std::vector<const functor*>, _overloads, m_functors)

        void set_init_error(error p_err) {
            m_init_err = p_err;
        }

        GETTER(error, _init_error, m_init_err)

        constexpr operator bool() const noexcept
        {
            return !( m_init_err != error::None || m_functors.empty() ||
                     (m_functors.size() == 1 && m_functors[0] == nullptr) );
        }

	protected:

        constexpr bool must_bind_refs() const noexcept {

            return ( m_functors[detail::call_by::value] == nullptr && 
                     m_functors.size() > detail::call_by::ncref );
        }

        template<class ...args_t>
        constexpr Return operator()(args_t&&...params) const noexcept 
        {
            if (must_bind_refs()) [[unlikely]] {
                return { error::ExplicitRefBindingRequired, RObject{} };
            }

            auto index = ( m_functors[detail::call_by::value] != nullptr ? 
                           detail::call_by::value : detail::call_by::cref );

            return m_hopper[index](*m_functors[index], std::forward<args_t>(params)...);
        }

        template<detail::member, class ...>
        friend struct detail::HopFunction;

        template<class , class ...>
        friend struct detail::HopMethod;
	};

    template<class ...args_t>
    using stdfn_t = std::function < rtl::Return(const dispatch::functor&, args_t...) >;

    template<class ...args_t>
    using stdfn_mt = std::function < rtl::Return(const dispatch::functor&, const RObject&, args_t...) >;

    template<class ...args_t>
    using reflect_fn = forward_call<stdfn_t<args_t...>>;

    template<class ...args_t>
    using reflect_mth = forward_call<stdfn_mt<args_t...>>;
}