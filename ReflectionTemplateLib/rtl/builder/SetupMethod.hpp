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

#include <cassert>

#include "view.h"
#include "rtl_typeid.h"
#include "SetupMethod.h"
#include "RObjectBuilder.hpp"
#include "functor_cache_const.h"
#include "functor_cache_nonconst.h"

namespace rtl::detail
{
    template<class _derivedType>
    template<class _recordType, class ..._signature>
    inline SetupMethod<_derivedType>::MethodLambda<_signature...>
           SetupMethod<_derivedType>::getMethodCaller(void(_recordType::* pFunctor)(_signature...))
    {
    /*  a variable arguments lambda, which finally calls the 'pFunctor' with 'params...'.
        this is stored in _derivedType's (MethodContainer<detail::methodQ::NonConst, _signature...>) vector holding lambda's.
    */  return [pFunctor](const FunctorId& pFunctorId, const RObject& pTargetObj, _signature&&...params)-> Return
        {
            if (!pTargetObj.isConstCastSafe()) [[unlikely]] {
                return { error::IllegalConstCast, RObject{} };
            }

            _recordType& target = const_cast<_recordType&>(pTargetObj.view<_recordType>()->get());
            (target.*pFunctor)(std::forward<_signature>(params)...);
            return { error::None, RObject{} };
        };
    }


    template<class _derivedType>
    template<class _recordType, class _returnType, class ..._signature>
    inline SetupMethod<_derivedType>::MethodLambda<_signature...>
           SetupMethod<_derivedType>::getMethodCaller(_returnType(_recordType::* pFunctor)(_signature...))
    {
    /*  a variable arguments lambda, which finally calls the 'pFunctor' with 'params...'.
        this is stored in _derivedType's (MethodContainer<detail::methodQ::NonConst, _signature...>) vector holding lambda's.
    */  return [pFunctor](const FunctorId& pFunctorId, const RObject& pTargetObj, _signature&&...params)-> Return
        {
            if (!pTargetObj.isConstCastSafe()) [[unlikely]] {
                return { error::IllegalConstCast, RObject{} };
            }

            constexpr bool isConstCastSafe = (!traits::is_const_v<_returnType>);
            //'target' needs const_cast, since the functor is non-const-member-function.
            _recordType& target = const_cast<_recordType&>(pTargetObj.view<_recordType>()->get());
            if constexpr (std::is_reference_v<_returnType>)
            {
            /*  if the function returns reference, this block will be retained by compiler.
                Note: reference to temporary or dangling is not checked here.
            */  using _rawRetType = traits::raw_t<_returnType>;
                const _rawRetType& retObj = (target.*pFunctor)(std::forward<_signature>(params)...);
                return { error::None,
                         RObjectBuilder<const _rawRetType*>::template
                         build<rtl::alloc::Stack>(&retObj, std::nullopt, isConstCastSafe)
                };
            }
            else {

                auto&& retObj = (target.*pFunctor)(std::forward<_signature>(params)...);
                using T = std::remove_cvref_t<decltype(retObj)>;

                return { error::None,
                         RObjectBuilder<const T>::template
                         build<rtl::alloc::Stack>(std::forward<decltype(retObj)>(retObj), std::nullopt, isConstCastSafe)
                };
            }
        };
    }


    template<class _derivedType>
    template<class _recordType, class ..._signature>
    inline SetupMethod<_derivedType>::MethodLambda<_signature...>
           SetupMethod<_derivedType>::getMethodCaller(void(_recordType::* pFunctor)(_signature...) const)
    {
    /*  a variable arguments lambda, which finally calls the 'pFunctor' with 'params...'.
        this is stored in _derivedType's (MethodContainer<detail::methodQ::Const, _signature...>) vector holding lambda's.
    */  return [pFunctor](const FunctorId& pFunctorId, const RObject& pTargetObj, _signature&&...params)-> Return
        {
            const _recordType& target = pTargetObj.view<_recordType>()->get();
            (target.*pFunctor)(std::forward<_signature>(params)...);
            return { error::None, RObject{} };
        };
    }


