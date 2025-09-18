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

#include <cassert>

#include "lambda.h"
#include "functor.h"
#include "RObjectBuilder.hpp"

namespace rtl::dispatch
{
    template<class ...signature_ts>
    template<class return_t>
	inline Return lambda<signature_ts...>::function(const lambda_hop& hopper, signature_ts&&...params) noexcept
	{
        auto functor = hopper.functor().get<return_t, signature_ts...>().get();

        if constexpr (std::is_same_v<return_t, void>)
        {
            (*functor)(std::forward<signature_ts>(params)...);

            return { error::None, RObject{} };
        }
        else
        {
            constexpr bool isConstCastSafe = (!traits::is_const_v<return_t>);
            if constexpr (std::is_reference_v<return_t>)
            {
                using T = traits::raw_t<return_t>;
                const T& retObj = functor(std::forward<signature_ts>(params)...);

                return { error::None,
                         detail::RObjectBuilder<const T*>::template
                         build<rtl::alloc::Stack>(&retObj, std::nullopt, isConstCastSafe)
                };
            }
            else {

                auto&& retObj = functor(std::forward<signature_ts>(params)...);
                using T = std::remove_cvref_t<decltype(retObj)>;

                return { error::None,
                         detail::RObjectBuilder<const T>::template
                         build<rtl::alloc::Stack>(std::forward<decltype(retObj)>(retObj), std::nullopt, isConstCastSafe)
                };
            }
        }
	}
}