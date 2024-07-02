#pragma once

#include "Constants.h"
#include "RStatus.h"

namespace rtl {

	namespace detail
	{
		template<class _derivedType>
		class CallReflector
		{
		protected:

			template<class ..._params>
			static access::RStatus reflectFunctionCall(std::size_t pFunctorId, _params..._args) 
			{
				return _derivedType::getFunctors().at(pFunctorId)(_args...);
			}

			template<class ..._params>
			static access::RStatus reflectConstructorCall(std::size_t pFunctorId, _params..._args) 
			{
				return _derivedType::getCtorFunctors().at(pFunctorId)(_args...);
			}

			template<class ..._params>
			static access::RStatus reflectMethodCall(access::UniqueAny& pTarget, std::size_t pFunctorId, _params..._args) 
			{
				return _derivedType::getMethodFunctors().at(pFunctorId)(pTarget, _args...);
			}

			template<class ..._params>
			static access::RStatus reflectMethodCall(const access::UniqueAny& pTarget, std::size_t pFunctorId, _params..._args) 
			{
				//FixMe: this is invalid.
				return _derivedType::getMethodFunctors().at(pFunctorId)(pTarget, _args...);
			}
		};
	}
}