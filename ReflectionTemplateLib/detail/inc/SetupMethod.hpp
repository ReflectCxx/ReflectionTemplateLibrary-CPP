#pragma once

#include "RStatus.h"
#include "TypeId.hpp"
#include "SetupMethod.h"

namespace rtl
{
    namespace detail
    {
    /*  @method: addFunctor().
        @param: 'pFuntor' (a non-const, non-static-member function pointer).
            '_derivedType' : class deriving this class ('MethodContainer<TypeQ::Mute, _signature...>').
            '_recordType' : the owner 'class/stuct' type of the functor.
            '_returnType' : return type deduced from 'pFunctor'.
            '_signature...' : function signature deduced from 'pFunctor'.
        @return: 'FunctorId' object, a hash-key to lookup the lambda (functor-wrapped) in the _derivedType's lambda-table.
        * adds lambda (functor-wrapped) in '_derivedType' (MethodContainer<TypeQ::Mute, _signature...>) and maintains functorSet.
        * thread safe, multiple functors can be registered simultaneously.
    */  template<class _derivedType>
        template<class _recordType, class _retType, class ..._signature>
        inline const detail::FunctorId SetupMethod<_derivedType>::addFunctor(_retType(_recordType::* pFunctor)(_signature...))
        {
        /*  set of already registered functors. (static life time).
            used std::vector, efficient for small sets. std::set/map will be overhead.
        */  static std::vector<std::pair<decltype(pFunctor), std::size_t>> functorSet;

        /*  adds the generated functor index to the 'functorSet'. (thread safe).
            called from '_derivedType' (MethodContainer<TypeQ::Mute, _signature...>)
        */  const auto& updateIndex = [&](const std::size_t& pIndex) {
                functorSet.emplace_back(pFunctor, pIndex);
            };

        /*  checks if the 'pFunctor' is already present in 'functorSet'. (thread safe).
            called from '_derivedType' ('FunctorContainer')
        */  const auto& getIndex = [&]()->const std::size_t
            {
                //linear search, efficient for small set.
                for (const auto& fptr : functorSet) {
                    if (fptr.first == pFunctor) {
                        //functor already registered, return its 'index'.
                        return fptr.second;
                    }
                }
                //functor is not already registered, return '-1'.
                return -1;
            };

            //generate a type-id of '_returnType'.
            const std::size_t retTypeId = TypeId<_retType>::get();
            
        /*  a variable arguments lambda, which finally calls the 'pFunctor' with 'params...'.
            this is stored in _derivedType's (MethodContainer<TypeQ::Mute, _signature...>) vector holding lambda's.
        */  const auto functor = [=](const std::any& pTargetObj, _signature...params)->access::RStatus
            {
                //cast would not fail, since the type has already been validated.
                _recordType* target = std::any_cast<_recordType*>(pTargetObj);

                //if functor does not returns anything, this 'if' block is retained and else block is omitted by compiler.
                if constexpr (std::is_same_v<_retType, void>) {
                    //call will definitely be successful, since the object type, signature type has already been validated.
                    (target->*pFunctor)(params...);
                    return access::RStatus(Error::None);
                }
                //if functor returns value, this 'else' block is retained and 'if' block is omitted by compiler.
                else {
                    
                    //call will definitely be successful, since the object type, signature type has already been validated.
                    const _retType& retObj = (target->*pFunctor)(params...);
                    const TypeQ& qualifier = std::is_const<_retType>::value ? TypeQ::Const : TypeQ::Mute;

                    //return 'RStatus' with return value wrapped in it as std::any.
                    return access::RStatus(std::make_any<_retType>(retObj), retTypeId, qualifier);
                }
            };

            //finally add the lambda 'functor' in 'MethodContainer<TypeQ::Mute, _signature...>' lambda vector and get the index.
            const std::size_t& index = _derivedType::pushBack(functor, getIndex, updateIndex);

            //construct the hash-key 'FunctorId' and return.
            return detail::FunctorId(index, retTypeId, TypeId<_recordType>::get(), _derivedType::getContainerId(),
                                     _derivedType::template getSignatureStr<_recordType, _retType>());
        }


