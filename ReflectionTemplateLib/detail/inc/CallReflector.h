#pragma once

#include <optional>
#include "Constants.h"

namespace rtl {

	namespace access {
		class RStatus;
	}

	namespace detail
	{
		template<class _derivedType>
		struct CallReflector
		{
			template<class ..._params>
			static access::RStatus reflectFunctionCall(std::size_t pFunctorId, const std::size_t pHashCode, _params..._args) 
			{
				const auto& functor = _derivedType::getFunctors().at(pFunctorId);
				if (functor.first == pHashCode) {
					return functor.second(_args...);
				}
				return access::RStatus(Error::SignatureMismatch);
			}


			template<class ..._params>
			static access::RStatus reflectMethodCall(const std::any& pTarget, std::size_t pFunctorId, const std::size_t pHashCode, _params..._args)
			{
				const auto& functor = _derivedType::getMethodFunctors().at(pFunctorId);
				if (functor.first == pHashCode) {
					return functor.second(pTarget, _args...);
				}
				return access::RStatus(Error::SignatureMismatch);
			}
		};
	}
}