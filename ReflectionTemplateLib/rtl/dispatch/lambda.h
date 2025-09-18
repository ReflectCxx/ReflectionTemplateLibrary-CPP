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

#include <tuple>
#include <functional>

#include "forward_decls.h"
#include "dispatch_interface.h"

namespace rtl::dispatch
{
    template<class ...signature_ts>
    struct lambda: public lambda_hop
    {
        using lambda_t = std::function<Return(const lambda_hop&, signature_ts...)>;

        template<class record_t>
        static lambda create_ctor(const functor_hop* fptr_hopper) 
        {
            return lambda(fptr_hopper, &ctor<record_t>);
        }

        template<class record_t>
        static lambda create_copy_ctor(const functor_hop* fptr_hopper)
        {
            return lambda(fptr_hopper, &copy_ctor<record_t>);
        }

        template<class return_t>
        static lambda create_function(const functor_hop* fptr_hopper)
        {
            return lambda(fptr_hopper, &function<return_t>);
        }

        template<class record_t, class return_t>
        static lambda create_method_const(const functor_hop* fptr_hopper)
        {
            return lambda(fptr_hopper, &method_const<record_t, return_t>);
        }

        template<class record_t, class return_t>
        static lambda create_method_nonconst(const functor_hop* fptr_hopper)
        {
            return lambda(fptr_hopper, &method_nonconst<record_t, return_t>);
        }
        
        template<class ...args_t>
        decltype(auto) operator()(args_t&&...params) const noexcept
        {
            return m_hopper(*this, std::forward<args_t>(params)...);
        }

    private:

        const lambda_t m_hopper;

        lambda(const functor_hop* fptr_hopper, lambda_t hopper) noexcept
            : m_hopper(std::move(hopper))
        {
            detail::TypeId<signature_ts...>::get(m_argumentsId);
            m_signatureId = detail::TypeId<std::tuple<signature_ts...>>::get();
            m_functor = fptr_hopper;
        }

        template<class record_t>
        static Return ctor(const lambda_hop&, signature_ts&&...) noexcept;

        template<class record_t>
        static Return copy_ctor(const lambda_hop&, signature_ts&&...) noexcept;

        template<class return_t>
        static Return function(const lambda_hop&, signature_ts&&...) noexcept;

        template<class record_t, class return_t>
        static Return method_const(const lambda_hop&, signature_ts&&...) noexcept;

        template<class record_t, class return_t>
        static Return method_nonconst(const lambda_hop&, signature_ts&&...) noexcept;
    };
}