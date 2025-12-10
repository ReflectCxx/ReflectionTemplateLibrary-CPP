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
#include "RObject.hpp"

namespace rtl
{
    template<class ...signature_t>
    class constructor
    {
        using lambda_t = std::function<Return(alloc, signature_t...)>;

        error m_init_err = error::InvalidCaller;

        std::vector<lambda_t> m_hop = {};

        std::vector<const dispatch::functor*> m_functors = {};

        void set_init_error(error p_err);

        GETTER_REF(std::vector<lambda_t>, _hop, m_hop)
        GETTER_REF(std::vector<const dispatch::functor*>, _overloads, m_functors)

    public:

        enum call_by {
            value = 0,
            cref = 1,   //const ref.
            ncref = 2   //non-const ref.
        };

        GETTER(rtl::error, _init_error, m_init_err)

        constexpr operator bool() const noexcept;

        template<class ...args_t>
            requires (sizeof...(args_t) == sizeof...(signature_t))
        constexpr Return operator()(args_t&&...params) const noexcept;
    };
}