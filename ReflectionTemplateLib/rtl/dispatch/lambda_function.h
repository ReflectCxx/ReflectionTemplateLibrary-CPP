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
#include "dispatch_interface.h"

namespace rtl::dispatch
{
    template<class ...signature_ts>
    class lambda: public lambda_hop
    {
        using lambda_t = std::function<Return(const lambda_hop&, const signature_ts&...)>;

        const lambda_t m_hopper;

        lambda(std::size_t returnId, const functor_hop* functor, lambda_t hopper) noexcept
            : m_hopper(std::move(hopper))
        {
            m_functor = functor;
            m_returnId = returnId;
            m_signatureId = detail::TypeId<std::tuple<signature_ts...>>::get();
            detail::TypeId<signature_ts...>::get(m_argumentsId);
        }

    public:

        template<class return_t>
        static lambda create(const functor_hop*);

        decltype(auto) operator()(const signature_ts&...) const noexcept;

        template<class return_t>
        decltype(auto) dispatch(const signature_ts&...) const noexcept;

        template<class record_t, class return_t>
        static lambda create_method_const(const functor_hop* fptr_hopper)
        {
            return lambda(detail::TypeId<return_t>::get(), fptr_hopper, nullptr);
                          //&hopper_const<signature_ts...>::template dispatch<record_t, return_t>);
        }
    };
}