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

#include "RObjectId.h"
#include "erased_method.h"

namespace rtl::erase
{
    template<class record_t, class return_t, class ...signature_ts>
    struct aware_method : public erased_method<record_t, signature_ts...>
    {
        using base_t = erased_method<record_t, signature_ts...>;
        
        using this_t = aware_method<record_t, return_t, signature_ts...>;

        rtl::method<return_t(record_t::*)(signature_ts...)> m_method;

        aware_method()
        {
            constexpr bool isConstCastSafe = (!traits::is_const_v<return_t>);

            base_t::hopper = hopper;
            base_t::robj_id = detail::RObjectId::create<return_t, alloc::Stack>(isConstCastSafe);
        }

        constexpr static void hopper(const base_t* p_this, std::optional<std::any>& p_return, const record_t& p_target, signature_ts&&...params) noexcept
        {
            auto this_p = static_cast<const this_t*>(p_this);

            if constexpr (std::is_void_v<return_t>) {
                this_p->m_method(const_cast<record_t&>(p_target), std::forward<signature_ts>(params)...);
            }
            else {
                auto&& ret_v = this_p->m_method(const_cast<record_t&>(p_target), std::forward<signature_ts>(params)...);

                if constexpr (std::is_pointer_v<return_t>)
                {
                    using raw_t = std::remove_pointer_t<return_t>;
                    p_return.emplace(static_cast<const raw_t*>(ret_v));
                }
                else if constexpr (std::is_reference_v<return_t>)
                {
                    using raw_t = std::remove_cv_t<std::remove_reference_t<return_t>>;
                    p_return.emplace(static_cast<const raw_t*>(&ret_v));
                }
                else
                {
                    using rconst_t = std::add_const_t<std::remove_reference_t<decltype(ret_v)>>;
                    p_return.emplace(rconst_t(std::forward<decltype(ret_v)>(ret_v)));
                }
            }
        }
    };
}