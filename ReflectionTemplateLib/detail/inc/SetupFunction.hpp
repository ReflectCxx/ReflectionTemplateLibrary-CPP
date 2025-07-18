
#include "RObject.hpp"
#include "RObjectBuilder.h"
#include "SetupFunction.h"

namespace rtl
{
    namespace detail
    {
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
            const auto& retTypeId = TypeId<remove_const_n_ref_n_ptr<_returnType>>::get();

        /*  a variable arguments lambda, which finally calls the 'pFunctor' with 'params...'.
            this is stored in _derivedType's (FunctorContainer) vector holding lambda's.
        */  const auto functor = [=](error& pError, _signature&&...params)-> access::RObject
            {
                //if functor does not returns anything, this 'if' block is retained and else block is omitted by compiler.
                if constexpr (std::is_same_v<_returnType, void>) {

                    //call will definitely be successful, since the signature type has alrady been validated.
                    (*pFunctor)(std::forward<_signature>(params)...);
                    pError = error::None;
                    return access::RObject();
                }
                else //if functor returns value, this 'else' block is retained and 'if' block is omitted by compiler.
                {
                    if constexpr (std::is_reference_v<_returnType>)
                    {
                        if constexpr (std::is_const_v<std::remove_reference_t<_returnType>>)
                        {
                            pError = error::None;
                            //call will definitely be successful, since the signature type has alrady been validated.
                            const _returnType& retObj = (*pFunctor)(std::forward<_signature>(params)...);
                            return RObjectBuilder::build(&retObj, nullptr, alloc::None);
                        }
                        else
                        {
                            pError = error::None;
                            //call will definitely be successful, since the signature type has alrady been validated.
                            const _returnType& retObj = (*pFunctor)(std::forward<_signature>(params)...);
                            return RObjectBuilder::build(&retObj, nullptr, alloc::None);
                        }
                    }
                    else
                    {
                        pError = error::None;
                        //call will definitely be successful, since the signature type has alrady been validated.
                        return RObjectBuilder::build((*pFunctor)(std::forward<_signature>(params)...), nullptr, alloc::None);
                    }
                }
            };

            //finally add the lambda 'functor' in 'FunctorContainer' lambda vector and get the index.
            std::size_t index = _derivedType::pushBack(functor, getIndex, updateIndex);

            //construct the hash-key 'FunctorId' and return.
            return detail::FunctorId(index, retTypeId, pRecordId, _derivedType::getContainerId(),
                                     _derivedType::template getSignatureStr<_returnType>());
        }
    }
}