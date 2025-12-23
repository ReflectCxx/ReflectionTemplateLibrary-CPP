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

#include <map>

#include "SetupDispatch.h"

namespace rtl::detail 
{
    class RegisterCtor : public SetupDispatch
    {
        template<class record_t, class ...signature_t>
        static std::pair<type_meta, detail::FunctorId> addConstructor()
        {
            using hash_t = std::pair<traits::uid_t, traits::uid_t>;
            static std::map<hash_t, type_meta> ctorMetaSet;

            traits::uid_t recordId = traits::uid<record_t>::value;
            traits::uid_t signatureId = traits::uid<traits::strict_sign_id_t<signature_t...>>::value;
            hash_t hashKey = hash_t(recordId, signatureId);

            const auto& doRegister = [&]()->type_meta {

                if constexpr (sizeof...(signature_t) == 0) {
                    auto typeMeta = type_meta::add_constructor<member::DefaultCtor, record_t, Return, alloc>();
                    ctorMetaSet.insert(std::make_pair(hashKey, typeMeta));
                    return typeMeta;
                }
                else {
                    auto typeMeta = type_meta::add_constructor<member::UserCtor, record_t, Return, signature_t...>();
                    ctorMetaSet.insert(std::make_pair(hashKey, typeMeta));
                    return typeMeta;
                }
            };

            const auto& isRegistered = [&]()->type_meta {

                const auto& itr = ctorMetaSet.find(hashKey);
                if (itr != ctorMetaSet.end()) {
                    return itr->second;
                }
                return type_meta();
            };
            
            type_meta typeMeta;
            if constexpr (sizeof...(signature_t) == 0) {
                typeMeta = init<Return, alloc>(isRegistered, doRegister);
            }
            else {
                typeMeta = init<Return, signature_t...>(isRegistered, doRegister);
            }
            const auto& signatureStr = (TypeId<record_t>::toString() + "::(" + TypeId<signature_t...>::toString() + ")");

            return {
                typeMeta,
                FunctorId {
                    rtl::index_none,
                    typeMeta.get_return_id(),
                    typeMeta.get_record_id(),
                    typeMeta.get_strict_args_id(),
                    signatureStr,
                    &typeMeta.get_functor()
                }
            };
        }

        friend ReflectionBuilder;
    };
}