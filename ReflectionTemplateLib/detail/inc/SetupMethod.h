#pragma once

#include "FunctorId.h"

namespace rtl {

	namespace detail
	{
    /*  @struct: SetupMethod
        @param: _derivedType (type which inherits this class)
        * creates a lambda to perform call on the registered functor.
        * adds it to the functor-container, maintains the already added functor set as well.
        * deriving classes is MethodContainer<TypeQ::Mute, _signature...> &
          MethodContainer<TypeQ::Const, _signature...>, which must implement -
            - std::size_t& _derived::getContainerId();
            - std::string _derivedType::getSignatureStr();
            - std::size_t& _derived::pushBack(std::function < access::RStatus(_signature...) >,
                                              std::function<const std::size_t()>,
                                              std::function<void(const std::size_t&)>);
        * sets up only non-static-member-function functors in lambda table.
        * called from 'ReflectionBuilder', as _derivedType member.
    */  template<class _derivedType>
		class SetupMethod
		{
		protected:

			template<class _recordType, class _retType, class ..._signature>
			static const detail::FunctorId addFunctor(_retType(_recordType::* pFunctor)(_signature...));

			template<class _recordType, class _retType, class ..._signature>
			static const detail::FunctorId addFunctor(_retType(_recordType::* pFunctor)(_signature...) const);
		};
	}
}