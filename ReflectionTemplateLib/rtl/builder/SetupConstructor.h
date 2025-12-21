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

#include "FunctorId.h"
#include "FunctorContainer.h"
#include "rtl_traits.h"

namespace rtl {

    namespace detail
    {
    /*  @struct: SetupConstructor
        @param: _derivedType ('FunctorContainer')
        * creates a constructor-call-wrapped-lambda to perform constructor call.
        * adds it to the functor-container, maintains the already added constructor set as well.
        * called from 'ReflectionBuilder', as _derivedType member.
    */  struct SetupConstructor
        {
            template<class _recordType, class ..._signature>
            static std::pair<type_meta, detail::FunctorId> addConstructor()
            {
                using hash_t = std::pair<traits::uid_t, traits::uid_t>;
                static std::map<hash_t, type_meta> ctorMetaSet;

                traits::uid_t recordId = traits::uid<_recordType>::value;
                traits::uid_t signatureId = traits::uid<traits::strict_sign_id_t<_signature...>>::value;
                hash_t hashKey = hash_t(recordId, signatureId);
                type_meta typeMeta;

                //will be called from '_derivedType' if the constructor not already registered.
                const auto& updateIndex = [&](std::size_t pIndex)->void
                {
                    typeMeta = type_meta::add_constructor<_recordType, _signature...>();
                    ctorMetaSet.insert(std::make_pair(hashKey, typeMeta));
                };

                //will be called from '_derivedType' to check if the constructor already registered.
                const auto& getIndex = [&]()-> std::size_t
                {
                    const auto& itr = ctorMetaSet.find(hashKey);
                    if (itr != ctorMetaSet.end())
                    {
                        typeMeta = itr->second;
                        return 0;
                    }
                    return index_none;
                };

                using ctor_t = std::function<Return(const FunctorId&, _signature...)>;
                const std::size_t fnIndex = FunctorContainer<_signature...>::pushBack(ctor_t(), getIndex, updateIndex);
                const std::size_t containerId = FunctorContainer<_signature...>::getContainerId();
                const auto& signatureStr = (TypeId<_recordType>::toString() + "::(" + TypeId<_signature...>::toString() + ")");

                return {
                    typeMeta,
                    FunctorId { 
                        fnIndex,
                        TypeId<_recordType>::get(),
                        TypeId<_recordType>::get(),
                        containerId,
                        signatureStr,
                        &typeMeta.get_functor()
                    }
                };
            }
        };
    }
}