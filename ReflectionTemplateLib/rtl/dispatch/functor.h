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
#include "rtl_forward_decls.h"

namespace rtl::dispatch
{
    struct functor
    {
        std::size_t m_recordId = detail::TypeId<>::None;
        std::size_t m_returnId = detail::TypeId<>::None;
        std::size_t m_signatureId = detail::TypeId<>::None;

        std::string m_recordStr;
        std::string m_returnStr;
        std::string m_signatureStr;

        std::vector<std::size_t> m_argumentsId = {};

        detail::methodQ m_qualifier = detail::methodQ::None;        

        GETTER_CPTR(lambda_base, _lambda, m_lambda)

    private:

        mutable const lambda_base* m_lambda = nullptr;

        template<class ...signature_ts>
        friend struct cache::lambda_function;

        template<class record_t, class ...signature_ts>
        friend struct cache::lambda_method;
    };
}