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

#include "method_ptr.h"
#include "RObjectBuilder.hpp"

namespace rtl::dispatch
{
    template<class record_t, class return_t, class ...signature_t>
    struct aware_return_n_target
    {
        // erased-target-aware-return-function-void
        static void e_target_a_return_fnv(const functor& fn, const RObject& p_target, traits::normal_sign_t<signature_t>&&... params) noexcept
        {
            if constexpr (std::is_void_v<return_t>)
            {
                const auto& target = p_target.view<record_t>()->get();

                auto mptr = static_cast<const method_ptr<record_t, return_t, signature_t...>&>(fn).f_ptr();

                (const_cast<record_t&>(target).*mptr)(std::forward<signature_t>(params)...);
            }
        }

        // erased-target-aware-return-function-returns(return_t)
        constexpr static auto e_target_a_return_fnr() noexcept
        {
            return [](const functor& fn, const RObject& p_target, traits::normal_sign_t<signature_t>&&... params)-> return_t
            {
                if constexpr (!std::is_void_v<return_t>)
                {
                    const auto& target = p_target.view<record_t>()->get();

                    auto mptr = static_cast<const method_ptr<record_t, return_t, signature_t...>&>(fn).f_ptr();

                    return (const_cast<record_t&>(target).*mptr)(std::forward<signature_t>(params)...);
                }
            };
        }

        // erased-return-aware-target-function
        constexpr static Return e_return_a_target_fnr(const functor& fn, const record_t& p_target, traits::normal_sign_t<signature_t>&&...params) noexcept
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

        // erased-return-erased-target-function
        constexpr static Return e_return_e_target_fnr(const functor& fn, const RObject& p_target, traits::normal_sign_t<signature_t>&&... params) noexcept
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