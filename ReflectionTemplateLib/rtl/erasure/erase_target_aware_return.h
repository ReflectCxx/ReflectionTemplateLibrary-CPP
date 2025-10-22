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

#include "erasure_base.h"

namespace rtl::dispatch
{
    template<class return_t, class ...normal_sign_t>
    struct erase_target_aware_return : public erasure_base
    {
        using lambda_vt = std::function<void(const lambda_base&, const rtl::RObject&, normal_sign_t...)>;

        using lambda_rt = std::function<return_t(const lambda_base&, const rtl::RObject&, normal_sign_t...)>;

        GETTER(lambda_vt, _void_hopper, m_vhopper)
            
        GETTER(lambda_rt, _return_hopper, m_rhopper)

    protected:

        lambda_vt m_vhopper;

        lambda_rt m_rhopper;

        erase_target_aware_return( const lambda_vt& p_void_hop,
                                   const lambda_rt& p_any_ret_hop ) noexcept

            : m_vhopper(p_void_hop)
            , m_rhopper(p_any_ret_hop)
        { }

        template<class, class, class ...>
        friend struct aware_return_n_target;
    };
}