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

#include "rtl_traits.h"
#include "functor.h"
#include "erasure_base.h"

namespace rtl::dispatch
{
    struct lambda_base
    {
        constexpr bool is_void() const 
        {
            return m_is_void;
        }

        template<class ...args_t>
        using function_t = lambda_function<args_t...>;
        
        template<class ...signature_t>
        constexpr const function_t<signature_t...>& to_function() const
        {
            return static_cast<const function_t<signature_t...>&>(*this);
        }

        template<class ...signature_t>
        constexpr const function_t<signature_t...>* to_function(std::size_t p_argsId) const
        {
            if (p_argsId == 0 || p_argsId == m_functor.m_strict_signId) [[likely]]
            {
                return static_cast<const function_t<signature_t...>*>(this);
            }
            else return nullptr;
        }

        template<class record_t, class ...args_t>
        using method_t = lambda_method<record_t, args_t...>;

        template<class record_t, class ...signature_t>
        constexpr const method_t<record_t, signature_t...>& to_method() const
        {
            return static_cast<const method_t<record_t, signature_t...>&>(*this);
        }

        template<class record_t, class ...signature_t>
        constexpr const method_t<record_t, signature_t...>* to_method(std::size_t p_recordId, std::size_t p_argsId) const
        {
            if (p_recordId == 0 || p_argsId ==0 ||
               (p_recordId == m_functor.m_recordId && p_argsId == m_functor.m_strict_signId)) [[likely]]
            {
                return static_cast<const method_t<record_t, signature_t...>*>(this);
            }
            else return nullptr;
        }

        GETTER_CREF(functor, _functor, m_functor)
        
        GETTER_BOOL(_any_ncref, m_functor.m_is_any_ncref)
        
        GETTER(traits::uid_t, _record_id, m_functor.m_recordId)

        GETTER(traits::uid_t, _strict_sign_id, m_functor.m_strict_signId)

        GETTER(traits::uid_t, _normal_sign_id, m_functor.m_normal_signId)

        lambda_base(const functor& p_functor, const erase::erasure_base& p_erasure) noexcept
            : m_is_void(p_functor.m_returnId == traits::uid<void>::value)
            , m_functor(p_functor)
            , m_erasure(p_erasure)
        { }

        const bool m_is_void;

        const functor& m_functor;

        const erase::erasure_base& m_erasure;
    };
}