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

#include "erased_hopper.h"
#include "rtl_forward_decls.h"

namespace rtl::dispatch::erase
{
    template<class record_t, class ...normal_sign_t>
    struct erased_hopper_rec : public erased_hopper<normal_sign_t...>
    {
        using lambda_vt = std::function<void(const lambda_base&, const record_t&, normal_sign_t...)>;

        using lambda_rt = std::function<std::any(const lambda_base&, const record_t&, normal_sign_t...)>;

        GETTER(lambda_vt, _void_hopper, m_void_hop)
            
        GETTER(lambda_rt, _return_hopper, m_any_ret_hop)

    protected:

        lambda_vt m_void_hop;

        lambda_rt m_any_ret_hop;

        using base_t = erased_hopper<normal_sign_t...>;

        erased_hopper_rec( const dispatch::functor& p_functor,
                           const detail::RObjectId& p_robj_id, 
                           const lambda_vt& p_void_hop,
                           const lambda_rt& p_any_ret_hop,
                           const base_t::lambda_robj_vt& p_void_robj_hop,
                           const base_t::lambda_robj_rt& p_any_ret_robj_hop ) noexcept

            : base_t(p_functor, p_robj_id, p_void_robj_hop, p_any_ret_robj_hop)
            , m_void_hop(p_void_hop)
            , m_any_ret_hop(p_any_ret_hop)
        { }
    };
}