/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#pragma once

#include <builder/SetupDispatch.h>

namespace rtl::builder
{
    struct RegisterMethod : public SetupDispatch
    {
        template<class record_t, class return_t, class ...args_t>
        static type_meta addMethodFunctor(return_t(record_t::* pMthFunctor)(args_t...))
        {
            const auto& doRegister = [=]()->type_meta {

                return type_meta::add_method(pMthFunctor);
            };

            const auto& isRegistered = [=]()->type_meta {

                auto& fnCache = cache::method_ptr<record_t, return_t, args_t...>::instance();
                auto functor = fnCache.find(pMthFunctor);
                if (functor != nullptr) {
                    return rtl::type_meta(*functor);
                }
                return type_meta();
            };

            return init<record_t, return_t, args_t...>(isRegistered, doRegister);
        }


        template<class record_t, class return_t, class ...args_t>
        static type_meta addMethodFunctor(return_t(record_t::* pMthFunctor)(args_t...) const)
        {
            const auto& doRegister = [=]()->type_meta {

                return type_meta::add_method(pMthFunctor);
            };

            const auto& isRegistered = [=]()->type_meta {

                auto& fnCache = cache::method_ptr<const record_t, return_t, args_t...>::instance();
                auto functor = fnCache.find(pMthFunctor);
                if (functor != nullptr) {
                    return rtl::type_meta(*functor);
                }
                return type_meta();
            };

            return init<record_t, return_t, args_t...>(isRegistered, doRegister);
        }
    };
}