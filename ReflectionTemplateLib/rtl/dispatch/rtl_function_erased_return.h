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
#include "lambda_base.h"

namespace rtl
{
    template<class ...signature_t>
    struct function<Return(signature_t...)>
    {
        constexpr operator bool() const {
            return (!m_lambda.empty());
        }

        template<class ...args_t>
        [[nodiscard]]
        constexpr Return operator()(args_t&&...params) const noexcept
        {
            if (m_lambda.empty()) [[unlikely]] {
                return { error::InvalidCaller, RObject{} };
            }

            if (m_lambda[call_by::value] == nullptr && 
               (m_lambda.size() > call_by::ref || 
                m_lambda[call_by::cref]->is_any_ncref()) ) [[unlikely]]
            {
                return { error::ExplicitRefBindingRequired, RObject{} };
            }

            auto index = (m_lambda[call_by::value] != nullptr ? call_by::value : call_by::cref);
            if (m_lambda[index]->is_void())
            {
                m_void_hop[index](*m_lambda[index], std::forward<args_t>(params)...);
                return { error::None, RObject{} };
            }
            else {

                return{ error::None,
                        RObject{ m_any_hop[index](*m_lambda[index], std::forward<args_t>(params)...),
                                 m_robj_id, nullptr }
                };
            }
        }


        template<class ...args_t>
        requires (std::is_same_v<traits::normal_sign_id_t<args_t...>, std::tuple<signature_t...>> == true)
        [[nodiscard]]
        constexpr Return call(args_t&&...params) const noexcept
        {
            auto signature_id = traits::uid<traits::strict_sign_id_t<args_t...>>::value;
            for (int index = 0; index < m_lambda.size(); index++)
            {
                if (signature_id == m_lambda[index]->get_strict_sign_id())
                {
                    if (m_lambda[index]->is_void())
                    {
                        m_void_hop[index](*m_lambda[index], std::forward<args_t>(params)...);
                        return { error::None, RObject{} };
                    }
                    else {

                        return{ error::None,
                                RObject{ m_any_hop[index](*m_lambda[index], std::forward<args_t>(params)...),
                                         m_robj_id, nullptr }
                        };
                    }
                }
            }
            return { error::InvalidCaller, RObject{} };
        }

    private:

        using lambda_vt = std::function<void(const dispatch::lambda_base&, signature_t...)>;

        using lambda_rt = std::function<std::any(const dispatch::lambda_base&, signature_t...)>;

        detail::RObjectId m_robj_id = {};

        std::vector<lambda_rt> m_any_hop = {};

        std::vector<lambda_vt> m_void_hop = {};

        std::vector<dispatch::lambda_base*> m_lambda = {};

        enum call_by
        {
            value = 0,
            cref = 1,
            ref = 2
        };

        static_assert((!std::is_reference_v<signature_t> && ...),
                       "function<Return(signature_t...)>: any type cannot be reference here");
    };
}