    template<class _derivedType>
    template<class _recordType, class _returnType, class ..._signature>
    inline SetupMethod<_derivedType>::MethodLambda<_signature...>
           SetupMethod<_derivedType>::getMethodCaller(_returnType(_recordType::* pFunctor)(_signature...) const)
    {
    /*  a variable arguments lambda, which finally calls the 'pFunctor' with 'params...'.
        this is stored in _derivedType's (MethodContainer<detail::methodQ::Const, _signature...>) vector holding lambda's.
    */  return [pFunctor](const FunctorId& pFunctorId, const RObject& pTargetObj, _signature&&...params)-> Return
        {
            constexpr bool isConstCastSafe = (!traits::is_const_v<_returnType>);
            //'target' is const and 'pFunctor' is const-member-function.
            const _recordType& target = pTargetObj.view<_recordType>()->get();
            if constexpr (std::is_reference_v<_returnType>) {
            /*  if the function returns reference, this block will be retained by compiler.
                Note: reference to temporary or dangling is not checked here.
            */  using _rawRetType = traits::raw_t<_returnType>;
                const _rawRetType& retObj = (target.*pFunctor)(std::forward<_signature>(params)...);
                return { error::None,
                         RObjectBuilder<const _rawRetType*>::template
                         build<rtl::alloc::Stack>(&retObj, std::nullopt, isConstCastSafe)
                };
            }
            else {

                auto&& retObj = (target.*pFunctor)(std::forward<_signature>(params)...);
                using T = std::remove_cvref_t<decltype(retObj)>;

                return { error::None,
                         RObjectBuilder<const T>::template
                         build<rtl::alloc::Stack>(std::forward<decltype(retObj)>(retObj), std::nullopt, isConstCastSafe)
                };
            }
        };
    }


/*  @method: addFunctor().
    @param: 'pFuntor' (a non-const, non-static-member function pointer).
        '_derivedType' : class deriving this class ('MethodContainer<detail::methodQ::NonConst, _signature...>').
        '_recordType' : the owner 'class/stuct' type of the functor.
        '_returnType' : return type deduced from 'pFunctor'.
        '_signature...' : function signature deduced from 'pFunctor'.
    @return: 'FunctorId' object, a hash-key to lookup the lambda (functor-wrapped) in the _derivedType's lambda-table.
    * adds lambda (functor-wrapped) in '_derivedType' (MethodContainer<detail::methodQ::NonConst, _signature...>) and maintains functorSet.
    * thread safe, multiple functors can be registered simultaneously.
*/  template<class _derivedType>
    template<class _recordType, class _returnType, class ..._signature>
    inline const detail::FunctorId SetupMethod<_derivedType>::addFunctor(_returnType(_recordType::* pFunctor)(_signature...))
    {
        auto& functorCache = dispatch::functor_cache_nonconst<_recordType, _returnType, _signature...>::get();

        // called from '_derivedType' (MethodContainer<detail::methodQ::NonConst, _signature...>)
        const auto& updateIndex = [&](std::size_t pIndex)->void
        {
            functorCache.push(pFunctor, pIndex);
        };

        // called from '_derivedType' (MethodContainer<detail::methodQ::NonConst, _signature...>)
        const auto& getIndex = [&]()-> std::size_t
        {
            std::size_t lambdaIndex = functorCache.find(pFunctor);
            return lambdaIndex;
        };

        //generate a type-id of '_returnType'.
        const std::size_t retTypeId = TypeId<traits::remove_const_n_ref_n_ptr<_returnType>>::get();
        //finally add the lambda 'functor' in 'MethodContainer<detail::methodQ::NonConst, _signature...>' lambda vector and get the index.

        if constexpr (std::is_same_v<_returnType, void>) 
        {
            auto lambdaIndex = _derivedType::pushBack(getMethodCaller(pFunctor), getIndex, updateIndex);
            //construct the hash-key 'FunctorId' and return.
            return detail::FunctorId{

                lambdaIndex,
                retTypeId,
                TypeId<_recordType>::get(),
                _derivedType::getContainerId(),
                _derivedType::template getSignatureStr<_recordType, _returnType>(),
                nullptr
            };
        }
        else
        {
            auto lambdaIndex = _derivedType::pushBack(getMethodCaller(pFunctor), getIndex, updateIndex);
            //construct the hash-key 'FunctorId' and return.
            return detail::FunctorId {

                lambdaIndex,
                retTypeId,
                TypeId<_recordType>::get(),
                _derivedType::getContainerId(),
                _derivedType::template getSignatureStr<_recordType, _returnType>(),
                nullptr
            };
        }
    }


/*  @method: addFunctor().
    @param: 'pFuntor' (a const, non-static-member function pointer).
        '_derivedType' : class deriving this class ('MethodContainer<detail::methodQ::Const, _signature...>').
        '_recordType' : the owner 'class/stuct' type of the functor.
        '_returnType' : return type deduced from 'pFunctor'.
        '_signature...' : function signature deduced from 'pFunctor'.
    @return: 'FunctorId' object, a hash-key to lookup the lambda (containing functor) in the _derivedType's lambda table.
    * adds lambda (containing functor) in '_derivedType' (MethodContainer<detail::methodQ::Const, _signature...>) and maintains a functorSet.
    * thread safe, multiple functors can be registered simultaneously.
*/  template<class _derivedType>
    template<class _recordType, class _returnType, class ..._signature>
    inline const detail::FunctorId SetupMethod<_derivedType>::addFunctor(_returnType(_recordType::* pFunctor)(_signature...) const)
    {
        auto& functorCache = dispatch::functor_cache_const<_recordType, _returnType, _signature...>::get();

        // called from '_derivedType' (MethodContainer<detail::methodQ::Const, _signature...>)
        const auto& updateIndex = [&](std::size_t pIndex)-> void
        {
            //functorIndex = functorCache.get().size();
            functorCache.push(pFunctor, pIndex);
        };

        // called from '_derivedType' (MethodContainer<detail::methodQ::Const, _signature...>)
        const auto& getIndex = [&]()-> std::size_t
        {
            std::size_t lambdaIndex = functorCache.find(pFunctor);
            return lambdaIndex;
        };

        //generate a type-id of '_returnType'.
        const std::size_t retTypeId = TypeId<traits::remove_const_n_ref_n_ptr<_returnType>>::get();
        //finally add the lambda 'functor' in 'MethodContainer<detail::methodQ::Const, _signature...>' lambda vector and get the index.

        if constexpr (std::is_same_v<_returnType, void>)
        {
            auto lambdaIndex = _derivedType::pushBack(getMethodCaller(pFunctor), getIndex, updateIndex);

            //construct the hash-key 'FunctorId' and return.
            return detail::FunctorId {

                lambdaIndex,
                retTypeId, 
                TypeId<_recordType>::get(), 
                _derivedType::getContainerId(),
                _derivedType::template getSignatureStr<_recordType, _returnType>(), 
                nullptr//&lambdaCache
            };
        }
        else
        {
            auto lambdaIndex = _derivedType::pushBack(getMethodCaller(pFunctor), getIndex, updateIndex);
            //construct the hash-key 'FunctorId' and return.
            return detail::FunctorId{

                lambdaIndex,
                retTypeId,
                TypeId<_recordType>::get(),
                _derivedType::getContainerId(),
                _derivedType::template getSignatureStr<_recordType, _returnType>(),
                nullptr// &lambdaCache
            };
        }
    }
}