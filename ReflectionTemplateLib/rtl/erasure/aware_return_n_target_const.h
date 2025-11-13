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

#include "RObjectId.h"
#include "erase_return_n_target.h"
#include "erase_return_aware_target.h"
#include "erase_target_aware_return.h"

namespace rtl::dispatch
{
    template<class record_t, class return_t, class ...signature_t>
    struct aware_return_n_target<const record_t, return_t, signature_t...> : public erase_return_n_target<traits::normal_sign_t<signature_t>...>
    {
        using this_t = aware_return_n_target;
        using base_t = erase_return_n_target<traits::normal_sign_t<signature_t>...>;

        using e_return_t = erase_return_aware_target<record_t, traits::normal_sign_t<signature_t>...>;
        using e_target_t = erase_target_aware_return<return_t, traits::normal_sign_t<signature_t>...>;

        constexpr static bool is_void = (std::is_void_v<return_t>);

        e_return_t e_return;
        e_target_t e_target;

        aware_return_n_target(const aware_return_n_target&) = delete;

        aware_return_n_target()
            : base_t( is_void ? this_t::e_return_e_target_fnv() : decltype(this_t::e_return_e_target_fnv()) {},
                     !is_void ? this_t::e_return_e_target_fnr() : decltype(this_t::e_return_e_target_fnr()) {})

            , e_return( is_void ? this_t::e_return_a_target_fnv() : decltype(this_t::e_return_a_target_fnv()) {},
                       !is_void ? this_t::e_return_a_target_fnr() : decltype(this_t::e_return_a_target_fnr()) {})

            , e_target( is_void ? this_t::e_target_a_return_fnv() : decltype(this_t::e_target_a_return_fnv()) {},
                       !is_void ? this_t::e_target_a_return_fnr() : decltype(this_t::e_target_a_return_fnr()) {})
        {
            constexpr static bool is_const_cast_safe = (!traits::is_const_v<return_t>);
            base_t::m_return_id = detail::RObjectId::create<return_t, alloc::Stack>(is_const_cast_safe);
        }

        void init_base()
        {
            e_return.m_return_id = base_t::m_return_id;
            e_target.m_return_id = base_t::m_return_id;

            base_t::m_erased_return = &e_return;
            base_t::m_erased_target = &e_target;
        }

        // erased-return-aware-target-function-void
        constexpr static auto e_return_a_target_fnv() noexcept
        {
            return [](const lambda_base& lambda, const record_t& p_target, traits::normal_sign_t<signature_t>&&... params)-> auto
            {
                if constexpr (is_void)
                {
                    auto mptr = lambda.template to_method<record_t, signature_t...>()
                                      .template get_functor<void>();

                    (p_target.*mptr)(std::forward<signature_t>(params)...);
                }
            };
        }

        // erased-target-aware-return-function-void
        constexpr static auto e_target_a_return_fnv() noexcept
        {
            return [](const lambda_base& lambda, const RObject& p_target, traits::normal_sign_t<signature_t>&&... params)-> void
            {
                if constexpr (is_void)
                {
                    auto mptr = lambda.template to_method<record_t, signature_t...>()
                                      .template get_functor<void>();

                    const auto& target = p_target.view<record_t>()->get();

                    (target.*mptr)(std::forward<signature_t>(params)...);
                }
            };
        }

        // erased-return-erased-target-function-void
        constexpr static auto e_return_e_target_fnv() noexcept
        {
            return [](const lambda_base& lambda, const RObject& p_target, traits::normal_sign_t<signature_t>&&... params)-> auto
            {
                if constexpr (is_void)
                {
                    auto mptr = lambda.template to_method<record_t, signature_t...>()
                                      .template get_functor<void>();

                    const auto& target = p_target.view<record_t>()->get();

                    (target.*mptr)(std::forward<signature_t>(params)...);
                }
            };
        }

        // erased-target-aware-return-function-returns(return_t)
        constexpr static auto e_target_a_return_fnr() noexcept
        {
            return [](const lambda_base& lambda, const RObject& p_target, traits::normal_sign_t<signature_t>&&... params)-> return_t
            {
                if constexpr (!is_void)
                {
                    auto mptr = lambda.template to_method<record_t, signature_t...>()
                                      .template get_functor<return_t>();

                    const auto& target = p_target.view<record_t>()->get();

                    return (target.*mptr)(std::forward<signature_t>(params)...);
                }
            };
        }

        // erased-return-aware-target-function-returns(std::any)
        constexpr static auto e_return_a_target_fnr() noexcept
        {
            return [](const lambda_base& lambda, const record_t& p_target, traits::normal_sign_t<signature_t>&&...params)-> auto
            {
                if constexpr (!is_void)
                {
                    auto mptr = lambda.template to_method<record_t, signature_t...>()
                                      .template get_functor<return_t>();

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
                        // TODO: enable it for move-constructible objects, NRVO.
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
                if constexpr (!is_void)
                {
                    auto mptr = lambda.template to_method<record_t, signature_t...>()
                                      .template get_functor<return_t>();

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
                        // TODO: enable it for move-constructible objects, NRVO.
                        static_assert(std::is_copy_constructible_v<return_t>, "return-type must be copy-constructible, required by std::any");
                        return std::any(raw_ct(std::forward<decltype(ret_v)>(ret_v)));
                    }
                }
                else return std::any();
            };
        }
    };
}