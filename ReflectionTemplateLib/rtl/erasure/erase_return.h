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

#include "erasure.h"
#include "rtl_traits.h"
#include "rtl_function.h"
#include "rtl_errors.h"
#include <type_traits>

namespace rtl::erase
{
    template<class return_t, class ...signature_ts>
    struct function_return : public erasure_base<signature_ts...>
    {
        rtl::function<return_t(signature_ts...)> m_function;

        void hop_v(signature_ts&&...params) const noexcept override
        {
            if constexpr (std::is_void_v<return_t>)
            {
                m_function(std::forward<signature_ts>(params)...);
            }
        }

        std::any hop_r(signature_ts&&...params) const noexcept override
        {
            if constexpr (!std::is_void_v<return_t>)
            {
                return std::any(m_function(std::forward<signature_ts>(params)...));
            }
            else return std::any();
        }
    };
 }