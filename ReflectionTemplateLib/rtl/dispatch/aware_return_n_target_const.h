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

#include "method_ptr_const.h"

namespace rtl::dispatch
{
    template<class record_t, class return_t, class ...signature_t>
    struct aware_return_n_target<const record_t, return_t, signature_t...>
    {
        // erased-return-aware-target-function-void
        static void e_return_a_target_fnv(const functor& fn, const record_t& p_target, traits::normal_sign_t<signature_t>&&... params) noexcept
        {
            if constexpr (std::is_void_v<return_t>)
            {
                auto mptr = static_cast<const method_ptr<const record_t, return_t, signature_t...>&>(fn).f_ptr();

                (p_target.*mptr)(std::forward<signature_t>(params)...);
            }
        }

        // erased-target-aware-return-function-void
        static void e_target_a_return_fnv(const functor& fn, const RObject& p_target, traits::normal_sign_t<signature_t>&&... params) noexcept
        {
            if constexpr (std::is_void_v<return_t>)
            {
                const auto& target = p_target.view<record_t>()->get();

                auto mptr = static_cast<const method_ptr<const record_t, return_t, signature_t...>&>(fn).f_ptr();

                (target.*mptr)(std::forward<signature_t>(params)...);
            }
        }

        // erased-return-erased-target-function-void
        static void e_return_e_target_fnv(const functor& fn, const RObject& p_target, traits::normal_sign_t<signature_t>&&... params) noexcept
        {
            if constexpr (std::is_void_v<return_t>)
            {
                auto mptr = static_cast<const method_ptr<const record_t, return_t, signature_t...>&>(fn).f_ptr();

                const auto& target = p_target.view<record_t>()->get();

                (target.*mptr)(std::forward<signature_t>(params)...);
            }
        }

        // erased-target-aware-return-function-returns(return_t)
        constexpr static auto e_target_a_return_fnr() noexcept
        {
            return [](const functor& fn, const RObject& p_target, traits::normal_sign_t<signature_t>&&... params)-> return_t
            {
                if constexpr (!std::is_void_v<return_t>)
                {
                    auto mptr = static_cast<const method_ptr<const record_t, return_t, signature_t...>&>(fn).f_ptr();

                    const auto& target = p_target.view<record_t>()->get();

                    return (target.*mptr)(std::forward<signature_t>(params)...);
                }
            };
        }

        // erased-return-aware-target-function-returns(std::any)
        constexpr static auto e_return_a_target_fnr(const functor& fn, const record_t& p_target, traits::normal_sign_t<signature_t>&&...params) noexcept
        {
            if constexpr (!std::is_void_v<return_t>)
            {
                auto mptr = static_cast<const method_ptr<const record_t, return_t, signature_t...>&>(fn).f_ptr();

                auto&& ret_v = (p_target.*mptr)(std::forward<signature_t>(params)...);

                if constexpr (std::is_pointer_v<return_t>)
                {
                    using raw_t = std::remove_pointer_t<return_t>;
                    return std::any(static_cast<const raw_t*>(ret_v));
                }
                else if constexpr (std::is_reference_v<return_t>)
                {
                    using raw_t = std::remove_cv_t<std::remove_reference_t<return_t>>;
                    return std::any(static_cast<const raw_t*>(&ret_v));
                }
                else
                {
                    using raw_ct = std::add_const_t<std::remove_reference_t<decltype(ret_v)>>;
                    // TODO: enable it for move-constructible objects.
                    static_assert(std::is_copy_constructible_v<return_t>, "return-type must be copy-constructible, required by std::any");
                    return std::any(raw_ct(std::forward<decltype(ret_v)>(ret_v)));
                }
            }
            else return std::any();
        }

        // erased-return-erased-target-function-returns(std::any)
        constexpr static auto e_return_e_target_fnr(const functor& fn, const RObject& p_target, traits::normal_sign_t<signature_t>&&... params) noexcept
        {
            if constexpr (!std::is_void_v<return_t>)
            {
                auto mptr = static_cast<const method_ptr<const record_t, return_t, signature_t...>&>(fn).f_ptr();

                const auto& target = p_target.view<record_t>()->get();

                auto&& ret_v = (target.*mptr)(std::forward<signature_t>(params)...);

                if constexpr (std::is_pointer_v<return_t>)
                {
                    using raw_t = std::remove_pointer_t<return_t>;
                    return std::any(static_cast<const raw_t*>(ret_v));
                }
                else if constexpr (std::is_reference_v<return_t>)
                {
                    using raw_t = std::remove_cv_t<std::remove_reference_t<return_t>>;
                    return std::any(static_cast<const raw_t*>(&ret_v));
                }
                else
                {
                    using raw_ct = std::add_const_t<std::remove_reference_t<decltype(ret_v)>>;
                    // TODO: enable it for move-constructible objects.
                    static_assert(std::is_copy_constructible_v<return_t>, "return-type must be copy-constructible, required by std::any");
                    return std::any(raw_ct(std::forward<decltype(ret_v)>(ret_v)));
                }
            }
            else return std::any();
        }
    };
}