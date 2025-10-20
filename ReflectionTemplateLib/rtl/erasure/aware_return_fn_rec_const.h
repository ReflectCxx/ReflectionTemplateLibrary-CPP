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
#include "erase_return_fn_rec.h"

namespace rtl::dispatch
{
    template<class record_t, class return_t, class ...signature_t>
    struct aware_return_fn_rec<const record_t, return_t, signature_t...> : public erase_return_fn_rec<record_t, traits::normal_sign_t<signature_t>...>
    {
        using base_t = erase_return_fn_rec<record_t, traits::normal_sign_t<signature_t>...>;

        constexpr static bool isConstCastSafe = (!traits::is_const_v<return_t>);

        aware_return_fn_rec(const dispatch::functor& p_functor)
        : base_t( p_functor,
                  p_functor.is_void() ? aware_return_fn_rec::get_lambda_void() : decltype(aware_return_fn_rec::get_lambda_void()){},
                 !p_functor.is_void() ? aware_return_fn_rec::get_lambda_any_ret() : decltype(aware_return_fn_rec::get_lambda_any_ret()){},
                  p_functor.is_void() ? aware_return_fn_rec::get_lambda_void_robj() : decltype(aware_return_fn_rec::get_lambda_void_robj()){},
                 !p_functor.is_void() ? aware_return_fn_rec::get_lambda_any_ret_robj() : decltype(aware_return_fn_rec::get_lambda_any_ret_robj()){},
                  detail::RObjectId::create<return_t, alloc::Stack>(isConstCastSafe) )
        { }

        constexpr static auto get_lambda_void() noexcept
        {
            return [](const lambda_base& lambda, const record_t& p_target, traits::normal_sign_t<signature_t>&&... params)-> auto
            {
                if constexpr (std::is_void_v<return_t>)
                {
                    auto mptr = lambda.template to_method<record_t, signature_t...>()
                                      .template get_functor<void>();

                    (p_target.*mptr)(std::forward<signature_t>(params)...);
                }
            };
        }

        constexpr static auto get_lambda_void_robj() noexcept
        {
            return [](const lambda_base& lambda, const RObject& p_target, traits::normal_sign_t<signature_t>&&... params)-> auto
            {
                if constexpr (std::is_void_v<return_t>)
                {
                    auto mptr = lambda.template to_method<record_t, signature_t...>()
                                      .template get_functor<void>();

                    const auto& target = p_target.view<record_t>()->get();

                    (target.*mptr)(std::forward<signature_t>(params)...);
                }
            };
        }

        constexpr static auto get_lambda_any_ret() noexcept
        {
            return [](const lambda_base& lambda, const record_t& p_target, traits::normal_sign_t<signature_t>&&...params)-> auto
            {
                if constexpr (!std::is_void_v<return_t>)
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
                        using craw_t = std::add_const_t<std::remove_reference_t<decltype(ret_v)>>;
                        return std::any(craw_t(std::forward<decltype(ret_v)>(ret_v)));
                    }
                }
                else return std::any();
            };
        }

        constexpr static auto get_lambda_any_ret_robj() noexcept
        {
            return[](const lambda_base& lambda, const RObject& p_target, traits::normal_sign_t<signature_t>&&... params)-> auto
            {
                if constexpr (!std::is_void_v<return_t>)
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
                        using craw_t = std::add_const_t<std::remove_reference_t<decltype(ret_v)>>;
                        return std::any(craw_t(std::forward<decltype(ret_v)>(ret_v)));
                    }
                }
                else return std::any();
            };
        }
    };
}