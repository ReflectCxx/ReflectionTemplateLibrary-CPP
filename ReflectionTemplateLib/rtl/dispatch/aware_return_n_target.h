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
#include "rtl_forward_decls.h"

namespace rtl::dispatch
{
    template<class record_t, class return_t, class ...signature_t>
    struct aware_return_n_target
    {
        // erased-return-aware-target-function-void
        constexpr static auto e_return_a_target_fnv() noexcept
        {
            return [](const lambda_base& lambda, const record_t& p_target, traits::normal_sign_t<signature_t>&&... params)-> auto
            {
                if constexpr (std::is_void_v<return_t>)
                {
                    auto mptr = lambda.template to_method<record_t, signature_t...>()
                                      .template get_functor<void>();

                    (const_cast<record_t&>(p_target).*mptr)(std::forward<signature_t>(params)...);
                }
            };
        }

        // erased-target-aware-return-function-void
        constexpr static auto e_target_a_return_fnv() noexcept
        {
            return [](const lambda_base& lambda, const RObject& p_target, traits::normal_sign_t<signature_t>&&... params)-> auto
            {
                if constexpr (std::is_void_v<return_t>)
                {
                    auto mptr = lambda.template to_method<record_t, signature_t...>()
                                      .template get_functor<void>();

                    const auto& target = p_target.view<record_t>()->get();

                    (const_cast<record_t&>(target).*mptr)(std::forward<signature_t>(params)...);
                }
            };
        }

        // erased-return-erased-target-function-void
        constexpr static auto e_return_e_target_fnv() noexcept
        {
            return [](const lambda_base& lambda, const RObject& p_target, traits::normal_sign_t<signature_t>&&... params)-> auto
            {
                if constexpr (std::is_void_v<return_t>)
                {
                    auto mptr = lambda.template to_method<record_t, signature_t...>()
                                      .template get_functor<void>();

                    const auto& target = p_target.view<record_t>()->get();

                    (const_cast<record_t&>(target).*mptr)(std::forward<signature_t>(params)...);
                }
            };
        }

        // erased-target-aware-return-function-returns(return_t)
        constexpr static auto e_target_a_return_fnr() noexcept
        {
            return [](const lambda_base& lambda, const RObject& p_target, traits::normal_sign_t<signature_t>&&... params)-> return_t
            {
                if constexpr (!std::is_void_v<return_t>)
                {
                    auto mptr = lambda.template to_method<record_t, signature_t...>()
                                      .template get_functor<return_t>();

                    const auto& target = p_target.view<record_t>()->get();

                    return (const_cast<record_t&>(target).*mptr)(std::forward<signature_t>(params)...);
                }
            };
        }

        // erased-return-aware-target-function-returns(std::any)
        constexpr static auto e_return_a_target_fnr() noexcept
        {
            return [](const lambda_base& lambda, const record_t& p_target, traits::normal_sign_t<signature_t>&&...params)-> auto
            {
                if constexpr (!std::is_void_v<return_t>)
                {
                    auto mptr = lambda.template to_method<record_t, signature_t...>()
                                      .template get_functor<return_t>();

                    auto&& ret_v = (const_cast<record_t&>(p_target).*mptr)(std::forward<signature_t>(params)...);

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
            };
        }

        // erased-return-erased-target-function-returns(std::any)
        constexpr static auto e_return_e_target_fnr() noexcept
        {
            return [](const lambda_base& lambda, const RObject& p_target, traits::normal_sign_t<signature_t>&&... params)-> auto
            {
                if constexpr (!std::is_void_v<return_t>)
                {
                    auto mptr = lambda.template to_method<record_t, signature_t...>()
                                      .template get_functor<return_t>();

                    const auto& target = p_target.view<record_t>()->get();

                    auto&& ret_v = (const_cast<record_t&>(target).*mptr)(std::forward<signature_t>(params)...);

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
            };
        }
    };
}