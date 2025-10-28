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

#include "rtl_constants.h"

#include "CallReflector.h"
#include "SetupMethod.h"

namespace rtl {

    class RObject;

    namespace detail
    {
        //forward decl
        class ReflectionBuilder;

        template<detail::member, class ..._signature>
        class MethodContainer;

    /*  @class: MethodContainer<detail::member::NonConst, _signature...>
        @param: '_signature...' (combination of any types)
        * container class for holding lambda's wrapping non-const-member-function functor calls of same signatures.
        * maintains a std::vector<std::function> with static lifetime.
    */  template<class ..._signature>
        class MethodContainer<detail::member::NonConst, _signature...> : public SetupMethod<MethodContainer<detail::member::NonConst, _signature...>>,
                                                                          public CallReflector<MethodContainer<detail::member::NonConst, _signature...>>
        {
            using MethodLambda = std::function < Return (const FunctorId&, const rtl::RObject&, _signature...) >;

        public:

            //every MethodContainer<detail::member::NonConst,...> will have a unique-id.
            static std::size_t getContainerId() {
                //holds unique-id
                static const std::size_t containerId = generate_unique_id();
                return containerId;
            }

            //get the vector holding lambdas as 'const-ref'
            ForceInline static const std::vector<MethodLambda>& getMethodFunctors() {
                static std::vector<MethodLambda>& functorTable = getFunctorTable();
                return functorTable;
            }

            //get container type as string
            template<class _recordType, class _returnType>
            static std::string getSignatureStr() 
            {
                return (TypeId<_returnType>::toString() + " " + TypeId<_recordType>::toString() + 
                        "::(" + TypeId<_signature...>::toString() + ")");
            }

        private:

            //vector holding lambdas
            static std::vector<MethodLambda>& getFunctorTable() {
                static std::vector<MethodLambda> functorTable;
                return  functorTable;
            }


        /*  @method: pushBack
            @params: pFunctor (lambda containing non-const-member-function functor call)
                     pGetIndex (lambda providing lambdaIndex if the functor is already registered)
                     pUpdate (lambda updating the already registered functors set)
            @return: lambdaIndex of newly added or already existing lambda in vector 'm_methodPtrs'.
        */  static std::size_t pushBack(const MethodLambda& pFunctor,
                                        std::function<const std::size_t()> pGetIndex,
                                        std::function<void(const std::size_t&)> pUpdateIndex)
            {
                //critical section, thread safe.
                static std::mutex mtx;
                std::lock_guard<std::mutex> lock(mtx);

                std::size_t index = pGetIndex();
                if (index == rtl::index_none) {
                    index = getFunctorTable().size();
                    pUpdateIndex(index);
                    getFunctorTable().push_back(pFunctor);
                }
                return index;
            }

            //friends :)
            friend ReflectionBuilder;
            friend SetupMethod<MethodContainer<detail::member::NonConst, _signature...>>;
        };
    }
	

    namespace detail
    {
    /*  @class: MethodContainer<detail::member::Const, _signature...>
        @param: '_signature...' (combination of any types)
        * container class for holding lambda's wrapping const-member-function functor calls of same signatures.
        * maintains a std::vector<std::function> with static lifetime.
    */  template<class ..._signature>
        class MethodContainer<detail::member::Const, _signature...> : public SetupMethod<MethodContainer<detail::member::Const, _signature...>>,
                                                                       public CallReflector<MethodContainer<detail::member::Const, _signature...>>
        {
            using MethodLambda = std::function < Return (const FunctorId&, const rtl::RObject&, _signature...) >;

        public:

            //every MethodContainer<detail::member::Const,...> will have a unique-id.
            ForceInline static std::size_t getContainerId() {
                //holds unique-id
                static const std::size_t containerId = generate_unique_id();
                return containerId;
            }

            //get the vector holding lambdas as 'const-ref'
            ForceInline static const std::vector<MethodLambda>& getMethodFunctors() {
                static std::vector<MethodLambda>& functorTable = getFunctorTable();
                return functorTable;
            }

            //get container type as string
            template<class _recordType, class _returnType>
            static std::string getSignatureStr() 
            {
                return (TypeId<_returnType>::toString() + " " + TypeId<_recordType>::toString() + 
                       "::(" + TypeId<_signature...>::toString() + ") const");
            }

        private:

            //vector holding lambdas
            static std::vector<MethodLambda>& getFunctorTable() {
                static std::vector<MethodLambda> functorTable;
                return  functorTable;
            }


        /*  @method: pushBack
            @params: pFunctor (lambda containing const-member-function functor call)
                     pGetIndex (lambda providing lambdaIndex if the functor is already registered)
                     pUpdate (lambda updating the already registered functors set)
            @return: lambdaIndex of newly added or already existing lambda in vector 'm_methodPtrs'.
        */  static std::size_t pushBack(const MethodLambda& pFunctor,
                                        std::function<const std::size_t()> pGetIndex,
                                        std::function<void(const std::size_t&)> pUpdateIndex)
            {
                //critical section, thread safe.
                static std::mutex mtx;
                std::lock_guard<std::mutex> lock(mtx);

                std::size_t index = pGetIndex();
                if (index == rtl::index_none) {
                    index = getFunctorTable().size();
                    pUpdateIndex(index);
                    getFunctorTable().push_back(pFunctor);
                }
                return index;
            }

            //friends :)
            friend ReflectionBuilder;
            friend SetupMethod<MethodContainer<detail::member::Const, _signature...>>;
        };
    }
}