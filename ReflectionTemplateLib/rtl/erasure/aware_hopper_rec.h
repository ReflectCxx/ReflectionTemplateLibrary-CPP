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
#include "erased_hopper_rec.h"

namespace rtl::dispatch::erase
{
    template<class record_t, class return_t, class ...signature_t>
    struct aware_hopper_rec : public erased_hopper_rec<record_t, traits::normal_sign_t<signature_t>...>
    {
        using base_t = erased_hopper_rec<record_t, traits::normal_sign_t<signature_t>...>;
        
        using this_t = aware_hopper_rec<record_t, return_t, signature_t...>;

        constexpr static bool isConstCastSafe = (!traits::is_const_v<return_t>);

        aware_hopper_rec(const dispatch::functor& p_functor)
            : base_t( p_functor, 
                      detail::RObjectId::create<return_t, alloc::Stack>(isConstCastSafe),
                      aware_hopper_rec::get_lambda_void(),
                      aware_hopper_rec::get_lambda_any_ret(),
                      aware_hopper_rec::get_lambda_void_robj(),
                      aware_hopper_rec::get_lambda_any_ret_robj() )
        { }

        constexpr static auto get_lambda_void() noexcept
        {
            return [](const base_t& eh, const record_t& p_target, traits::normal_sign_t<signature_t>&&... params)-> auto
            {
                //TODO: handle these kind of overloads.
                constexpr bool is_any_ptr = ((traits::is_raw_ptr_v<signature_t> || ...));
                constexpr bool is_any_rvref = ((std::is_rvalue_reference_v<signature_t> || ...));

                if constexpr (std::is_void_v<return_t> && !is_any_ptr && !is_any_rvref)
                {
                    auto mptr = eh.get_lambda()
                                  .template to_method<record_t, signature_t...>()
                                  .template get_functor<void>();

                    (const_cast<record_t&>(p_target).*mptr)(params...);
                }
            };
        }

        constexpr static auto get_lambda_void_robj() noexcept
        {
            return [](const base_t::base_t& eh, const RObject& p_target, traits::normal_sign_t<signature_t>&&... params)-> auto
            {
                //TODO: handle these kind of overloads.
                constexpr bool is_any_ptr = ((traits::is_raw_ptr_v<signature_t> || ...));
                constexpr bool is_any_rvref = ((std::is_rvalue_reference_v<signature_t> || ...));

                if constexpr (std::is_void_v<return_t> && !is_any_ptr && !is_any_rvref)
                {
                    auto mptr = eh.get_lambda()
                                  .template to_method<record_t, signature_t...>()
                                  .template get_functor<void>();

                    const auto& target = p_target.view<record_t>()->get();

                    (const_cast<record_t&>(target).*mptr)(params...);
                }
            };
        }

        constexpr static auto get_lambda_any_ret() noexcept
        {
            return [](const base_t& eh, const record_t& p_target, traits::normal_sign_t<signature_t>&&...params)-> auto
            {
                //TODO: handle these kind of overloads.
                constexpr bool is_any_ptr = ((traits::is_raw_ptr_v<signature_t> || ...));
                constexpr bool is_any_rvref = ((std::is_rvalue_reference_v<signature_t> || ...));

                if constexpr (!std::is_void_v<return_t> && !is_any_ptr && !is_any_rvref)
                {
                    auto mptr = eh.get_lambda()
                                  .template to_method<record_t, signature_t...>()
                                  .template get_functor<return_t>();

                    auto&& ret_v = (const_cast<record_t&>(p_target).*mptr)(params...);

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
                        using rconst_t = std::add_const_t<std::remove_reference_t<decltype(ret_v)>>;
                        return std::any(rconst_t(std::forward<decltype(ret_v)>(ret_v)));
                    }
                }
                else return std::any();
            };
        }

        constexpr static auto get_lambda_any_ret_robj() noexcept
        {
            return [](const base_t::base_t& eh, const RObject& p_target, traits::normal_sign_t<signature_t>&&... params)-> auto
            {
                //TODO: handle these kind of overloads.
                constexpr bool is_any_ptr = ((traits::is_raw_ptr_v<signature_t> || ...));
                constexpr bool is_any_rvref = ((std::is_rvalue_reference_v<signature_t> || ...));

                if constexpr (!std::is_void_v<return_t> && !is_any_ptr && !is_any_rvref)
                {
                    auto mptr = eh.get_lambda()
                                  .template to_method<record_t, signature_t...>()
                                  .template get_functor<return_t>();

                    const auto& target = p_target.view<record_t>()->get();

                    auto&& ret_v = (const_cast<record_t&>(target).*mptr)(params...);

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
                        using rconst_t = std::add_const_t<std::remove_reference_t<decltype(ret_v)>>;
                        return std::any(rconst_t(std::forward<decltype(ret_v)>(ret_v)));
                    }
                }
                else return std::any();
            };
        }
    };
}