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

#include "rtl_constants.h"
#include "rtl_forward_decls.h"

namespace rtl::dispatch
{
    struct functor
    {
        constexpr bool is_void() const {
            return m_is_void;
        }

        GETTER_CPTR(lambda_base, _lambda, m_lambda)

    protected:

        std::string m_recordStr;
        std::string m_returnStr;
        std::string m_signatureStr;

        traits::uid_t m_recordId = traits::uid<>::none;
        traits::uid_t m_returnId = traits::uid<>::none;

        traits::uid_t m_normal_signId = traits::uid<>::none;
        traits::uid_t m_strict_signId = traits::uid<>::none;

        bool m_is_void = false;
        bool m_is_any_ncref = false;
        std::vector<std::size_t> m_argumentsId = {};

        detail::methodQ m_qualifier = detail::methodQ::None;

    private:

        constexpr void set_lambda(const lambda_base* p_lambda) const {
            m_lambda = p_lambda;
        }

        mutable const lambda_base* m_lambda = nullptr;

        friend lambda_base;

        template<class ...>
        friend struct lambda_function;

        template<class, class ...>
        friend struct lambda_method;

        template<class, class ...>
        friend struct cache::lambda_function;

        template<class, class, class ...>
        friend struct cache::lambda_method;
    };
}