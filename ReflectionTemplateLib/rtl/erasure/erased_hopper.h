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

#include <functional>

#include "erasure_base.h"

namespace rtl::dispatch::erase
{
    template<class ...normal_sign_t>
    struct erased_hopper : public erasure_base
    {
        using lambda_vt = std::function<void(const lambda_base&, normal_sign_t...)>;

        using lambda_rt = std::function<std::any(const lambda_base&, normal_sign_t...)>;

        using lambda_robj_vt = std::function<void(const lambda_base&, const RObject&, normal_sign_t...)>;

        using lambda_robj_rt = std::function<std::any(const lambda_base&, const RObject&, normal_sign_t...)>;

        GETTER_CREF(lambda_vt, _void_hopper, m_vhopper)
        GETTER_CREF(lambda_rt, _return_hopper, m_rhopper)
        GETTER_CREF(lambda_robj_vt, _void_method_hopper, m_vmhopper)
        GETTER_CREF(lambda_robj_rt, _return_method_hopper, m_rmhopper)

    protected:

        lambda_vt m_vhopper;

        lambda_rt m_rhopper;

        lambda_robj_vt m_vmhopper;

        lambda_robj_rt m_rmhopper;

        erased_hopper( const dispatch::functor& p_functor,
                       const lambda_vt& p_void_hop,
                       const lambda_rt& p_any_ret_hop,
                       const detail::RObjectId& p_ret_id ) noexcept

            : erasure_base(p_functor, p_ret_id)
            , m_vhopper(p_void_hop)
            , m_rhopper(p_any_ret_hop)
        { }

        erased_hopper( const dispatch::functor& p_functor,
                       const lambda_robj_vt& p_void_method_hop,
                       const lambda_robj_rt& p_any_ret_method_hop,
                       const detail::RObjectId& p_ret_id ) noexcept

            : erasure_base(p_functor, p_ret_id)
            , m_vmhopper(p_void_method_hop)
            , m_rmhopper(p_any_ret_method_hop)
        { }
    };
}