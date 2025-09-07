#pragma once

#include "RObjectBuilder.hpp"

namespace rtl::detail 
{
    template<class _retT, class... _signature>
    struct LambdaFunction 
    {
        using Invoker = _retT(*)(void* , _signature&...);

        Invoker m_invoker = nullptr;
        void* m_storage = nullptr;

        template<class _returnType>
        void init(_returnType(*pFunctor)(_signature...))
        {
            struct Holder {
                
                using Functor = decltype(pFunctor);
                Functor m_functor;

                Holder(Functor pFptr) : m_functor(pFptr) { }
            };

            static auto holder = Holder{ pFunctor };
            m_storage = &holder;

            m_invoker = +[](void* stor, _signature&... params) -> _retT {

                auto h = static_cast<Holder*>(stor);
                return (h->m_functor)(params...);
            };
        }

        _retT operator()(_signature&... params)
        {
            return m_invoker(m_storage, params...);
        }
    };
}