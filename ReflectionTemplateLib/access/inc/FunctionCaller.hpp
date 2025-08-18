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

#include "RObject.h"
#include "Function.h"
#include "FunctionCaller.h"
#include "FunctorContainer.h"

namespace rtl
{
    namespace access
    {
        class RObject;

        template<class ..._signature>
        //FunctionCaller, holds only 'Method' associated with a static-member-function.
        inline FunctionCaller<_signature...>::FunctionCaller(const Function& pFunction)
            :m_function(pFunction) {
        }

        template<class ..._signature>
        template<class ..._args>
        inline std::pair<error, RObject> rtl::access::FunctionCaller<_signature...>::call(_args&&...params) const noexcept
        {
            using Container = std::conditional_t<sizeof...(_signature) == 0,
                                                 detail::FunctorContainer<std::remove_reference_t<_args>...>,
                                                 detail::FunctorContainer<_signature...>>;

            std::size_t index = m_function.hasSignatureId(Container::getContainerId());
            if (index != rtl::index_none) {

                error err = error::None;
                return { err, Container::template forwardCall<_args...>(err, index, std::forward<_args>(params)...) };
            }

            return { error::SignatureMismatch, RObject{} };
        }
    }
}