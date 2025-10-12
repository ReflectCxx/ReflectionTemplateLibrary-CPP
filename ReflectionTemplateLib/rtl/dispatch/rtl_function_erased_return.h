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
    template<class ...norm_sign_t>
    struct function<Return(norm_sign_t...)>
    {
        constexpr operator bool() const {
            return (!m_any_hop.empty() || !m_void_hop.empty());
        }

        template<class ...args_t>
        [[nodiscard]]
        Return operator()(args_t&&...params) const noexcept
        {
            if (!m_void_hop.empty()) 
            {
                auto& lambda_f = (m_void_hop[0].second);
                auto& lambda_b = *(m_void_hop[0].first);

                lambda_f(lambda_b, std::forward<args_t>(params)...);
                return { error::None, RObject{} };
            }
            else if (!m_any_hop.empty()) {

                auto& lambda_f = (m_any_hop[0].second);
                auto& lambda_b = *(m_any_hop[0].first);

                return{ error::None,  
                        RObject{ lambda_f(lambda_b, std::forward<args_t>(params)...), 
                                 m_robj_id, nullptr}
                };
            }
            else [[unlikely]] {
                return { error::InvalidCaller, RObject{} };
            }
        }

    private:

        using lambda_vt = std::function<void(const dispatch::lambda_base&, norm_sign_t...)>;

        using lambda_rt = std::function<std::any(const dispatch::lambda_base&, norm_sign_t...)>;

        std::vector<std::pair<const dispatch::lambda_base*, lambda_rt>> m_any_hop = {};

        std::vector<std::pair<const dispatch::lambda_base*, lambda_vt>> m_void_hop = {};

        detail::RObjectId m_robj_id = {};
    };
}