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

namespace rtl::dispatch
{
    struct functor
    {
        constexpr bool is_void() const {
            return m_is_void;
        }

    protected:

        enum index {
            erased_ctor = 0,
            erased_return = 0,
            erased_target = 1,
            erased_method = 2
        };

        std::string m_record_str;
        std::string m_return_str;
        std::string m_signature_str;

        traits::uid_t m_record_id = traits::uid<>::none;
        traits::uid_t m_return_id = traits::uid<>::none;

        traits::uid_t m_normal_args_id = traits::uid<>::none;
        traits::uid_t m_strict_args_id = traits::uid<>::none;

        bool m_is_void = false;
        bool m_is_any_arg_ncref = false;
        std::vector<std::size_t> m_args_type_ids = {};

        detail::member m_member_kind = detail::member::None;

        std::vector<lambda*> m_lambdas;

    private:

        constexpr void set_lambda(const dispatch::lambda_base* p_lambda) const {
            m_lambda = p_lambda;
        }

        constexpr void set_erasure(const dispatch::erasure_base* p_elambda) const {
            m_erasure = p_elambda;
        }

        mutable const dispatch::lambda_base* m_lambda = nullptr;

        mutable const dispatch::erasure_base* m_erasure = nullptr;
        
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