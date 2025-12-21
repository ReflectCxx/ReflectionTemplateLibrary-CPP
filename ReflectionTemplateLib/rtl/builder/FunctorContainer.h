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

#include "rtl_traits.h"
#include "CallReflector.h"
#include "SetupFunction.h"

namespace rtl {

    namespace detail
    {
        //forward decl
        class ReflectionBuilder;

    /*  @class: FunctorContainer
        @param: '_signature...' (combination of any types)
        * container class for holding std::function, wrapping functor, constructor calls of same signatures.
        * maintains a std::vector<std::function> with static lifetime.
    */  template<class ..._signature>
        class FunctorContainer : public SetupFunction<FunctorContainer<_signature...>>
        {
            using FunctionLambda = std::function < Return(const FunctorId&, _signature...) >;
        public:

            //every FunctorContainer<...> will have a unique-id.
            ForceInline static std::size_t getContainerId() {
                static const std::size_t containerId = generate_unique_id();
                return containerId;
            }

            //get the vector holding lambdas as 'const-ref'
            ForceInline const static std::vector<FunctionLambda>& getOverloads() {
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


        /*  @method: pushBack
            @params: pFunctor (lambda containing functor or constructor call)
                        pGetIndex (lambda providing index if the functor is already registered)
                        pUpdate (lambda updating the already registered functors/ctor/d'tor set)
            @return: index of newly added or already existing lambda in vector 'm_functors'.
        */  static std::size_t pushBack(const FunctionLambda& pFunctor,
                                        std::function<const std::size_t()> pGetIndex,
                                        std::function<void(const std::size_t&)> pUpdate)
            {
                //critical section, thread safe.
                static std::mutex mtx;
                std::lock_guard<std::mutex> lock(mtx);

                std::size_t index = pGetIndex();
                if (index == rtl::index_none) {
                    index = getFunctorTable().size();
                    pUpdate(index);
                    getFunctorTable().push_back(pFunctor);
                }
                return index;
            }
            
            //friends :)
            friend ReflectionBuilder;
            friend SetupFunction<FunctorContainer<_signature...>>;
            friend SetupConstructor;
        };
    }
}