#pragma once

#include "view.h"
#include "TypeId.h"
#include "SetupMethod.h"
#include "RObjectBuilder.hpp"

namespace rtl
{
    namespace detail
    {
        template<class _derivedType>
        template<class _recordType, class _returnType, class ..._signature>
        inline SetupMethod<_derivedType>::MethodLambda<_signature...>
               SetupMethod<_derivedType>::getMethodCaller(_returnType(_recordType::* pFunctor)(_signature...))
        {
        /*  a variable arguments lambda, which finally calls the 'pFunctor' with 'params...'.
            this is stored in _derivedType's (MethodContainer<methodQ::NonConst, _signature...>) vector holding lambda's.
        */  return [=](error& pError, const access::RObject& pTargetObj, _signature&&...params)-> access::RObject
            {
                //call on 'pFunctor' will definitely be successful, since the object type, signature type has already been validated.
                pError = error::None;
                //'target' needs const_cast, since the functor is non-const-member-function.
                _recordType* target = const_cast<_recordType*>(pTargetObj.view<const _recordType*>()->get());
                
                if constexpr (std::is_same_v<_returnType, void>) {
                    //if the function do not returns anything, this block will be retained by compiler.
                    (target->*pFunctor)(std::forward<_signature>(params)...);
                    return access::RObject();
                }
                else if constexpr (std::is_reference_v<_returnType>) {
                /*  if the function returns reference, this block will be retained by compiler.
                    Note: reference to temporary or dangling is not checked here.
                */  const _returnType& retObj = (target->*pFunctor)(std::forward<_signature>(params)...);
                    return RObjectBuilder::build(&retObj);
                }
                else {
                    //if the function returns anything (not refrence), this block will be retained by compiler.
                    return RObjectBuilder::build<_returnType, rtl::alloc::None>((target->*pFunctor)(std::forward<_signature>(params)...));
                }
            };
        }


        template<class _derivedType>
        template<class _recordType, class _returnType, class ..._signature>
        inline SetupMethod<_derivedType>::MethodLambda<_signature...>
               SetupMethod<_derivedType>::getMethodCaller(_returnType(_recordType::* pFunctor)(_signature...) const)
        {
        /*  a variable arguments lambda, which finally calls the 'pFunctor' with 'params...'.
            this is stored in _derivedType's (MethodContainer<methodQ::Const, _signature...>) vector holding lambda's.
        */  return [=](error& pError, const access::RObject& pTargetObj, _signature&&...params)-> access::RObject
            {
                //call will definitely be successful, since the object type, signature type has already been validated.
                pError = error::None;
                //'target' is const and 'pFunctor' is const-member-function.
                const _recordType* target = pTargetObj.view<const _recordType*>()->get();

                if constexpr (std::is_same_v<_returnType, void>) {
                    //if the function do not returns anything, this block will be retained by compiler.
                    (target->*pFunctor)(std::forward<_signature>(params)...);
                    return access::RObject();
                }
                else if constexpr (std::is_reference_v<_returnType>) {
                /*  if the function returns reference, this block will be retained by compiler.
                    Note: reference to temporary or dangling is not checked here.
                */  const _returnType& retObj = (target->*pFunctor)(std::forward<_signature>(params)...);
                    return RObjectBuilder::build(&retObj);
                }
                else {
                    //if the function returns anything (not refreence), this block will be retained by compiler.
                    return RObjectBuilder::build<_returnType, rtl::alloc::None>((target->*pFunctor)(std::forward<_signature>(params)...));
                }
            };
        }


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
            const std::size_t retTypeId = TypeId<traits::remove_const_n_ref_n_ptr<_returnType>>::get();
            //finally add the lambda 'functor' in 'MethodContainer<methodQ::NonConst, _signature...>' lambda vector and get the index.
            const std::size_t index = _derivedType::pushBack(getMethodCaller(pFunctor), getIndex, updateIndex);
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
            const std::size_t retTypeId = TypeId<traits::remove_const_n_ref_n_ptr<_returnType>>::get();
            //finally add the lambda 'functor' in 'MethodContainer<methodQ::Const, _signature...>' lambda vector and get the index.
            const std::size_t index = _derivedType::pushBack(getMethodCaller(pFunctor), getIndex, updateIndex);
            //construct the hash-key 'FunctorId' and return.
            return detail::FunctorId(index, retTypeId, TypeId<_recordType>::get(), _derivedType::getContainerId(),
                                     _derivedType::template getSignatureStr<_recordType, _returnType>());
        }
    }
}