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

#include "RObjectBuilder.hpp"
#include "SetupConstructor.h"

namespace rtl
{
    namespace detail
    {
    /*  @method: addConstructor()
        @param: '_derivedType' (FunctorContainer), '_recordType' (class/struct), '_signature...' (ctor's args, explicitly specified)
        @return: 'FunctorId' object, a hash-key to lookup the lambda in the _derivedType's lambda-table.
        * adds lambda (wrapping constructor call) in '_derivedType' (FunctorContainer).
        * maintains a static map to check for already registered constructor for a particular class/struct type.
        * thread safe, this method is uniquely generated for each '_recordType' (class/struct type).
        * adds constructor with any combination of arguments except, copy & const-ref copy constructors.
    */  template<class _derivedType>
        template<class _recordType, class ..._signature>
        inline const detail::FunctorId SetupConstructor<_derivedType>::addConstructor()
        {
            std::size_t recordId = TypeId<_recordType>::get();
            std::size_t containerId = _derivedType::getContainerId();
            std::size_t hashKey = std::stoull(std::to_string(containerId) + std::to_string(recordId));

            //maintaining a set of already registered constructors.
            static std::map<std::size_t, std::size_t> ctorSet;

            //will be called from '_derivedType' if the constructor not already registered.
            const auto& updateIndex = [&](std::size_t pIndex)->void {
                ctorSet.insert(std::make_pair(hashKey, pIndex));
            };

            //will be called from '_derivedType' to check if the constructor already registered.
            const auto& getIndex = [&]()-> std::size_t {
                const auto& itr = ctorSet.find(hashKey);
                return (itr != ctorSet.end() ? itr->second : index_none);
            };

            //lambda containing constructor call.
            const auto& functor = [=](error& pError, alloc pAllocType, _signature&&...params)-> access::RObject
            {
                if constexpr (sizeof...(_signature) == 0 && !std::is_default_constructible_v<_recordType>) 
                {   //default constructor, private or deleted.
                    pError = error::TypeNotDefaultConstructible;
                    return access::RObject();
                }
                else 
                {
                    if (pAllocType == alloc::Stack) {

                        if constexpr (!std::is_copy_constructible_v<_recordType>) {
                            pError = error::TypeNotCopyConstructible;
                            return access::RObject();
                        }
                        else {
                            pError = error::None;
                            return RObjectBuilder::build<_recordType, alloc::Stack>(_recordType(std::forward<_signature>(params)...), true);
                        }
                    }
                    else if (pAllocType == alloc::Heap) {
                        return RObjectBuilder::build<_recordType*, alloc::Heap>(new _recordType(std::forward<_signature>(params)...), true);
                    }
                }
                return access::RObject();   //dead code. compiler warning ommited.
            };

            //add the lambda in 'FunctorContainer'.
            std::size_t index = _derivedType::pushBack(functor, getIndex, updateIndex);
            const auto& signatureStr = _derivedType::template getSignatureStr<_recordType>(true);
            return detail::FunctorId(index, recordId, recordId, containerId, signatureStr);
        }
    }
}