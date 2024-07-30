
#include "RStatus.h"
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
        inline const detail::FunctorId SetupFunction<_derivedType>::addFunctor(_returnType(*pFunctor)(_signature...))
        {

        /*  set of already registered functors. (static life time).
            used std::vector, since std::set/map are not designed for function pointers
        */  static std::vector<std::pair<decltype(pFunctor), std::size_t>> functorSet;

        /*  adds the generated functor index to the 'functorSet'. (thread safe).
            called from '_derivedType' ('FunctorContainer')
        */  const auto& updateIndex = [&](const std::size_t& pIndex) 
            {
                functorSet.emplace_back(pFunctor, pIndex);
            };

        /*  checks if the 'pFunctor' is already present in 'functorSet'. (thread safe).
            called from '_derivedType' ('FunctorContainer')
        */  const auto& getIndex = [&]()->const std::size_t 
            {
                //linear search, efficient for small set.
                for (const auto& fptr : functorSet) {
                    if (fptr.first == pFunctor) {
                        //functor already registered, return its 'index'.
                        return fptr.second;
                    }
                }
                //functor is not already registered, return '-1'.
                return -1;
            };

            //generate a type-id of '_returnType'.
            const auto& retTypeId = TypeId<_returnType>::get();

        /*  a variable arguments lambda, which finally calls the 'pFunctor' with 'params...'.
            this is stored in _derivedType's (FunctorContainer) vector holding lambda's.
        */  const auto functor = [=](_signature...params)->access::RStatus
            {
                //if functor does not returns anything, this 'if' block is retained and else block is omitted by compiler.
                if constexpr (std::is_same_v<_returnType, void>) {

                    //call will definitely be successful, since the signature type has alrady been validated.
                    (*pFunctor)(params...);
                    return access::RStatus(Error::None);
                }
                //if functor returns value, this 'else' block is retained and 'if' block is omitted by compiler.
                else {
                    //call will definitely be successful, since the signature type has alrady been validated.
                    const _returnType& retObj = (*pFunctor)(params...);
                    const TypeQ& qualifier = std::is_const<_returnType>::value ? TypeQ::Const : TypeQ::Mute;
                    //return 'RStatus' with return value wrapped in it as std::any.
                    return access::RStatus(std::make_any<_returnType>(retObj), retTypeId, qualifier);
                }
            };

            //finally add the lambda 'functor' in 'FunctorContainer' lambda vector and get the index.
            const std::size_t& index = _derivedType::pushBack(functor, getIndex, updateIndex);

            //construct the hash-key 'FunctorId' and return.
            return detail::FunctorId(index, retTypeId, TypeId<>::None, _derivedType::getContainerId(),
                                     _derivedType::template getSignatureStr<_returnType>());
        }
    }
}