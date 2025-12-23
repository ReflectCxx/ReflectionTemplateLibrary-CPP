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

#include "type_meta.hpp"

namespace rtl::detail
{
    template<class _derivedType>
    template<class _recordType, class ..._signature>
    inline SetupMethod<_derivedType>::MethodLambda<_signature...>
           SetupMethod<_derivedType>::getMethodCaller(void(_recordType::* pFunctor)(_signature...))
    {
    /*  a variable arguments lambda, which finally calls the 'pFunctor' with 'params...'.
        this is stored in _derivedType's (MethodContainer<detail::member::NonConst, _signature...>) vector holding lambda's.
    */  return [](const FunctorId& pFunctorId, const RObject& pTargetObj, _signature&&...params)-> Return
        {   
            using method_t = dispatch::method_ptr<_recordType, void, _signature...>;

            auto fptr = static_cast<const method_t&>(pFunctorId.get_functor()).f_ptr();

            if (!pTargetObj.isConstCastSafe()) [[unlikely]] {
                return { error::IllegalConstCast, RObject{} };
            }

            _recordType& target = const_cast<_recordType&>(pTargetObj.view<_recordType>()->get());
            (target.*fptr)(std::forward<_signature>(params)...);
            return { error::None, RObject{} };
        };
    }


    template<class _derivedType>
    template<class _recordType, class _returnType, class ..._signature>
    inline SetupMethod<_derivedType>::MethodLambda<_signature...>
           SetupMethod<_derivedType>::getMethodCaller(_returnType(_recordType::* pFunctor)(_signature...))
    {
    /*  a variable arguments lambda, which finally calls the 'pFunctor' with 'params...'.
        this is stored in _derivedType's (MethodContainer<detail::member::NonConst, _signature...>) vector holding lambda's.
    */  return [](const FunctorId& pFunctorId, const RObject& pTargetObj, _signature&&...params)-> Return
        {
            using method_t = dispatch::method_ptr<_recordType, _returnType, _signature...>;

            auto fptr = static_cast<const method_t&>(pFunctorId.get_functor()).f_ptr();

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
                const _rawRetType& retObj = (target.*fptr)(std::forward<_signature>(params)...);
                return { error::None,
                         RObjectBuilder<const _rawRetType*>::template
                         build<rtl::alloc::Stack>(&retObj, isConstCastSafe)
                };
            }
            else {

                auto&& retObj = (target.*fptr)(std::forward<_signature>(params)...);
                using T = std::remove_cvref_t<decltype(retObj)>;

                return { error::None,
                         RObjectBuilder<const T>::template
                         build<rtl::alloc::Stack>(std::forward<decltype(retObj)>(retObj), isConstCastSafe)
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
        this is stored in _derivedType's (MethodContainer<detail::member::Const, _signature...>) vector holding lambda's.
    */  return [](const FunctorId& pFunctorId, const RObject& pTargetObj, _signature&&...params)-> Return
        {
            using method_t = dispatch::method_ptr<const _recordType, void, _signature...>;

            auto fptr = static_cast<const method_t&>(pFunctorId.get_functor()).f_ptr();

            const _recordType& target = pTargetObj.view<_recordType>()->get();
            (target.*fptr)(std::forward<_signature>(params)...);
            return { error::None, RObject{} };
        };
    }


    template<class _derivedType>
    template<class _recordType, class _returnType, class ..._signature>
    inline SetupMethod<_derivedType>::MethodLambda<_signature...>
           SetupMethod<_derivedType>::getMethodCaller(_returnType(_recordType::* pFunctor)(_signature...) const)
    {
    /*  a variable arguments lambda, which finally calls the 'pFunctor' with 'params...'.
        this is stored in _derivedType's (MethodContainer<detail::member::Const, _signature...>) vector holding lambda's.
    */  return [](const FunctorId& pFunctorId, const RObject& pTargetObj, _signature&&...params)-> Return
        {
            using method_t = dispatch::method_ptr<const _recordType, _returnType, _signature...>;

            auto fptr = static_cast<const method_t&>(pFunctorId.get_functor()).f_ptr();

            constexpr bool isConstCastSafe = (!traits::is_const_v<_returnType>);
            //'target' is const and 'pFunctor' is const-member-function.
            const _recordType& target = pTargetObj.view<_recordType>()->get();
            if constexpr (std::is_reference_v<_returnType>) {
            /*  if the function returns reference, this block will be retained by compiler.
                Note: reference to temporary or dangling is not checked here.
            */  using _rawRetType = traits::raw_t<_returnType>;
                const _rawRetType& retObj = (target.*fptr)(std::forward<_signature>(params)...);
                return { error::None,
                         RObjectBuilder<const _rawRetType*>::template
                         build<rtl::alloc::Stack>(&retObj, isConstCastSafe)
                };
            }
            else {

                auto&& retObj = (target.*fptr)(std::forward<_signature>(params)...);
                using T = std::remove_cvref_t<decltype(retObj)>;

                return { error::None,
                         RObjectBuilder<const T>::template
                         build<rtl::alloc::Stack>(std::forward<decltype(retObj)>(retObj), isConstCastSafe)
                };
            }
        };
    }


/*  @method: addFunctor().
    @param: 'pFuntor' (a non-const, non-static-member function pointer).
        '_derivedType' : class deriving this class ('MethodContainer<detail::member::NonConst, _signature...>').
        '_recordType' : the owner 'class/stuct' type of the functor.
        '_returnType' : return type deduced from 'pFunctor'.
        '_signature...' : function signature deduced from 'pFunctor'.
    @return: 'FunctorId' object, a hash-key to lookup the lambda (functor-wrapped) in the _derivedType's lambda-table.
    * adds lambda (functor-wrapped) in '_derivedType' (MethodContainer<detail::member::NonConst, _signature...>) and maintains functorSet.
    * thread safe, multiple functors can be registered simultaneously.
*/  template<class _derivedType>
    template<class _recordType, class _returnType, class ..._signature>
    inline std::pair<type_meta, detail::FunctorId> SetupMethod<_derivedType>::addFunctor(_returnType(_recordType::* pFunctor)(_signature...))
    {
        rtl::type_meta typeMeta;
        const auto& updateIndex = [&](std::size_t pIndex)-> void
        {
            typeMeta = rtl::type_meta::add_method(pFunctor, pIndex);
        };

        const auto& getIndex = [&]()-> std::size_t
        {
            auto& functorCache = cache::method_ptr<_recordType, _returnType, _signature...>::instance();
            auto [functor, lambdaIndex] = functorCache.find(pFunctor);

            if (lambdaIndex != rtl::index_none) {
                typeMeta = rtl::type_meta(*functor);
            }
            return lambdaIndex;
        };

        auto lambdaIndex = _derivedType::pushBack(getMethodCaller(pFunctor), getIndex, updateIndex);
        //construct the hash-key 'FunctorId' and return.
        return {
            typeMeta,
            FunctorId {
                lambdaIndex,
                typeMeta.get_return_id(),
                traits::uid<_recordType>::value,
                _derivedType::getContainerId(),
                _derivedType::template getSignatureStr<_recordType, _returnType>(),
                &(typeMeta.get_functor())
            }
        };
    }


/*  @method: addFunctor().
    @param: 'pFuntor' (a const, non-static-member function pointer).
        '_derivedType' : class deriving this class ('MethodContainer<detail::member::Const, _signature...>').
        '_recordType' : the owner 'class/stuct' type of the functor.
        '_returnType' : return type deduced from 'pFunctor'.
        '_signature...' : function signature deduced from 'pFunctor'.
    @return: 'FunctorId' object, a hash-key to lookup the lambda (containing functor) in the _derivedType's lambda table.
    * adds lambda (containing functor) in '_derivedType' (MethodContainer<detail::member::Const, _signature...>) and maintains a functorSet.
    * thread safe, multiple functors can be registered simultaneously.
*/  template<class _derivedType>
    template<class _recordType, class _returnType, class ..._signature>
    inline std::pair<type_meta, detail::FunctorId> SetupMethod<_derivedType>::addFunctor(_returnType(_recordType::* pFunctor)(_signature...) const)
    {
        rtl::type_meta typeMeta;
        const auto& updateIndex = [&](std::size_t pIndex)-> void {
            typeMeta = rtl::type_meta::add_method(pFunctor, pIndex);
        };

        const auto& getIndex = [&]()-> std::size_t
        {
            auto& functorCache = cache::method_ptr<const _recordType, _returnType, _signature...>::instance();
            auto [functor, lambdaIndex] = functorCache.find(pFunctor);
            
            if (lambdaIndex != rtl::index_none) {
                typeMeta = rtl::type_meta(*functor);
            }
            return lambdaIndex;
        };

        auto lambdaIndex = _derivedType::pushBack(getMethodCaller(pFunctor), getIndex, updateIndex);

        //construct the hash-key 'FunctorId' and return.
        return {
            typeMeta,
            FunctorId {
                lambdaIndex,
                typeMeta.get_return_id(),
                traits::uid<_recordType>::value,
                _derivedType::getContainerId(),
                _derivedType::template getSignatureStr<_recordType, _returnType>(),
                &(typeMeta.get_functor())
            }
        };
    }
}