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
#include <type_traits>

#include "forward_decls.h"

#include "hopper.h"
#include "hopper_ctor.h"
#include "hopper_const.h"
#include "hopper_nonconst.h"

#include "dispatch_interface.h"

namespace rtl::dispatch
{
    template<class ...signature_ts>
    struct lambda: public lambda_hop
    {
        using lambda_t = std::function<Return(const lambda_hop&, signature_ts&&...)>;

        template<class record_t>
        static lambda create_ctor(const functor_hop* fptr_hopper) 
        {
            return lambda(detail::TypeId<record_t>::get(), fptr_hopper, 
                          &hopper_ctor<signature_ts...>::template constructor<record_t>);
        }

        template<class record_t>
        static lambda create_copy_ctor(const functor_hop* fptr_hopper)
        {
            return lambda(detail::TypeId<record_t>::get(), fptr_hopper, 
                          &hopper_ctor<signature_ts...>::template cloner<record_t>);
        }

        template<class return_t>
        static lambda create_function(const functor_hop* fptr_hopper)
        {
            return lambda(detail::TypeId<return_t>::get(), fptr_hopper,
                          &hopper<signature_ts...>::template function<Return, std::is_same_v<return_t, void>>);
        }

        template<class record_t, class return_t>
        static lambda create_method_const(const functor_hop* fptr_hopper)
        {
            return lambda(detail::TypeId<return_t>::get(), fptr_hopper, 
                          &hopper_const<signature_ts...>::template method<record_t, return_t>);
        }

        template<class record_t, class return_t>
        static lambda create_method_nonconst(const functor_hop* fptr_hopper)
        {
            return lambda(detail::TypeId<return_t>::get(), fptr_hopper,
                          &hopper_nonconst<signature_ts...>::template method<record_t, return_t>);
        }
        
        template<class ...args_t>
        Return operator()(args_t&&...params) const noexcept
        {
            return m_hopper(*this, std::forward<signature_ts>(params)...);
        }

        template<class return_t, class ...args_t>
        decltype(auto) call(args_t&&...params) const noexcept
        {
            if constexpr (std::is_same_v<return_t, void>) {
                hopper<signature_ts...>::template function<return_t>(*this, std::forward<signature_ts>(params)...);
            }
            else {
                return hopper<signature_ts...>::template function<return_t>(*this, std::forward<signature_ts>(params)...);
            }
        }

    private:

        const lambda_t m_hopper;

        lambda(std::size_t returnId, const functor_hop* functor, lambda_t hopper) noexcept
            : m_hopper(std::move(hopper))
        {
            m_functor = functor;
            m_returnId = returnId;
            m_signatureId = detail::TypeId<std::tuple<signature_ts...>>::get();
            detail::TypeId<signature_ts...>::get(m_argumentsId);
        }

        template<class record_t>
        static Return ctor(const lambda_hop&, signature_ts&&...) noexcept;

        template<class record_t>
        static Return copy_ctor(const lambda_hop&, signature_ts&&...) noexcept;

        template<class return_t>
        static return_t function(const lambda_hop&, signature_ts&&...) noexcept;

        template<class record_t, class return_t>
        static Return method_const(const lambda_hop&, signature_ts&&...) noexcept;

        template<class record_t, class return_t>
        static Return method_nonconst(const lambda_hop&, signature_ts&&...) noexcept;
    };
}