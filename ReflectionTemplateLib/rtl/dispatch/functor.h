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
        GETTER_BOOL(_void, m_is_void)
        GETTER_BOOL(_any_arg_ncref, m_is_any_arg_ncref)
        GETTER(traits::uid_t, _strict_sign_id, m_strict_args_id)
        GETTER(traits::uid_t, _normal_sign_id, m_normal_args_id)
        GETTER_CREF(detail::RObjectId, _robject_id, m_robject_id)

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

        detail::RObjectId m_robject_id = {};
        detail::member m_member_kind = detail::member::None;
        
        std::vector<lambda*> m_lambdas;
        std::vector<std::size_t> m_args_type_ids = {};

    private:

        constexpr void set_lambda(const dispatch::lambda_base* p_lambda) const {
            m_lambda = p_lambda;
        }

        mutable const dispatch::lambda_base* m_lambda = nullptr;
        
        friend rtl::type_meta;

        friend dispatch::lambda_base;

        template<fn_void, class...>
        friend struct functor_cast;

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