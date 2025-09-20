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

#include "lambda_hop.h"
#include "hopper_nonconst.h"

namespace rtl::dispatch
{
    template<class record_t, class ...signature_ts>
    struct lambda_hop_method : public lambda_hop
    {
        lambda_hop_method(const functor* functor) noexcept
        {
            m_functor = functor;
            m_signatureId = detail::TypeId<std::tuple<traits::raw_t<signature_ts>...>>::get();
            detail::TypeId<signature_ts...>::get(m_argumentsId);
        }

        template<class return_t>
        decltype(auto) dispatch(record_t& target, const signature_ts& ...params) const noexcept
        {
            if constexpr (std::is_same_v<return_t, void>) {
                hopper_nonconst<record_t, signature_ts...>::template dispatch<return_t>(target, *this, params...);
            }
            else {
                return hopper_nonconst<record_t, signature_ts...>::template dispatch<return_t>(target, *this, params...);
            }
        }
    };
}