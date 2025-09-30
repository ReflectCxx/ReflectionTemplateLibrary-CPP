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

#include "erased_function.h"

namespace rtl::erase
{
    template<class return_t, class ...signature_ts>
    struct aware_function : public erased_function<signature_ts...>
    {
        rtl::function<return_t(signature_ts...)> m_function;

        using base_t = erased_function<signature_ts...>;

        using this_t = aware_function<return_t, signature_ts...>;

        aware_function()
        {
            constexpr bool isConstCastSafe = (!traits::is_const_v<return_t>);

            base_t::hopper = hopper;
            base_t::robj_id = detail::RObjectId::create<return_t, alloc::Stack>(isConstCastSafe);
        }

        constexpr static void hopper(const base_t* p_this, std::optional<std::any>& p_return, signature_ts&&...params) noexcept
        {
            auto this_p = static_cast<const this_t*>(p_this);
            
            if constexpr (std::is_void_v<return_t>) {
                this_p->m_function(std::forward<signature_ts>(params)...);
            }
            else {
                auto&& ret_v = this_p->m_function(std::forward<signature_ts>(params)...);

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