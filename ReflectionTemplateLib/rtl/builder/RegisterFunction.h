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

#include "SetupDispatch.h"

namespace rtl::detail
{
    struct RegisterFunction : public SetupDispatch
    {
        template<class return_t, class ...signature_t>
        static std::pair<rtl::type_meta, detail::FunctorId> addFunctor(return_t(*pFunctor)(signature_t...), traits::uid_t pRecordUid,
                                                                       std::size_t pRecordId, member pMemberType)
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

            type_meta typeMeta = init<return_t, signature_t...>(isRegistered, doRegister);
            const auto& signatureStr = (TypeId<return_t>::toString() + " (" + TypeId<signature_t...>::toString() + ")");

            return {
                typeMeta,
                FunctorId {
                    rtl::index_none,
                    TypeId<traits::remove_const_n_ref_n_ptr<return_t>>::get(),
                    pRecordId,
                    typeMeta.get_strict_args_id(),
                    signatureStr,
                    &(typeMeta.get_functor())
                }
            };
        }
    };
}