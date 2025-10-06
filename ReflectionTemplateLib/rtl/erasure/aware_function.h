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
#include "erased_hopper.h"

namespace rtl::erase
{
    template<class return_t, class ...signature_t>
    struct aware_function : public erased_hopper<traits::normal_sign_t<signature_t>...>
    {
        using base_t = erased_hopper<traits::normal_sign_t<signature_t>...>;

        constexpr static bool isConstCastSafe = (!traits::is_const_v<return_t>);

        aware_function(const dispatch::functor& p_functor)
            : base_t( p_functor, 
                      detail::RObjectId::create<return_t, alloc::Stack>(isConstCastSafe),
                      aware_function::get_lambda_void(),
                      aware_function::get_lambda_any_return() )
        { }

        constexpr static auto get_lambda_void() noexcept
        {
            return [](const base_t& eh, traits::normal_sign_t<signature_t>&&... params)-> auto
            {
                constexpr bool is_any_ptr = ((traits::is_raw_ptr_v<signature_t> || ...));
                constexpr bool is_any_rvref = ((std::is_rvalue_reference_v<signature_t> || ...));

                if constexpr (std::is_void_v<return_t> && !is_any_ptr && !is_any_rvref)
                {
                    auto fptr = eh.get_lambda()
                                  .template to_function<signature_t...>()
                                  .template get_functor<void>();

                    (*fptr)(params...);
                }
            };
        }

        constexpr static auto get_lambda_any_return() noexcept
        {
            return [](const base_t& eh, traits::normal_sign_t<signature_t>&&... params)-> auto
            {
                constexpr bool is_any_ptr = ((traits::is_raw_ptr_v<signature_t> || ...));
                constexpr bool is_any_rvref = ((std::is_rvalue_reference_v<signature_t> || ...));

                if constexpr (!std::is_void_v<return_t> && !is_any_ptr && !is_any_rvref)
                {
                    auto fptr = eh.get_lambda()
                                  .template to_function<signature_t...>()
                                  .template get_functor<return_t>();

                    auto&& ret_v = (*fptr)(params...);

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