/*****************************************************************
 *                                                               *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP  *
 *                                                               *
 *  Copyright (c) 2025 Neeraj Singh (reflectcxx@outlook.com)     *
 *  SPDX-License-Identifier: MIT                                 *
 *                                                               *
 *****************************************************************/


#pragma once

#include <mutex>
#include <atomic>
#include <vector>
#include <functional>

#include "Constants.h"

#include "CallReflector.h"
#include "SetupMethod.h"

namespace rtl {

	namespace access {
        class RObject;
	}

    namespace detail
    {
        //forward decl
        class ReflectionBuilder;
        //unique id generator.
        extern std::atomic<std::size_t> g_containerIdCounter;

        template<methodQ, class ..._signature>
        class MethodContainer;

    /*  @class: MethodContainer<methodQ::NonConst, _signature...>
        @param: '_signature...' (combination of any types)
        * container class for holding lambda's wrapping non-const-member-function functor calls of same signatures.
        * maintains a std::vector<std::function> with static lifetime.
    */  template<class ..._signature>
        class MethodContainer<methodQ::NonConst, _signature...> : public SetupMethod<MethodContainer<methodQ::NonConst, _signature...>>,
                                                                  public CallReflector<MethodContainer<methodQ::NonConst, _signature...>>
        {
            using MethodLambda = std::function < access::RObject (error&, const rtl::access::RObject&, _signature...) >;

        public:

            //every MethodContainer<methodQ::NonConst,...> will have a unique-id.
            static std::size_t getContainerId() {
                return m_containerId;
            }

            //get the vector holding lambdas as 'const-ref'
            static const std::vector<MethodLambda>& getMethodFunctors() {
                return m_methodPtrs;
            }

            //get container type as string
            template<class _recordType, class _returnType>
            static std::string getSignatureStr() 
            {
                return (TypeId<_returnType>::toString() + " " + TypeId<_recordType>::toString() + 
                        "::(" + TypeId<_signature...>::toString() + ")");
            }

        private:

            //holds unique-id
            static const std::size_t m_containerId;

            //vector holding lambdas
            static std::vector<MethodLambda> m_methodPtrs;

        /*  @method: pushBack
            @params: pFunctor (lambda containing non-const-member-function functor call)
                     pGetIndex (lambda providing index if the functor is already registered)
                     pUpdate (lambda updating the already registered functors set)
            @return: index of newly added or already existing lambda in vector 'm_methodPtrs'.
        */  static std::size_t pushBack(const MethodLambda& pFunctor,
                                        std::function<const std::size_t()> pGetIndex,
                                        std::function<void(const std::size_t&)> pUpdateIndex)
            {
                //critical section, thread safe.
                static std::mutex mtx;
                std::lock_guard<std::mutex> lock(mtx);

                std::size_t index = pGetIndex();
                if (index == -1) {
                    index = m_methodPtrs.size();
                    pUpdateIndex(index);
                    m_methodPtrs.push_back(pFunctor);
                }
                return index;
            }

            //friends :)
            friend ReflectionBuilder;
            friend SetupMethod<MethodContainer<methodQ::NonConst, _signature...>>;
        };

        template<class ..._signature>
        const std::size_t MethodContainer<methodQ::NonConst, _signature...>::m_containerId = g_containerIdCounter.fetch_add(1);

        template<class ..._signature>
        std::vector<typename MethodContainer<methodQ::NonConst, _signature...>::MethodLambda>
        MethodContainer<methodQ::NonConst, _signature...>::m_methodPtrs;
    }
	

    namespace detail
    {
    /*  @class: MethodContainer<methodQ::Const, _signature...>
        @param: '_signature...' (combination of any types)
        * container class for holding lambda's wrapping const-member-function functor calls of same signatures.
        * maintains a std::vector<std::function> with static lifetime.
    */  template<class ..._signature>
        class MethodContainer<methodQ::Const, _signature...> : public SetupMethod<MethodContainer<methodQ::Const, _signature...>>,
                                                               public CallReflector<MethodContainer<methodQ::Const, _signature...>>
        {
            using MethodLambda = std::function < access::RObject (error&, const rtl::access::RObject&, _signature...) >;

        public:

            //every MethodContainer<methodQ::Const,...> will have a unique-id.
            static std::size_t getContainerId() {
                return m_containerId;
            }

            //get the vector holding lambdas as 'const-ref'
            static const std::vector<MethodLambda>& getMethodFunctors() {
                return  m_methodPtrs;
            }

            //get container type as string
            template<class _recordType, class _returnType>
            static std::string getSignatureStr() 
            {
                return (TypeId<_returnType>::toString() + " " + TypeId<_recordType>::toString() + 
                       "::(" + TypeId<_signature...>::toString() + ") const");
            }

        private:

            //holds unique-id
            static const std::size_t m_containerId;

            //vector holding lambdas
            static std::vector<MethodLambda> m_methodPtrs;

        /*  @method: pushBack
            @params: pFunctor (lambda containing const-member-function functor call)
                     pGetIndex (lambda providing index if the functor is already registered)
                     pUpdate (lambda updating the already registered functors set)
            @return: index of newly added or already existing lambda in vector 'm_methodPtrs'.
        */  static std::size_t pushBack(const MethodLambda& pFunctor,
                                        std::function<const std::size_t()> pGetIndex,
                                        std::function<void(const std::size_t&)> pUpdateIndex)
            {
                //critical section, thread safe.
                static std::mutex mtx;
                std::lock_guard<std::mutex> lock(mtx);

                std::size_t index = pGetIndex();
                if (index == -1) {
                    index = m_methodPtrs.size();
                    pUpdateIndex(index);
                    m_methodPtrs.push_back(pFunctor);
                }
                return index;
            }

            //friends :)
            friend ReflectionBuilder;
            friend SetupMethod<MethodContainer<methodQ::Const, _signature...>>;
        };

        template<class ..._signature>
        const std::size_t MethodContainer<methodQ::Const, _signature...>::m_containerId = g_containerIdCounter.fetch_add(1);

        template<class ..._signature>
        std::vector<typename MethodContainer<methodQ::Const, _signature...>::MethodLambda> 
        MethodContainer<methodQ::Const, _signature...>::m_methodPtrs;
    }
}