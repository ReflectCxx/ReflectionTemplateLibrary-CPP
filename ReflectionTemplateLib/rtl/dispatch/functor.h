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
#include "rtl_constants.h"
#include "rtl_forward_decls.h"

namespace rtl::dispatch
{
    struct functor
    {
        constexpr bool is_void() const {
            return m_is_void;
        }

    protected:

        std::string m_recordStr;
        std::string m_returnStr;
        std::string m_signatureStr;

        traits::uid_t m_recordId = traits::uid<>::none;
        traits::uid_t m_returnId = traits::uid<>::none;

        traits::uid_t m_normal_signId = traits::uid<>::none;
        traits::uid_t m_strict_signId = traits::uid<>::none;

        bool m_is_void = false;
        bool m_is_any_arg_ncref = false;
        std::vector<std::size_t> m_argumentsId = {};

        detail::methodQ m_qualifier = detail::methodQ::None;

    private:

        constexpr void set_lambda(const dispatch::lambda_base* p_lambda) const {
            m_lambda = p_lambda;
        }

        constexpr void set_erased_lambda(const dispatch::erased_fnbase* p_elambda) const {
            m_erased_lambda = p_elambda;
        }

        mutable const dispatch::lambda_base* m_lambda = nullptr;

        mutable const dispatch::erased_fnbase* m_erased_lambda = nullptr;
        
        friend rtl::type_meta;

        friend dispatch::lambda_base;

        template<class ...>
        friend struct dispatch::lambda_function;

        template<class, class ...>
        friend struct dispatch::lambda_method;

        template<class, class ...>
        friend struct cache::lambda_function;

        template<class, class, class ...>
        friend struct cache::lambda_method;
    };
}