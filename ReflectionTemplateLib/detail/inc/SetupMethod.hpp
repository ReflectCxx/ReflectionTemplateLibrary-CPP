#pragma once

#include "view.h"
#include "TypeId.h"
#include "RObject.h"
#include "SetupMethod.h"
#include "RObjectBuilder.h"

namespace rtl
{
    namespace detail
    {
    /*  @method: addFunctor().
        @param: 'pFuntor' (a non-const, non-static-member function pointer).
            '_derivedType' : class deriving this class ('MethodContainer<methodQ::NonConst, _signature...>').
            '_recordType' : the owner 'class/stuct' type of the functor.
            '_returnType' : return type deduced from 'pFunctor'.
            '_signature...' : function signature deduced from 'pFunctor'.
        @return: 'FunctorId' object, a hash-key to lookup the lambda (functor-wrapped) in the _derivedType's lambda-table.
        * adds lambda (functor-wrapped) in '_derivedType' (MethodContainer<methodQ::NonConst, _signature...>) and maintains functorSet.
        * thread safe, multiple functors can be registered simultaneously.
    */  template<class _derivedType>
        template<class _recordType, class _returnType, class ..._signature>
        inline const detail::FunctorId SetupMethod<_derivedType>::addFunctor(_returnType(_recordType::* pFunctor)(_signature...))
        {
        /*  set of already registered functors. (static life time).
            used std::vector, efficient for small sets. std::set/map will be overhead.
        */  static std::vector<std::pair<decltype(pFunctor), std::size_t>> functorSet;

        /*  adds the generated functor index to the 'functorSet'. (thread safe).
            called from '_derivedType' (MethodContainer<methodQ::NonConst, _signature...>)
        */  const auto& updateIndex = [&](std::size_t pIndex)->void {
                functorSet.emplace_back(pFunctor, pIndex);
            };

        /*  checks if the 'pFunctor' is already present in 'functorSet'. (thread safe).
            called from '_derivedType' ('FunctorContainer')
        */  const auto& getIndex = [&]()->std::size_t
            {
                //linear search, efficient for small set.
                for (const auto& fptr : functorSet) {
                    if (fptr.first == pFunctor) {
                        //functor already registered, return its 'index'.
                        return fptr.second;
                    }
                }
                //functor is not already registered, return '-1'.
                return rtl::index_none;
            };

            //generate a type-id of '_returnType'.
            std::size_t retTypeId = TypeId<remove_const_n_ref_n_ptr<_returnType>>::get();
            
        /*  a variable arguments lambda, which finally calls the 'pFunctor' with 'params...'.
            this is stored in _derivedType's (MethodContainer<methodQ::NonConst, _signature...>) vector holding lambda's.
        */  const auto functor = [=](error& pError, const access::RObject& pTargetObj, _signature&&...params)-> access::RObject
            {
                pError = error::None;
                const _recordType* target = pTargetObj.view<const _recordType*>()->get();

                //if functor does not returns anything, this 'if' block is retained and else block is omitted by compiler.
                if constexpr (std::is_same_v<_returnType, void>) {
                    //call will definitely be successful, since the object type, signature type has already been validated.
                    (const_cast<_recordType*>(target)->*pFunctor)(std::forward<_signature>(params)...);
                    return access::RObject();
                }
                //if functor returns value, this 'else' block is retained and 'if' block is omitted by compiler.
                else {
                    //call will definitely be successful, since the object type, signature type has already been validated.
                    return RObjectBuilder::build((const_cast<_recordType*>(target)->*pFunctor)(std::forward<_signature>(params)...), 
                                                 nullptr, alloc::None);
                }
            };

            //finally add the lambda 'functor' in 'MethodContainer<methodQ::NonConst, _signature...>' lambda vector and get the index.
            std::size_t index = _derivedType::pushBack(functor, getIndex, updateIndex);
            //construct the hash-key 'FunctorId' and return.
            return detail::FunctorId(index, retTypeId, TypeId<_recordType>::get(), _derivedType::getContainerId(),
                                     _derivedType::template getSignatureStr<_recordType, _returnType>());
        }


    /*  @method: addFunctor().
        @param: 'pFuntor' (a const, non-static-member function pointer).
            '_derivedType' : class deriving this class ('MethodContainer<methodQ::Const, _signature...>').
            '_recordType' : the owner 'class/stuct' type of the functor.
            '_returnType' : return type deduced from 'pFunctor'.
            '_signature...' : function signature deduced from 'pFunctor'.
        @return: 'FunctorId' object, a hash-key to lookup the lambda (containing functor) in the _derivedType's lambda table.
        * adds lambda (containing functor) in '_derivedType' (MethodContainer<methodQ::Const, _signature...>) and maintains a functorSet.
        * thread safe, multiple functors can be registered simultaneously.
    */  template<class _derivedType>
        template<class _recordType, class _returnType, class ..._signature>
        inline const detail::FunctorId SetupMethod<_derivedType>::addFunctor(_returnType(_recordType::* pFunctor)(_signature...) const)
        {
        /*  set of already registered functors. (static life time).
            used std::vector, efficient for small sets. std::set/map will be overhead.
        */  static std::vector<std::pair<decltype(pFunctor), std::size_t>> functorSet;
            const auto& updateIndex = [&](std::size_t pIndex)->void {
                functorSet.emplace_back(pFunctor, pIndex);
            };

        /*  adds the generated functor index to the 'functorSet'. (thread safe).
            called from '_derivedType' (MethodContainer<methodQ::Const, _signature...>)
        */  const auto& getIndex = [&]()->std::size_t
            {
                //linear search, efficient for small set.
                for (const auto& fptr : functorSet) {
                    if (fptr.first == pFunctor) {
                        //functor already registered, return its 'index'.
                        return fptr.second;
                    }
                }
                //functor is not already registered, return '-1'.
                return rtl::index_none;
            };

            //generate a type-id of '_returnType'.
            std::size_t retTypeId = TypeId<remove_const_n_ref_n_ptr<_returnType>>::get();

        /*  a variable arguments lambda, which finally calls the 'pFunctor' with 'params...'.
            this is stored in _derivedType's (MethodContainer<methodQ::Const, _signature...>) vector holding lambda's.
        */  const auto functor = [=](error& pError, const access::RObject& pTargetObj, _signature&&...params)-> access::RObject
            {
                pError = error::None;
                const _recordType* target = pTargetObj.view<const _recordType*>()->get();

                //if functor does not returns anything, this 'if' block is retained and else block is omitted by compiler.
                if constexpr (std::is_same_v<_returnType, void>) {
                    //call will definitely be successful, since the object type, signature type has already been validated.
                    (target->*pFunctor)(std::forward<_signature>(params)...);
                    return access::RObject();
                }
                else {
                    //call will definitely be successful, since the object type, signature type has already been validated.
                    return RObjectBuilder::build((target->*pFunctor)(std::forward<_signature>(params)...), nullptr, alloc::None);
                }
            };

            //finally add the lambda 'functor' in 'MethodContainer<methodQ::Const, _signature...>' lambda vector and get the index.
            std::size_t index = _derivedType::pushBack(functor, getIndex, updateIndex);
            //construct the hash-key 'FunctorId' and return.
            return detail::FunctorId(index, retTypeId, TypeId<_recordType>::get(), _derivedType::getContainerId(),
                                     _derivedType::template getSignatureStr<_recordType, _returnType>());
        }
    }
}