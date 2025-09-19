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

#include "forward_decls.h"
#include "dispatch_interface.h"
#include "hopper_nonconst.h"

namespace rtl::dispatch
{
    template<class record_t, class ...signature_ts>
    class lambda_method : public lambda_hop
    {
        using lambda_t = std::function<Return(record_t&, const lambda_hop&, const signature_ts&...)>;

        const lambda_t m_hopper;

        lambda_method(std::size_t returnId, const functor_hop* functor, lambda_t hopper) noexcept
            : m_hopper(std::move(hopper))
        {
            m_functor = functor;
            m_returnId = returnId;
            m_recordId = detail::TypeId<record_t>::get();
            m_signatureId = detail::TypeId<std::tuple<signature_ts...>>::get();
            detail::TypeId<signature_ts...>::get(m_argumentsId);
        }

    public:

        template<class return_t>
        static lambda_method create(const functor_hop* fptr_hopper)
        {
            return lambda_method(detail::TypeId<return_t>::get(), fptr_hopper, nullptr);
   			                     //&hopper_nonconst<record_t, signature_ts...>::template dispatch<std::is_same_v<return_t, void>, return_t>);
        }

        decltype(auto) operator()(record_t&, const signature_ts&...) const noexcept;

        template<class record_t, class return_t>
        decltype(auto) dispatch(record_t&, const signature_ts&...) const noexcept;

        //lambda_method() :m_hopper(nullptr) {}
    };
}