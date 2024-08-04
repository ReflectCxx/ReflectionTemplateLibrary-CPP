#pragma once

#include <mutex>
#include <atomic>
#include <vector>
#include <functional>

#include "Constants.h"
#include "CallReflector.h"
#include "SetupFunction.hpp"
#include "SetupConstructor.hpp"

namespace rtl {

    namespace detail
    {
        //forward decl
        class ReflectionBuilder;
        //unique id generator.
        extern std::atomic<std::size_t> g_containerIdCounter;

    /*  @class: FunctorContainer
        @param: '_signature...' (combination of any types)
        * container class for holding lambda's wrapping functor, constructor/destructor calls of same signatures.
        * maintains a std::vector<std::function> with static lifetime.
    */  template<class ..._signature>
        class FunctorContainer : public SetupFunction<FunctorContainer<_signature...>>,
                                 public SetupConstructor<FunctorContainer<_signature...>>,
                                 public CallReflector<FunctorContainer<_signature...>>
        {
            using FunctionLambda = std::function < access::RStatus(_signature...) >;
        public:

            //every FunctorContainer<...> will have a unique-id.
            static const std::size_t& getContainerId() {
                return m_containerId;
            }

            //get the vector holding lambdas as 'const-ref'
            const static std::vector<FunctionLambda>& getFunctors() {
                return m_functors;
            }

            //get functor container type(_signature...) as string with given 'returnType'.
            template<class _returnType>
            static const std::string getSignatureStr(const bool pIsMember = false) {
                const std::string& retStr = TypeId<_returnType>::toString();
                return (retStr + (pIsMember ? "::" : " ") + "(" + TypeId<_signature...>::toString() + ")");
            }

        private:

            //holds unique-id
            static const std::size_t m_containerId;

            //vector holding lambdas
            static std::vector<FunctionLambda> m_functors;

        /*  @method: pushBack
            @params: pFunctor (lambda containing functor or constructor/destructor call)
                     pGetIndex (lambda providing index if the functor is already registered)
                     pUpdate (lambda updating the already registered functors/ctor/d'tor set)
            @return: index of newly added or already existing lambda in vector 'm_functors'.
        */  static const std::size_t pushBack(const FunctionLambda& pFunctor,
                                              std::function<const std::size_t()> pGetIndex,
                                              std::function<void(const std::size_t&)> pUpdate)
            {
                //critical section, thread safe.
                static std::mutex mtx;
                std::lock_guard<std::mutex> lock(mtx);

                std::size_t index = pGetIndex();
                if (index == -1) {
                    index = m_functors.size();
                    pUpdate(index);
                    m_functors.push_back(pFunctor);
                }
                return index;
            }
            
            //friends :)
            friend ReflectionBuilder;
            friend SetupFunction<FunctorContainer<_signature...>>;
            friend SetupConstructor<FunctorContainer<_signature...>>;
        };

        template<class ..._signature>
        const std::size_t FunctorContainer<_signature...>::m_containerId = g_containerIdCounter.fetch_add(1);

        template<class ..._signature>
        std::vector<typename FunctorContainer<_signature...>::FunctionLambda> FunctorContainer<_signature...>::m_functors;
    }
}