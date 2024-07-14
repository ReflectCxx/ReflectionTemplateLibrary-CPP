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
			static access::RStatus forwardCall(std::size_t pFunctorIndex, _params..._args) 
			{
				return _derivedType::getFunctors().at(pFunctorIndex)(_args...);
			}


			template<class ..._params>
			static access::RStatus forwardCall(const std::any& pTarget, std::size_t pFunctorIndex, _params..._args)
			{
				return _derivedType::getMethodFunctors().at(pFunctorIndex)(pTarget, _args...);
			}
		};
	}
}