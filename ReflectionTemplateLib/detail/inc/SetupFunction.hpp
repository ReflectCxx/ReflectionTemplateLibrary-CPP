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

#include "SetupFunction.h"
#include "RObjectBuilder.hpp"

namespace rtl
{
    namespace detail
    {
        template<class _derivedType>
        template<class... _signature>
        inline SetupFunction<_derivedType>::FunctionLambda<_signature...>
               SetupFunction<_derivedType>::getCaller(void(*pFunctor)(_signature...)) 
        {
            return [pFunctor](_signature&&... params) -> Return 
            {
                pFunctor(std::forward<_signature>(params)...);
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
            */  return [pFunctor](_signature&&...params)-> Return
            {
                constexpr bool isConstCastSafe = (!traits::is_const_v<_returnType>);

                if constexpr (std::is_reference_v<_returnType>) {
                /*  if the function returns reference, this block will be retained by compiler.
                        Note: reference to temporary or dangling is not checked here.
                */  using _rawRetType = traits::raw_t<_returnType>;
                    const _rawRetType& retObj = pFunctor(std::forward<_signature>(params)...);
                    return { error::None,
                             RObjectBuilder<const _rawRetType*>::template
                             build<rtl::alloc::Stack>(&retObj, rtl::index_none, isConstCastSafe)
                    };
                }
                else {
                    //if the function returns anything (not refrence), this block will be retained by compiler.
                    auto&& retObj = pFunctor(std::forward<_signature>(params)...);
                    using T = std::remove_cvref_t<decltype(retObj)>;

                    return { error::None,
                             RObjectBuilder<const T>::template
                             build<rtl::alloc::Stack>(std::forward<decltype(retObj)>(retObj), rtl::index_none, isConstCastSafe)
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
        inline const detail::FunctorId SetupFunction<_derivedType>::addFunctor(_returnType(*pFunctor)(_signature...), std::size_t pRecordId)
        {
        /*  set of already registered functors. (static life time).
            used std::vector, since std::set/map are not designed for function pointers
        */  static std::vector<std::pair<decltype(pFunctor), std::size_t>> functorSet;

        /*  adds the generated functor index to the 'functorSet'. (thread safe).
            called from '_derivedType' ('FunctorContainer')
        */  const auto& updateIndex = [&](std::size_t pIndex)->void
            {
                functorSet.emplace_back(pFunctor, pIndex);
            };

        /*  checks if the 'pFunctor' is already present in 'functorSet'. (thread safe).
            called from '_derivedType' ('FunctorContainer')
        */  const auto& getIndex = [&]()-> std::size_t 
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
            //finally add the lambda 'functor' in 'FunctorContainer' lambda vector and get the index.
            auto [index, lambdaPtr] = _derivedType::pushBack(getCaller(pFunctor), getIndex, updateIndex);

            //construct the hash-key 'FunctorId' and return.
            return detail::FunctorId {
                index, retTypeId, pRecordId, _derivedType::getContainerId(), 
                _derivedType::template getSignatureStr<_returnType>(), lambdaPtr
            };
        }
    }
}