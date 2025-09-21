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

#include "rtl_typeid.h"
#include "rtl_constants.h"
#include "forward_decls.h"

namespace rtl::dispatch
{
    struct functor
    {
        std::size_t m_recordId = detail::TypeId<>::None;
        std::size_t m_returnId = detail::TypeId<>::None;
        std::size_t m_signatureId = detail::TypeId<>::None;

        std::vector<std::size_t> m_argumentsId = {};

        detail::methodQ m_qualifier = detail::methodQ::None;        

        GETTER_CPTR(lambda, _lambda, m_lambda)

    private:

        mutable const lambda* m_lambda = nullptr;

        template<class ...signature_ts>
        friend struct cache::lambda_function;

        template<class record_t, class ...signature_ts>
        friend struct cache::lambda_method;
    };
}