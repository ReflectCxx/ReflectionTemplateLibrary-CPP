/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#pragma once

#include <dispatch/function_ptr.h>
#include <detail/inc/RObjectBuilder.hpp>

namespace rtl::dispatch
{
    template<class return_t, class ...signature_t>
    struct aware_return
    {
        constexpr static Return get_lambda_any_return(const functor& fn, traits::normal_sign_t<signature_t>&&... params) noexcept
        {
            auto fptr = static_cast<const function_ptr<return_t, signature_t...>&>(fn).f_ptr();

            if constexpr (std::is_void_v<return_t>)
            {
                (*fptr)(std::forward<signature_t>(params)...);
                return { error::None, RObject{} };
            }
            else
            {
                constexpr bool isConstCastSafe = (!traits::is_const_v<return_t>);
                if constexpr (std::is_reference_v<return_t>) {

                    using raw_t = traits::raw_t<return_t>;
                    const raw_t& ret_v = (*fptr)(std::forward<signature_t>(params)...);
                    return { error::None,
                             detail::RObjectBuilder<const raw_t*>::template
                             build<alloc::Stack>(&ret_v, isConstCastSafe)
                    };
                }
                else {

                    auto&& ret_v = (*fptr)(std::forward<signature_t>(params)...);
                    return { error::None,
                             detail::RObjectBuilder<decltype(ret_v)>::template
                             build<alloc::Stack>(std::forward<decltype(ret_v)>(ret_v), isConstCastSafe)
                    };
                }
            }
        }
    };
}