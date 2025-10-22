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
#include "erase_return.h"

namespace rtl::dispatch
{
    template<class return_t, class ...signature_t>
    struct aware_return : public erase_return<traits::normal_sign_t<signature_t>...>
    {
        using this_t = aware_return;
        using base_t = erase_return<traits::normal_sign_t<signature_t>...>;

        constexpr static bool is_void = (std::is_void_v<return_t>);

        aware_return()
            : base_t( is_void ? this_t::get_lambda_void() : decltype(this_t::get_lambda_void()) {},
                     !is_void ? this_t::get_lambda_any_return() : decltype(this_t::get_lambda_any_return()) {})
        {
            constexpr static bool is_const_cast_safe = (!traits::is_const_v<return_t>);
            base_t::m_return_id = detail::RObjectId::create<return_t, alloc::Stack>(is_const_cast_safe);
        }

        constexpr static auto get_lambda_void() noexcept
        {
            return [](const lambda_base& lambda, traits::normal_sign_t<signature_t>&&... params)-> auto
            {
                if constexpr (is_void)
                {
                    auto fptr = lambda.template to_function<signature_t...>()
                                      .template get_functor<void>();

                    (*fptr)(std::forward<signature_t>(params)...);
                }
            };
        }

        constexpr static auto get_lambda_any_return() noexcept
        {
            return [](const lambda_base& lambda, traits::normal_sign_t<signature_t>&&... params)-> auto
            {
                if constexpr (!is_void)
                {
                    auto fptr = lambda.template to_function<signature_t...>()
                                      .template get_functor<return_t>();

                    auto&& ret_v = (*fptr)(std::forward<signature_t>(params)...);

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
                        return std::any(raw_ct(std::forward<decltype(ret_v)>(ret_v)));
                    }
                }
                else return std::any();
            };
        }
    };
}