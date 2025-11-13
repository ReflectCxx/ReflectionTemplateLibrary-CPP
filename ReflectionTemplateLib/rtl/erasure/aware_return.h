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
    template<class return_t, class ...signature_t>
    struct aware_return
    {
        constexpr static auto get_lambda_void() noexcept
        {
            return [](const lambda_base& lambda, traits::normal_sign_t<signature_t>&&... params)-> auto
            {
                if constexpr (std::is_void_v<return_t>)
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
                if constexpr (!std::is_void_v<return_t>)
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