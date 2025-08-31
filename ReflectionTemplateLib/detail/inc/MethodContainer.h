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

#include <vector>
#include <functional>

#include "Constants.h"

#include "CallReflector.h"
#include "SetupMethod.h"

namespace rtl {

    class RObject;

    namespace detail
    {
        //forward decl
        class ReflectionBuilder;

        template<detail::methodQ, class ..._signature>
        class MethodContainer;

    /*  @class: MethodContainer<detail::methodQ::NonConst, _signature...>
        @param: '_signature...' (combination of any types)
        * container class for holding lambda's wrapping non-const-member-function functor calls of same signatures.
        * maintains a std::vector<std::function> with static lifetime.
    */  template<class ..._signature>
        class MethodContainer<detail::methodQ::NonConst, _signature...> : public SetupMethod<MethodContainer<detail::methodQ::NonConst, _signature...>>,
                                                                          public CallReflector<MethodContainer<detail::methodQ::NonConst, _signature...>>
        {
            using MethodLambda = std::function < RObject (error&, const rtl::RObject&, _signature...) >;

        public:

            //every MethodContainer<detail::methodQ::NonConst,...> will have a unique-id.
            static std::size_t getContainerId() {
                //holds unique-id
                static const std::size_t containerId = generate_unique_id();
                return containerId;
            }

            //get the vector holding lambdas as 'const-ref'
            static const std::vector<MethodLambda>& getMethodFunctors() {
                return getFunctorTable();
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
                     pGetIndex (lambda providing index if the functor is already registered)
                     pUpdate (lambda updating the already registered functors set)
            @return: index of newly added or already existing lambda in vector 'm_methodPtrs'.
        */  static std::size_t pushBack(const MethodLambda& pFunctor,
                                        std::function<const std::size_t()> pGetIndex,
                                        std::function<void(const std::size_t&)> pUpdateIndex)
            {
                // Old design, using locks, now thread-safety is enforced by scoped-static initialization
                // No need of locks now but keeping 'pGetIndex' & 'pUpdate' as is. could be refactored.

                //critical section, thread safe.
                //static std::mutex mtx;
                //std::lock_guard<std::mutex> lock(mtx);

                std::size_t index = pGetIndex();
                if (index == -1) {
                    index = getFunctorTable().size();
                    pUpdateIndex(index);
                    getFunctorTable().push_back(pFunctor);
                }
                return index;
            }

            //friends :)
            friend ReflectionBuilder;
            friend SetupMethod<MethodContainer<detail::methodQ::NonConst, _signature...>>;
        };
    }
	

    namespace detail
    {
    /*  @class: MethodContainer<detail::methodQ::Const, _signature...>
        @param: '_signature...' (combination of any types)
        * container class for holding lambda's wrapping const-member-function functor calls of same signatures.
        * maintains a std::vector<std::function> with static lifetime.
    */  template<class ..._signature>
        class MethodContainer<detail::methodQ::Const, _signature...> : public SetupMethod<MethodContainer<detail::methodQ::Const, _signature...>>,
                                                                       public CallReflector<MethodContainer<detail::methodQ::Const, _signature...>>
        {
            using MethodLambda = std::function < RObject (error&, const rtl::RObject&, _signature...) >;

        public:

            //every MethodContainer<detail::methodQ::Const,...> will have a unique-id.
            static std::size_t getContainerId() {
                //holds unique-id
                static const std::size_t containerId = generate_unique_id();
                return containerId;
            }

            //get the vector holding lambdas as 'const-ref'
            static const std::vector<MethodLambda>& getMethodFunctors() {
                return  getFunctorTable();
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
                     pGetIndex (lambda providing index if the functor is already registered)
                     pUpdate (lambda updating the already registered functors set)
            @return: index of newly added or already existing lambda in vector 'm_methodPtrs'.
        */  static std::size_t pushBack(const MethodLambda& pFunctor,
                                        std::function<const std::size_t()> pGetIndex,
                                        std::function<void(const std::size_t&)> pUpdateIndex)
            {
                // Old design, using locks, now thread-safety is enforced by scoped-static initialization
                // No need of locks now but keeping 'pGetIndex' & 'pUpdate' as is. could be refactored.

                //critical section, thread safe.
                //static std::mutex mtx;
                //std::lock_guard<std::mutex> lock(mtx);

                std::size_t index = pGetIndex();
                if (index == -1) {
                    index = getFunctorTable().size();
                    pUpdateIndex(index);
                    getFunctorTable().push_back(pFunctor);
                }
                return index;
            }

            //friends :)
            friend ReflectionBuilder;
            friend SetupMethod<MethodContainer<detail::methodQ::Const, _signature...>>;
        };
    }
}