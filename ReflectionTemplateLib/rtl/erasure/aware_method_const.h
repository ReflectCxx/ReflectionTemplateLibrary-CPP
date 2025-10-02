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

#include "RObjectId.h"
#include "erased_method.h"

namespace rtl::erase
{
    template<class record_t, class return_t, class ...signature_ts>
    struct aware_method<const record_t, return_t, signature_ts...> : public erased_method<record_t, signature_ts...>
    {
        using base_t = erased_method<record_t, signature_ts...>;

        using this_t = aware_method<record_t, return_t, signature_ts...>;

        rtl::method<return_t (record_t::*)(signature_ts...) const> m_method;

        aware_method()
        {
            constexpr bool isConstCastSafe = (!traits::is_const_v<return_t>);

            base_t::hopper_v = hop_v;
            base_t::hopper_r = hop_r;
            base_t::base_t::hopper_robj_v = hop_robj_v;
            base_t::base_t::hopper_robj_r = hop_robj_r;
            base_t::base_t::return_obj_id = detail::RObjectId::create<return_t, alloc::Stack>(isConstCastSafe);
        }

        constexpr static void hop_v(const base_t* p_this, const record_t& p_target, signature_ts&&...params) noexcept
        {
            if constexpr (std::is_void_v<return_t>)
            {
                auto this_p = static_cast<const this_t*>(p_this);
                this_p->m_method(p_target, std::forward<signature_ts>(params)...);
            }
        }

        constexpr static void hop_robj_v(const base_t::base_t* p_this, const rtl::RObject& p_target, signature_ts&&...params) noexcept
        {
            if constexpr (std::is_void_v<return_t>)
            {
                const auto& target = p_target.view<record_t>()->get();
                auto this_p = static_cast<const this_t*>(p_this);
                this_p->m_method(target, std::forward<signature_ts>(params)...);
            }
        }

        ForceInline static std::any hop_r(const base_t* p_this, const record_t& p_target, signature_ts&&...params) noexcept
        {
            if constexpr (!std::is_void_v<return_t>)
            {
                auto this_p = static_cast<const this_t*>(p_this);
                auto&& ret_v = this_p->m_method(p_target, std::forward<signature_ts>(params)...);
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
        }

        ForceInline static std::any hop_robj_r(const base_t::base_t* p_this, const rtl::RObject& p_target, signature_ts&&...params) noexcept
        {
            if constexpr (!std::is_void_v<return_t>)
            {
                const auto& target = p_target.view<record_t>()->get();
                auto this_p = static_cast<const this_t*>(p_this);
                auto&& ret_v = this_p->m_method(target, std::forward<signature_ts>(params)...);
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
        }
    };
}