    /*  @method: addFunctor().
        @param: 'pFuntor' (a const, non-static-member function pointer).
            '_derivedType' : class deriving this class ('MethodContainer<TypeQ::Const, _signature...>').
            '_recordType' : the owner 'class/stuct' type of the functor.
            '_returnType' : return type deduced from 'pFunctor'.
            '_signature...' : function signature deduced from 'pFunctor'.
        @return: 'FunctorId' object, a hash-key to lookup the lambda (containing functor) in the _derivedType's lambda table.
        * adds lambda (containing functor) in '_derivedType' (MethodContainer<TypeQ::Const, _signature...>) and maintains a functorSet.
        * thread safe, multiple functors can be registered simultaneously.
    */  template<class _derivedType>
        template<class _recordType, class _retType, class ..._signature>
        inline const detail::FunctorId SetupMethod<_derivedType>::addFunctor(_retType(_recordType::* pFunctor)(_signature...) const)
        {
        /*  set of already registered functors. (static life time).
            used std::vector, efficient for small sets. std::set/map will be overhead.
        */  static std::vector<std::pair<decltype(pFunctor), std::size_t>> functorSet;
            const auto& updateIndex = [&](const std::size_t& pIndex) {
                functorSet.emplace_back(pFunctor, pIndex);
			};

        /*  adds the generated functor index to the 'functorSet'. (thread safe).
            called from '_derivedType' (MethodContainer<TypeQ::Const, _signature...>)
        */  const auto& getIndex = [&]()->const std::size_t
            {
                //linear search, efficient for small set.
                for (const auto& fptr : functorSet) {
                    if (fptr.first == pFunctor) {
                        //functor already registered, return its 'index'.
                        return fptr.second;
                    }
                }
                //functor is not already registered, return '-1'.
                return -1;
            };

            //generate a type-id of '_retType'.
            const std::size_t retTypeId = TypeId<_retType>::get();

        /*  a variable arguments lambda, which finally calls the 'pFunctor' with 'params...'.
            this is stored in _derivedType's (MethodContainer<TypeQ::Const, _signature...>) vector holding lambda's.
        */  const auto functor = [=](const std::any& pTargetObj, _signature...params)->access::RStatus
            {
                //cast would not fail, since the type has already been validated.
                _recordType* target = std::any_cast<_recordType*>(pTargetObj);

                //if functor does not returns anything, this 'if' block is retained and else block is omitted by compiler.
                if constexpr (std::is_same_v<_retType, void>) {

                    //call will definitely be successful, since the object type, signature type has already been validated.
                    ((static_cast<const _recordType*>(target))->*pFunctor)(params...);
                    return access::RStatus(Error::None);
                }
                else {
                    const TypeQ& qualifier = std::is_const<_retType>::value ? TypeQ::Const : TypeQ::Mute;

                    //call will definitely be successful, since the object type, signature type has already been validated.
                    const _retType& retObj = ((static_cast<const _recordType*>(target))->*pFunctor)(params...);

                    //return 'RStatus' with return value wrapped in it as std::any.
                    return access::RStatus(std::make_any<_retType>(retObj), retTypeId, qualifier);
                }
            };

            //finally add the lambda 'functor' in 'MethodContainer<TypeQ::Const, _signature...>' lambda vector and get the index.
            const std::size_t& index = _derivedType::pushBack(functor, getIndex, updateIndex);

            //construct the hash-key 'FunctorId' and return.
            return detail::FunctorId(index, retTypeId, TypeId<_recordType>::get(), _derivedType::getContainerId(),
                                     _derivedType::template getSignatureStr<_recordType, _retType>());
        }
    }
}