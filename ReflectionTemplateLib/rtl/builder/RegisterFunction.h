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

#include "type_meta.hpp"
#include "SetupDispatch.h"

namespace rtl::detail
{
    struct RegisterFunction : public SetupDispatch
    {
        template<class return_t, class ...signature_t>
        static rtl::type_meta addFunctor(return_t(*pFunctor)(signature_t...),
                                         traits::uid_t pRecordUid, member pMemberType)
        {
            const auto& doRegister = [=]()->type_meta {

                return rtl::type_meta::add_function(pFunctor, pRecordUid, pMemberType);
            };

            const auto& isRegistered = [=]()->type_meta {

                auto& fnCache = cache::function_ptr<return_t, signature_t...>::instance();
                auto functor = fnCache.find(pFunctor);
                if (functor != nullptr) {
                    return rtl::type_meta(*functor);
                }
                return type_meta();
            };

            return init<return_t, signature_t...>(isRegistered, doRegister);
        }
    };
}