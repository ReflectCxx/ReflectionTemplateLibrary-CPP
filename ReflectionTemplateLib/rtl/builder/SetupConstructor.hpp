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
#include <cassert>

#include "functor_cast.h"
#include "RObjectBuilder.hpp"
#include "SetupConstructor.h"

namespace rtl::detail
{
    template<class _derivedType>
    template<class _recordType, class ..._signature>
    inline SetupConstructor<_derivedType>::CtorLambda<_signature...> 
           SetupConstructor<_derivedType>::getConstructorCaller()
    {
        return [](const FunctorId& pFunctorId, alloc pAllocType, const FunctorId& pClonerId, _signature&&...params)-> Return
        {
            return {
                error::TypeNotCopyConstructible,
                RObject{}
            };
        };
    }


/*  @method: addConstructor()
    @param: '_derivedType' (FunctorContainer), '_recordType' (class/struct), '_signature...' (ctor's args, explicitly specified)
    @return: 'FunctorId' object, a hash-key to lookup the lambda in the _derivedType's lambda-table.
    * adds lambda (wrapping constructor call) in '_derivedType' (FunctorContainer).
    * maintains a static map to check for already registered constructor for a particular class/struct type.
    * thread safe, this method is uniquely generated for each '_recordType' (class/struct type).
    * adds constructor with any combination of arguments except, copy & const-ref copy constructors.
*/  template<class _derivedType>
    template<class _recordType, class ..._signature>
    inline std::pair<type_meta, detail::FunctorId> SetupConstructor<_derivedType>::addConstructor()
    {
        std::size_t recordId = TypeId<_recordType>::get();
        std::size_t returnId = recordId;
        std::size_t containerId = _derivedType::getContainerId();
        std::size_t hashKey = std::stoull(std::to_string(containerId) + std::to_string(recordId));

        //maintaining a set of already registered constructors.
        static std::map<std::size_t, std::pair<type_meta, std::size_t>> ctorSet;

        rtl::type_meta typeMeta;

        //will be called from '_derivedType' if the constructor not already registered.
        const auto& updateIndex = [&](std::size_t pIndex)->void {
            typeMeta = rtl::type_meta::add_constructor<_recordType, _signature...>(pIndex);
            ctorSet.insert(std::make_pair(hashKey, std::make_pair(typeMeta, pIndex)));
        };

        //will be called from '_derivedType' to check if the constructor already registered.
        const auto& getIndex = [&]()-> std::size_t {
            const auto& itr = ctorSet.find(hashKey);
            if (itr != ctorSet.end())
            {
                typeMeta = itr->second.first;
                return itr->second.second;
            }
            return index_none;
        };

        //add the lambda in 'FunctorContainer'.
        auto lambdaIndex = _derivedType::pushBack(getConstructorCaller<_recordType, _signature...>(), getIndex, updateIndex);

        return { 
            typeMeta,            
            detail::FunctorId {

                lambdaIndex,
                returnId,
                recordId,
                containerId,
                _derivedType::template getSignatureStr<_recordType>(true),
                &typeMeta.get_functor()
            }
        };
    }
}