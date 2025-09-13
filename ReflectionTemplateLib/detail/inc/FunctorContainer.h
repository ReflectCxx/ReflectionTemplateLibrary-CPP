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

#include <mutex>
#include <vector>
#include <functional>

#include "LambdaTable.h"
#include "Constants.h"
#include "CallReflector.h"
#include "SetupFunction.h"
#include "SetupConstructor.h"

namespace rtl {

    namespace detail
    {
        //forward decl
        class ReflectionBuilder;

        /*  @class: FunctorContainer
            @param: '_signature...' (combination of any types)
            * container class for holding lambda's wrapping functor, constructor calls of same signatures.
            * maintains a std::vector<std::function> with static lifetime.
    */  template<class ..._signature>
        class FunctorContainer : public SetupFunction<FunctorContainer<_signature...>>,
                                 public SetupConstructor<FunctorContainer<_signature...>>,
                                 public CallReflector<FunctorContainer<_signature...>>
        {
            using FunctionLambda = std::function < Return(_signature...) >;
        public:

            using lambda_t = detail::functors<_signature...>;

            //every FunctorContainer<...> will have a unique-id.
            FORCE_INLINE static std::size_t getContainerId() {
                static const std::size_t containerId = generate_unique_id();
                return containerId;
            }

            //get the vector holding lambdas as 'const-ref'
            FORCE_INLINE const static std::vector<FunctionLambda>& getFunctors() {
                static std::vector<FunctionLambda>& functorTable = getFunctorTable();
                return functorTable;
            }

            //get functor container type(_signature...) as string with given 'returnType'.
            template<class _returnType>
            static std::string getSignatureStr(const bool pIsMember = false) 
            {
                return (TypeId<_returnType>::toString() + (pIsMember ? "::" : " ") +
                       "(" + TypeId<_signature...>::toString() + ")");
            }

        private:

            //vector holding lambdas
            static std::vector<FunctionLambda>& getFunctorTable() {
                static std::vector<FunctionLambda> functorTable;
                return  functorTable;
            }

            static lambda_t& lambdaCache()
            {
                static lambda_t functorsCache;
                return functorsCache;
            }

        /*  @method: pushBack
            @params: pFunctor (lambda containing functor or constructor call)
                        pGetIndex (lambda providing index if the functor is already registered)
                        pUpdate (lambda updating the already registered functors/ctor/d'tor set)
            @return: index of newly added or already existing lambda in vector 'm_functors'.
        */  static std::pair<std::size_t, detail::lambda_table*> pushBack(const FunctionLambda& pFunctor,
                                                                          std::function<const std::size_t()> pGetIndex,
                                                                          std::function<void(const std::size_t&)> pUpdate)
            {
                //critical section, thread safe.
                static std::mutex mtx;
                std::lock_guard<std::mutex> lock(mtx);

                std::size_t index = pGetIndex();
                if (index == rtl::index_none) 
                {
                    index = lambdaCache().get().size();

                    lambdaCache().pushBack(pFunctor);

                    getFunctorTable().push_back(pFunctor);

                    pUpdate(index);
                }
                return { index, &lambdaCache() };
            }
            
            //friends :)
            friend ReflectionBuilder;
            friend SetupFunction<FunctorContainer<_signature...>>;
            friend SetupConstructor<FunctorContainer<_signature...>>;
        };
    }
}