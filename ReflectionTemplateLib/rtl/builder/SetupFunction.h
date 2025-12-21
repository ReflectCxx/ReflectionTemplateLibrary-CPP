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

#include "FunctorId.h"
#include "FunctorContainer.h"
#include "rtl_traits.h"

namespace rtl::detail 
{
    struct SetupFunction
    {
        template<class _returnType, class ..._signature>
        static std::pair<rtl::type_meta, detail::FunctorId> addFunctor(_returnType(*pFunctor)(_signature...), traits::uid_t pRecordUid,
                                                                       std::size_t pRecordId, member pMemberType)
        {
            rtl::type_meta typeMeta;
            const auto& updateIndex = [&](std::size_t pIndex)-> void {
                typeMeta = rtl::type_meta::add_function(pFunctor, pRecordUid, pMemberType);
            };

            const auto& getIndex = [&]()-> std::size_t
            {
                auto& functorCache = cache::function_ptr<_returnType, _signature...>::instance();
                auto functor = functorCache.find(pFunctor);
                if (functor != nullptr) {
                    typeMeta = rtl::type_meta(*functor);
                }
                else { 
                    return rtl::index_none; 
                }
                return 0;
            };

            using lambda_t = std::function<Return(const FunctorId&, _signature...)>;
            FunctorContainer<_signature...>::pushBack(lambda_t(), getIndex, updateIndex);
            const auto& signatureStr = (TypeId<_returnType>::toString() + " (" + TypeId<_signature...>::toString() + ")");
            const std::size_t returnId = TypeId<traits::remove_const_n_ref_n_ptr<_returnType>>::get();

            //construct the hash-key 'FunctorId' and return.
            return {
                typeMeta,
                FunctorId {
                    0,
                    returnId,
                    pRecordId,
                    FunctorContainer<_signature...>::getContainerId(),
                    signatureStr,
                    &(typeMeta.get_functor())
                }
            };
        }
    };
}