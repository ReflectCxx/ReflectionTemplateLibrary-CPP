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
    struct lambda
    {
    protected:

        const functor& m_functor;

        lambda(const functor& p_functor) noexcept
            :m_functor(p_functor)
        { }

        template<class ...args_t>
        using function_t = lambda_function<args_t...>;

        template<class record_t, class ...args_t>
        using method_t = lambda_method<record_t, args_t...>;

    public:

        GETTER_CREF(functor, _functor, m_functor);

        template<class ...signature_ts>
        constexpr const function_t<signature_ts...>* to_function() const
        {
            const std::size_t typeId = detail::TypeId<std::tuple<traits::raw_t<signature_ts>...>>::get();
            if (typeId == m_functor.m_signatureId)
            {
                return static_cast<const function_t<signature_ts...>*>(this);
            }
            return nullptr;
        }

        template<class record_t, class ...signature_ts>
        constexpr const method_t<record_t, signature_ts...>* to_method() const
        {
            std::size_t recordId = detail::TypeId<record_t>::get();
            std::size_t typeId = detail::TypeId<std::tuple<traits::raw_t<signature_ts>...>>::get();
            if (typeId == m_functor.m_signatureId && recordId == m_functor.m_recordId)
            {
                return static_cast<const method_t<record_t, signature_ts...>*>(this);
            }
            return nullptr;
        }


        template<class return_t>
        constexpr bool is_returning() const
        {
            return (m_functor.m_returnId == detail::TypeId<traits::raw_t<return_t>>::get());
        }

        template<class...args_t>
        constexpr bool is_signature() const
        {
            return (m_functor.m_signatureId == detail::TypeId<std::tuple<traits::raw_t<args_t>...>>::get());
        }

        template<class record_t>
        constexpr bool is_member() const
        {
            return (m_functor.m_recordId == detail::TypeId<traits::raw_t<record_t>>::get() ||
                    m_functor.m_recordId == detail::TypeId<const traits::raw_t<record_t>>::get());
        }
    };
}