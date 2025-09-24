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

namespace rtl::dispatch
{
    struct lambda_base
    {
    protected:

        const functor& m_functor;

        lambda_base(const functor& p_functor) noexcept
            :m_functor(p_functor)
        { }

        template<class ...args_t>
        using function_t = lambda_function<args_t...>;

        template<class record_t, class ...args_t>
        using method_t = lambda_method<record_t, args_t...>;
        
        template<class ...signature_ts>
        constexpr const function_t<signature_ts...>* to_function(std::size_t p_argsId) const
        {
            if (p_argsId == m_functor.m_signatureId) [[likely]]
            {
                return static_cast<const function_t<signature_ts...>*>(this);
            }
            else return nullptr;
        }

        template<class record_t, class ...signature_ts>
        constexpr const method_t<record_t, signature_ts...>* to_method(std::size_t p_recordId, std::size_t p_argsId) const
        {
            if (p_recordId == m_functor.m_recordId && p_argsId == m_functor.m_signatureId) [[likely]]
            {
                return static_cast<const method_t<record_t, signature_ts...>*>(this);
            }
            else return nullptr;
        }

    public:

        GETTER_CREF(functor, _functor, m_functor);

        template<class return_t>
        constexpr bool is_returning() const
        {
            return (m_functor.m_returnId == detail::TypeId<return_t>::get());
        }

        template<class...args_t>
        constexpr bool is_signature() const
        {
            return (m_functor.m_signatureId == detail::TypeId<std::tuple<traits::raw_t<args_t>...>>::get());
        }

        template<class record_t>
        constexpr bool is_member() const
        {
            return (m_functor.m_recordId == detail::TypeId<record_t>::get() ||
                    m_functor.m_recordId == detail::TypeId<const record_t>::get());
        }

        friend detail::FunctorId;
    };
}