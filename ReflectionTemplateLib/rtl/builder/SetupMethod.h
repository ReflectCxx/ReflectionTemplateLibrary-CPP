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
    struct RegisterMethod : public SetupDispatch
    {
        template<class record_t, class return_t, class ...args_t>
        static std::pair<rtl::type_meta, detail::FunctorId> addMethodFunctor(return_t(record_t::* pMthFunctor)(args_t...))
        {
            const auto& doRegister = [=]()->type_meta {

                return rtl::type_meta::add_method(pMthFunctor);
            };

            const auto& isRegistered = [=]()->type_meta {

                auto& fnCache = cache::method_ptr<record_t, return_t, args_t...>::instance();
                auto functor = fnCache.find(pMthFunctor);
                if (functor != nullptr) {
                    return rtl::type_meta(*functor);
                }
                return type_meta();
            };

            type_meta typeMeta = init<record_t, return_t, args_t...>(isRegistered, doRegister);
            const auto& signatureStr = (TypeId<return_t>::toString() + " " + TypeId<record_t>::toString() + 
                                        "::(" + TypeId<args_t...>::toString() + ")");

            return {
                typeMeta,
                FunctorId {
                    typeMeta.get_return_id(),
                    typeMeta.get_record_id(),
                    &(typeMeta.get_functor())
                }
            };
        }

        template<class record_t, class return_t, class ...args_t>
        static std::pair<rtl::type_meta, detail::FunctorId> addMethodFunctor(return_t(record_t::* pMthFunctor)(args_t...) const)
        {
            const auto& doRegister = [=]()->type_meta {

                return rtl::type_meta::add_method(pMthFunctor);
            };

            const auto& isRegistered = [=]()->type_meta {

                auto& fnCache = cache::method_ptr<const record_t, return_t, args_t...>::instance();
                auto functor = fnCache.find(pMthFunctor);
                if (functor != nullptr) {
                    return rtl::type_meta(*functor);
                }
                return type_meta();
            };

            type_meta typeMeta = init<record_t, return_t, args_t...>(isRegistered, doRegister);

            return {
                typeMeta,
                FunctorId {
                    typeMeta.get_return_id(),
                    typeMeta.get_record_id(),
                    &(typeMeta.get_functor())
                }
            };
        }
    };
}