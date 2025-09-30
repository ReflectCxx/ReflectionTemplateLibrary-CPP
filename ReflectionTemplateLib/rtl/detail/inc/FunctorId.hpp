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

#include "FunctorId.h"

#include "lambda_method.h"
#include "lambda_function.h"

namespace rtl::detail 
{
    template<class ...args_t>
    inline constexpr const FunctorId::lambda_ft<args_t...>* FunctorId::get_lambda_function(std::size_t p_argsId) const
    {
        return m_lambda->to_function<args_t...>(p_argsId);
    }
    
    template<class record_t, class ...args_t>
    inline constexpr const FunctorId::lambda_mt<record_t, args_t...>* FunctorId::get_lambda_method(std::size_t p_recordId, std::size_t p_argsId) const
    {
        return m_lambda->to_method<record_t, args_t...>(p_recordId, p_argsId);
    }
}