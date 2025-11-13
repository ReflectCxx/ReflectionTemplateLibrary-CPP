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
#include "aware_return.h"
#include "aware_constructor.h"

namespace rtl::dispatch
{
    template<class ...normal_sign_t>
    struct erase_return : public erasure_base
    {
        using lambda_vt = std::function<void(const lambda_base&, normal_sign_t...)>;

        using lambda_rt = std::function<std::any(const lambda_base&, normal_sign_t...)>;

        using lambda_ctor_t = std::function<Return(alloc, normal_sign_t...)>;

        GETTER_CREF(lambda_vt, _void_hopper, m_vhopper)
        GETTER_CREF(lambda_rt, _return_hopper, m_rhopper)

    private:

        lambda_vt m_vhopper = nullptr;

        lambda_rt m_rhopper = nullptr;

        lambda_ctor_t m_ctor_hopper = nullptr;

        template<detail::member mem_kind, class return_t, class...signature_t>
        void init_lambdas()
        {
            if constexpr (mem_kind == detail::member::UserCtor)
            {
                using record_t = return_t;
                m_ctor_hopper = aware_constructor<record_t, signature_t...>::get_allocator();
            }
            else
            {
                if constexpr (std::is_void_v<return_t>) {
                    m_vhopper = aware_return<return_t, signature_t...>::get_lambda_void();
                }
                else {
                    m_rhopper = aware_return<return_t, signature_t...>::get_lambda_any_return();
                }
                constexpr static bool is_const_cast_safe = (!traits::is_const_v<return_t>);
                m_return_id = detail::RObjectId::create<return_t, alloc::Stack>(is_const_cast_safe);
            }
        }

        template<class, class...>
        friend struct cache::lambda_function;
    };
}