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
                return (itr != ctorSet.end() ? itr->second : rtl::index_none);
            };

            //lambda containing constructor call.
            const auto& functor = [=](error& pError, rtl::alloc pAllocType, _signature&&...params)-> access::RObject
            {
                if (pAllocType == rtl::alloc::Heap) {
                    pError = rtl::error::None;
                    return RObjectBuilder::build<const _recordType*, alloc::Heap>(new _recordType(std::forward<_signature>(params)...));
                }
                else if (pAllocType == rtl::alloc::Stack) 
                {
                    if constexpr (!std::is_copy_constructible<_recordType>::value) {
                        pError = rtl::error::CopyConstructorPrivateOrDeleted;
                        return access::RObject();
                    }
                    else {
                        pError = error::None;
                        return RObjectBuilder::build<_recordType, rtl::alloc::Stack>(_recordType(std::forward<_signature>(params)...));
                    }
                }
                //dead-code.
                return access::RObject();
            };

            //add the lambda in 'FunctorContainer'.
            std::size_t index = _derivedType::pushBack(functor, getIndex, updateIndex);
            const auto& signatureStr = _derivedType::template getSignatureStr<_recordType>(true);
            return detail::FunctorId(index, recordId, recordId, containerId, signatureStr);
        }
    }
}