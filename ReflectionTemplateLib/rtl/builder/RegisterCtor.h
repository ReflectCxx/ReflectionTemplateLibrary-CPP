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

#include <map>

#include <builder/SetupDispatch.h>

namespace rtl::builder
{
    class RegisterCtor : public SetupDispatch
    {
        template<class record_t, class ...signature_t>
        static type_meta addConstructor()
        {
            using hash_t = std::pair<traits::uid_t, traits::uid_t>;
            static std::map<hash_t, type_meta> ctorMetaSet;

            traits::uid_t recordId = traits::uid<record_t>::value;
            traits::uid_t signatureId = traits::uid<traits::strict_sign_id_t<signature_t...>>::value;
            hash_t hashKey = hash_t(recordId, signatureId);

            const auto& doRegister = [&]()->type_meta {

                if constexpr (sizeof...(signature_t) == 0) {
                    auto typeMeta = type_meta::add_constructor<detail::member::DefaultCtor, record_t, Return, alloc>();
                    ctorMetaSet.insert(std::make_pair(hashKey, typeMeta));
                    return typeMeta;
                }
                else {
                    auto typeMeta = type_meta::add_constructor<detail::member::UserCtor, record_t, Return, signature_t...>();
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
            
            if constexpr (sizeof...(signature_t) == 0) {
                return init<Return, alloc>(isRegistered, doRegister);
            }
            else {
                return init<Return, signature_t...>(isRegistered, doRegister);
            }
        }

        friend ReflectionBuilder;
    };
}