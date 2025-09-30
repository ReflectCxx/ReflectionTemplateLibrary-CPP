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

#include "RObject.h"
#include "erased_function.h"
#include "RObjectBuilder.hpp"

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
            base_t::hop_void = void_hop;
            base_t::hop_return = return_hop;
        }

        constexpr static void void_hop(const base_t* p_this, signature_ts&&...params) noexcept
        {
            if constexpr (std::is_void_v<return_t>)
            {
                auto this_p = static_cast<const this_t*>(p_this);
                this_p->m_function(std::forward<signature_ts>(params)...);
            }
        }


        ForceInline static rtl::Return return_hop(const base_t* p_this, signature_ts&&...params) noexcept
        {
            if constexpr (!std::is_void_v<return_t>)
            {
                auto this_p = static_cast<const this_t*>(p_this);
                auto&& ret_v = this_p->m_function(std::forward<signature_ts>(params)...);

                constexpr bool isConstCastSafe = (!traits::is_const_v<return_t>);

                if constexpr (std::is_reference_v<return_t>) 
                {
                    using T = traits::raw_t<return_t>;
                    return{ error::None, 
                            detail::RObjectBuilder<const T*>::template build<rtl::alloc::Stack> (
                                &ret_v, std::nullopt, isConstCastSafe
                            )
                    };
                }
                else 
                {
                    using T = std::remove_cvref_t<decltype(ret_v)>;
                    return{ error::None,
                            detail::RObjectBuilder<const T>::template build<rtl::alloc::Stack> (
                                std::forward<decltype(ret_v)>(ret_v), std::nullopt, isConstCastSafe
                            )
                    };
                }
            }
            return {error::SignatureMismatch, RObject{ }};
        }
    };
}