#pragma once
#include <map>

#include "RStatus.h"
#include "SetupConstructor.h"

namespace rtl
{
    namespace detail
    {
    /*  @method: addDestructor()
        @param: '_derivedType' (FunctorContainer), '_recordType' (class/struct type)
        @return: 'FunctorId' object, a hash-key to lookup the destructor (wrapped in lambda) in the _derivedType's lambda-table.
        * adds lambda (destructor-call-wrapped) in '_derivedType' (FunctorContainer).
        * maintains a static var for already registered destructor for a particular class/struct type.
        * thread safe, this method is uniquely generated for each '_recordType' (class/struct type).
	*/  template<class _derivedType>
        template<class _recordType>
        inline const detail::FunctorId SetupConstructor<_derivedType>::addDestructor()
        {
            //no destructor is registered yet for type '_recordType' if 'dctorIndex' is -1.
            static std::size_t dctorIndex = -1;

            //will be called from '_derivedType' if the destructor not already registered.
            const auto& updateIndex = [&](const std::size_t& pIndex) {
                dctorIndex = pIndex;
            };

            //will be called from '_derivedType' to check if the destructor already registered.
            const auto& getIndex = [&]()->const std::size_t {
                return dctorIndex;
            };

            //destructor lambda.
            const auto& functor = [](const std::any& pTarget)->access::RStatus
            {
                //cast will definitely succeed, will not throw since the object type is already validated.
                _recordType* object = std::any_cast<_recordType*>(pTarget);
                delete object;
                return access::RStatus(Error::None);
            };

            //add the lambda in 'FunctorContainer'.
            const std::size_t& index = _derivedType::pushBack(functor, getIndex, updateIndex);
            return detail::FunctorId(index, TypeId<>::None, TypeId<_recordType>::get(), _derivedType::getContainerId(), 
                                    (std::string("~") + _derivedType::template getSignatureStr<_recordType>(true)));
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
        inline const detail::FunctorId SetupConstructor<_derivedType>::addConstructor()
        {
            const auto& recordId = TypeId<_recordType>::get();
            const auto& containerId = _derivedType::getContainerId();
            const auto& hashKey = std::stoull(std::to_string(containerId) + std::to_string(recordId));

            //maintaining a set of already registered constructors.
            static std::map<std::size_t, std::size_t> ctorSet;

            //will be called from '_derivedType' if the constructor not already registered.
            const auto& updateIndex = [&](const std::size_t& pIndex) {
                ctorSet.insert(std::make_pair(hashKey, pIndex));
            };

            //will be called from '_derivedType' to check if the constructor already registered.
            const auto& getIndex = [&]()->const std::size_t {
                const auto& itr = ctorSet.find(hashKey);
                return (itr != ctorSet.end() ? itr->second : -1);
            };

            //lambda containing constructor call.
            const auto& functor = [=](_signature...params)->access::RStatus
            {
                _recordType* retObj = new _recordType(params...);
                return access::RStatus(std::make_any<_recordType*>(retObj), recordId, TypeQ::Mute);
            };

            //add the lambda in 'FunctorContainer'.
            const std::size_t& index = _derivedType::pushBack(functor, getIndex, updateIndex);
            return detail::FunctorId(index, TypeId<_recordType>::get(), recordId, containerId,
                                     _derivedType::template getSignatureStr<_recordType>(true));
        }


    /*  @method: addCopyConstructor()
        @param: '_derivedType' (FunctorContainer), '_recordType' (class/struct).
        @return: 'FunctorId' object, a hash-key to lookup the lambda in the _derivedType's lambda-table.
        * adds lambda (wrapping copy-constructor call) in '_derivedType' (FunctorContainer).
        * maintains a static map to check for already registered constructor for a particular class/struct type.
        * thread safe, this method is uniquely generated for each '_recordType' (class/struct type).
        * adds copy constructor with argument '_recordType&'.
    */  template<class _derivedType>
        template<class _recordType>
        inline const detail::FunctorId SetupConstructor<_derivedType>::addCopyConstructor()
        {
            //no copy-constructor is registered yet for type '_recordType' if 'copyCtorIndex' is -1.
            static std::size_t copyCtorIndex = -1;
            
            //will be called from '_derivedType' if the copy-constructor not already registered.
            const auto& updateIndex = [&](const std::size_t& pIndex) {
                copyCtorIndex = pIndex;
            };

            //will be called from '_derivedType' to check if the constructor already registered.
            const auto& getIndex = [&]()->const std::size_t {
                return copyCtorIndex;
            };

            const auto& recordId = TypeId<_recordType>::get();
            //lambda containing constructor call.
            const auto& functor = [=](const std::any& pOther)->access::RStatus
            {
                //cast will definitely succeed, will not throw since the object type is already validated.
                _recordType* srcObj = std::any_cast<_recordType*>(pOther);
                _recordType* retObj = new _recordType(*srcObj);
                return access::RStatus(std::make_any<_recordType*>(retObj), recordId, TypeQ::Mute);
            };

            //add the lambda in 'FunctorContainer'.
            const std::size_t& index = _derivedType::pushBack(functor, getIndex, updateIndex);
            return detail::FunctorId(index, TypeId<_recordType>::get(), recordId, _derivedType::getContainerId(),
                                     _derivedType::template getSignatureStr<_recordType>(true));
        }


    /*  @method: addConstCopyConstructor()
        @param: '_derivedType' (FunctorContainer), '_recordType' (class/struct).
        @return: 'FunctorId' object, a hash-key to lookup the lambda in the _derivedType's lambda-table.
        * adds lambda (wrapping copy-constructor with const-ref call) in '_derivedType' (FunctorContainer).
        * maintains a static map to check for already registered constructor for a particular class/struct type.
        * thread safe, this method is uniquely generated for each '_recordType' (class/struct type).
        * adds copy constructor with argument 'const _recordType&'.
    */  template<class _derivedType>
        template<class _recordType>
        inline const detail::FunctorId SetupConstructor<_derivedType>::addConstCopyConstructor()
        {
            //no copy constructor with const-ref is registered yet for type '_recordType' if 'constCopyCtorIndex' is -1.
            static std::size_t constCopyCtorIndex = -1;

            //will be called from '_derivedType' if the const-ref-copy-constructor not already registered.
            const auto& updateIndex = [&](const std::size_t& pIndex) {
                constCopyCtorIndex = pIndex;
            };

            //will be called from '_derivedType' to check if the const-ref-copy-constructor already registered.
            const auto& getIndex = [&]()->const std::size_t {
                return constCopyCtorIndex;
            };

            const auto& recordId = TypeId<_recordType>::get();
            //lambda containing constructor call.
            const auto& functor = [=](const std::any& pOther)->access::RStatus
            {
                //cast will definitely succeed, will not throw since the object type is already validated.
                const _recordType* srcObj = std::any_cast<_recordType*>(pOther);
                _recordType* retObj = new _recordType(*srcObj);
                return access::RStatus(std::make_any<_recordType*>(retObj), recordId, TypeQ::Mute);
            };

            //add the lambda in 'FunctorContainer'.
            const std::size_t& index = _derivedType::pushBack(functor, getIndex, updateIndex);
            return detail::FunctorId(index, TypeId<_recordType>::get(), recordId, _derivedType::getContainerId(),
                                     _derivedType::template getSignatureStr<_recordType>(true));
        }
    }
}