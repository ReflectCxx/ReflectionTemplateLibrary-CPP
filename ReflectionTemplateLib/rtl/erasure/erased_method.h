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

#include <any>
#include <functional>

#include "erased_function.h"
#include "rtl_forward_decls.h"

namespace rtl::erase
{
    template<class record_t, class ...normal_sign_t>
    class erased_method_hop : public erased_hopper<normal_sign_t...>
    {
        using base_t = erased_hopper<normal_sign_t...>;

        using this_t = erased_method_hop<record_t, normal_sign_t...>;

        using lambda_vt = std::function<void(const this_t&, const record_t&, normal_sign_t...)>;

        using lambda_rt = std::function<std::any(const this_t&, const record_t&, normal_sign_t...)>;

        lambda_vt m_void_hop;

        lambda_rt m_any_ret_hop;

    protected:

        erased_method_hop( const dispatch::functor& p_functor,
                           const detail::RObjectId& p_robj_id, 
                           const lambda_vt& p_void_hop,
                           const lambda_rt& p_any_ret_hop,
                           const base_t::lambda_robj_vt& p_void_robj_hop,
                           const base_t::lambda_robj_rt& p_any_ret_robj_hop ) noexcept

            : base_t(p_functor, p_robj_id, p_void_robj_hop, p_any_ret_robj_hop)
            , m_void_hop(p_void_hop)
            , m_any_ret_hop(p_any_ret_hop)
        { }

    public:

        constexpr void hop_void(const record_t& p_target, normal_sign_t&&...params) const noexcept
        {
            m_void_hop(*this, p_target, std::forward<normal_sign_t>(params)...);
        }

        ForceInline std::any hop_return(const record_t& p_target, normal_sign_t&&...params) const noexcept
        {
            return m_any_ret_hop(*this, p_target, std::forward<normal_sign_t>(params)...);
        }
    };
}