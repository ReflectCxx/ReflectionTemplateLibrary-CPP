#pragma once

#include <mutex>
#include <atomic>
#include <vector>
#include <functional>

#include "Constants.h"

#include "CallReflector.h"
#include "SetupMethod.hpp"

namespace rtl {

    namespace detail
    {
        //forward decl
        class ReflectionBuilder;
        //unique id generator.
        extern std::atomic<std::size_t> g_containerIdCounter;

        template<TypeQ, class ..._signature>
        class MethodContainer;

    /*  @class: MethodContainer<TypeQ::Mute, _signature...>
        @param: '_signature...' (combination of any types)
        * container class for holding lambda's wrapping non-const-member-function functor calls of same signatures.
        * maintains a std::vector<std::function> with static lifetime.
    */  template<class ..._signature>
        class MethodContainer<TypeQ::Mute, _signature...> : public SetupMethod<MethodContainer<TypeQ::Mute, _signature...>>,
                                                            public CallReflector<MethodContainer<TypeQ::Mute, _signature...>>
        {
            using MethodLambda = std::function < access::RStatus(std::any, _signature...) >;

        public:

            //every MethodContainer<TypeQ::Mute,...> will have a unique-id.
            static const std::size_t& getContainerId() {
                return m_containerId;
            }

            //get the vector holding lambdas as 'const-ref'
            static const std::vector<MethodLambda>& getMethodFunctors() {
                return m_methodPtrs;
            }

            //get container type as string
            template<class _recordType, class _returnType>
            static const std::string getSignatureStr() {
                return (TypeId<_returnType>::toString() + " " + TypeId<_recordType>::toString() + "::(" + TypeId<_signature...>::toString() + ")");
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
        */  static const std::size_t pushBack(const MethodLambda& pFunctor,
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
            friend SetupMethod<MethodContainer<TypeQ::Mute, _signature...>>;
        };

        template<class ..._signature>
        const std::size_t MethodContainer<TypeQ::Mute, _signature...>::m_containerId = g_containerIdCounter.fetch_add(1);

        template<class ..._signature>
        std::vector<typename MethodContainer<TypeQ::Mute, _signature...>::MethodLambda>
        MethodContainer<TypeQ::Mute, _signature...>::m_methodPtrs;
    }
	

    namespace detail
    {
    /*  @class: MethodContainer<TypeQ::Const, _signature...>
        @param: '_signature...' (combination of any types)
        * container class for holding lambda's wrapping const-member-function functor calls of same signatures.
        * maintains a std::vector<std::function> with static lifetime.
    */  template<class ..._signature>
        class MethodContainer<TypeQ::Const, _signature...> : public SetupMethod<MethodContainer<TypeQ::Const, _signature...>>,
                                                             public CallReflector<MethodContainer<TypeQ::Const, _signature...>>
        {
            using MethodLambda = std::function < access::RStatus(std::any, _signature...) >;

        public:

            //every MethodContainer<TypeQ::Const,...> will have a unique-id.
            static const std::size_t& getContainerId() {
                return m_containerId;
            }

            //get the vector holding lambdas as 'const-ref'
            static const std::vector<MethodLambda>& getMethodFunctors() {
                return  m_methodPtrs;
            }

            //get container type as string
            template<class _recordType, class _returnType>
            static const std::string getSignatureStr() {
                return (TypeId<_returnType>::toString() + " " + TypeId<_recordType>::toString() + "::(" + TypeId<_signature...>::toString() + ") const");
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
        */  static const std::size_t pushBack(const MethodLambda& pFunctor,
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
            friend SetupMethod<MethodContainer<TypeQ::Const, _signature...>>;
        };

        template<class ..._signature>
        const std::size_t MethodContainer<TypeQ::Const, _signature...>::m_containerId = g_containerIdCounter.fetch_add(1);

        template<class ..._signature>
        std::vector<typename MethodContainer<TypeQ::Const, _signature...>::MethodLambda> 
        MethodContainer<TypeQ::Const, _signature...>::m_methodPtrs;
    }
}