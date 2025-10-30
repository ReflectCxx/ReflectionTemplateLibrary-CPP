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

#include "type_meta.hpp"

#include "SetupFunction.h"
#include "RObjectBuilder.hpp"

#include "FunctorId.hpp"

namespace rtl
{
    namespace detail
    {
        template<class _derivedType>
        template<class... _signature>
        inline SetupFunction<_derivedType>::FunctionLambda<_signature...>
               SetupFunction<_derivedType>::getCaller(void(*pFunctor)(_signature...)) 
        {
            return [](const FunctorId& pFunctorId, _signature&&... params) -> Return
            {
                auto fptr = pFunctorId.get_lambda_function<_signature...>()
                                      ->template get_hopper<void>()
                                      .f_ptr();
                
                fptr(std::forward<_signature>(params)...);
                return { error::None, RObject{} };
            };
        }


        template<class _derivedType>
        template<class _returnType, class ..._signature>
        inline SetupFunction<_derivedType>::FunctionLambda<_signature...> 
               SetupFunction<_derivedType>::getCaller(_returnType(*pFunctor)(_signature...))
        {
        /*  a variable arguments lambda, which finally calls the 'pFunctor' with 'params...'.
            this is stored in _derivedType's (FunctorContainer) vector holding lambda's.
        */  return [](const FunctorId& pFunctorId, _signature&&...params)-> Return
            {
                auto fptr = pFunctorId.get_lambda_function<_signature...>()
                                      ->template get_hopper<_returnType>()
                                      .f_ptr();

                constexpr bool isConstCastSafe = (!traits::is_const_v<_returnType>);

                if constexpr (std::is_reference_v<_returnType>) {
                /*  if the function returns reference, this block will be retained by compiler.
                    Note: reference to temporary or dangling is not checked here.
                */  using _rawRetType = traits::raw_t<_returnType>;
                    const _rawRetType& retObj = fptr(std::forward<_signature>(params)...);
                    return { error::None,
                             RObjectBuilder<const _rawRetType*>::template
                             build<rtl::alloc::Stack>(&retObj, std::nullopt, isConstCastSafe)
                    };
                }
                else {
                    //if the function returns anything (not refrence), this block will be retained by compiler.
                    auto&& retObj = fptr(std::forward<_signature>(params)...);
                    using T = std::remove_cvref_t<decltype(retObj)>;

                    return { error::None,
                             RObjectBuilder<const T>::template
                             build<rtl::alloc::Stack>(std::forward<decltype(retObj)>(retObj), std::nullopt, isConstCastSafe)
                    };
                }
            };
        }


    /*  @method: addFunctor().
        @param: 'pFuntor' (a non-member or static-member function pointer).
            '_derivedType' : class deriving this class ('FunctionContainer<...>').
            '_returnType' : return type deduced from 'pFunctor'.
            '_signature...' : function signature deduced from 'pFunctor'.
        @return: 'FunctorId' object, a hash-key to lookup the functor in the _derivedType's lambda-table.
        * adds functor in _derivedType ('FunctionContainer<...>') and maintains functorSet of already registered functors.
        * thread safe, multiple functors can be registered simultaneously.
    */  template<class _derivedType>
        template<class _returnType, class ..._signature>
        inline std::pair<type_meta, detail::FunctorId> 
        SetupFunction<_derivedType>::addFunctor(_returnType(*pFunctor)(_signature...), traits::uid_t pRecordUid, std::size_t pRecordId, member pMemberType)
        {
            rtl::type_meta typeMeta;
            const auto& updateIndex = [&](std::size_t pIndex)-> void {
                typeMeta = rtl::type_meta::add_function(pFunctor, pRecordUid, pMemberType, pIndex);
            };

            const auto& getIndex = [&]()-> std::size_t
            {
                auto& functorCache = cache::function_ptr<_returnType, _signature...>::instance();
                auto [functor, lambdaIndex] = functorCache.find(pFunctor);
                if (lambdaIndex != rtl::index_none) {
                    typeMeta = rtl::type_meta(*functor);
                }
                return lambdaIndex;
            };

            //generate a type-id of '_returnType'.
            const std::size_t returnId = TypeId<traits::remove_const_n_ref_n_ptr<_returnType>>::get();
            //finally add the lambda 'functor' in 'FunctorContainer' lambda vector and get the index.
            auto lambdaIndex = _derivedType::pushBack(getCaller(pFunctor), getIndex, updateIndex);

            //construct the hash-key 'FunctorId' and return.
            return { 
                typeMeta,
                FunctorId {
                    lambdaIndex,
                    returnId,
                    pRecordId,
                    _derivedType::getContainerId(),
                    _derivedType::template getSignatureStr<_returnType>(),
                    &(typeMeta.get_lambda())
                }
            };
        }
    }
}