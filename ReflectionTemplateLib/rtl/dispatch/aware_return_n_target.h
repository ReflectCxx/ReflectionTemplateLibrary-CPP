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

#include <dispatch/method_ptr.h>
#include <detail/inc/RObjectBuilder.hpp>

namespace rtl::dispatch
{
    template<class record_t, class return_t, class ...signature_t>
    struct aware_return_n_target
    {
        constexpr static auto erased_target_aware_return(const functor& fn, const RObject& p_target,
                                                         traits::normal_sign_t<signature_t>&&... params) noexcept
        {
            const auto& target = p_target.view<record_t>()->get();
            auto mptr = static_cast<const method_ptr<record_t, return_t, signature_t...>&>(fn).f_ptr();

            if constexpr (std::is_void_v<return_t>) 
            {
                (const_cast<record_t&>(target).*mptr)(std::forward<signature_t>(params)...);
                return std::make_pair(error::None, std::optional<void*>());
            }
            else
            {
                auto&& ret_v = (const_cast<record_t&>(target).*mptr)(std::forward<signature_t>(params)...);
                if constexpr (std::is_reference_v<return_t>) {
                    return std::make_pair(error::None, std::optional<std::remove_reference_t<return_t>*>(&ret_v));
                }
                else {
                    return std::make_pair(error::None, std::optional<return_t>(std::in_place, std::move(ret_v)));
                }
            }
        }

        
        constexpr static Return erased_return_aware_target(const functor& fn, const record_t& p_target,
                                                           traits::normal_sign_t<signature_t>&&...params) noexcept
        {
            auto mptr = static_cast<const method_ptr<record_t, return_t, signature_t...>&>(fn).f_ptr();

            if constexpr (std::is_void_v<return_t>)
            {
                (const_cast<record_t&>(p_target).*mptr)(std::forward<signature_t>(params)...);
                return { error::None, RObject{} };
            }
            else
            {
                constexpr bool isConstCastSafe = (!traits::is_const_v<return_t>);
                auto&& ret_v = (const_cast<record_t&>(p_target).*mptr)(std::forward<signature_t>(params)...);

                if constexpr (std::is_reference_v<return_t>) {
                    return { error::None,
                             detail::RObjectBuilder<const traits::raw_t<return_t>*>::template
                             build<alloc::Stack>(&ret_v, isConstCastSafe)
                    };
                }
                else {
                    return { error::None,
                             detail::RObjectBuilder<decltype(ret_v)>::template
                             build<alloc::Stack>(std::forward<decltype(ret_v)>(ret_v), isConstCastSafe)
                    };
                }
            }
        }

        
        constexpr static Return erased_return_and_target(const functor& fn, const RObject& p_target,
                                                         traits::normal_sign_t<signature_t>&&... params) noexcept
        {
            const auto& target = p_target.view<record_t>()->get();
            auto mptr = static_cast<const method_ptr<record_t, return_t, signature_t...>&>(fn).f_ptr();

            if constexpr (std::is_void_v<return_t>)
            {
                (const_cast<record_t&>(target).*mptr)(std::forward<signature_t>(params)...);
                return { error::None, RObject{} };
            }
            else
            {
                constexpr bool isConstCastSafe = (!traits::is_const_v<return_t>);
                auto&& ret_v = (const_cast<record_t&>(target).*mptr)(std::forward<signature_t>(params)...);

                if constexpr (std::is_reference_v<return_t>) {
                    return { error::None,
                             detail::RObjectBuilder<const traits::raw_t<return_t>*>::template
                             build<alloc::Stack>(&ret_v, isConstCastSafe)
                    };
                }
                else {
                    return { error::None,
                             detail::RObjectBuilder<decltype(ret_v)>::template
                             build<alloc::Stack>(std::forward<decltype(ret_v)>(ret_v), isConstCastSafe)
                    };
                }
            }
        }
    };
}