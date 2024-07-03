#pragma once

#include <optional>
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
			static access::RStatus reflectFunctionCall(std::size_t pFunctorId, const std::size_t pHashCode, _params..._args) 
			{
				const auto& functor = _derivedType::getFunctors().at(pFunctorId);
				if (functor.first == pHashCode) {
					return functor.second(_args...);
				}
				return access::RStatus(false);
			}


			template<class ..._params>
			static access::RStatus reflectConstructorCall(std::size_t pFunctorId, const std::size_t pHashCode, _params..._args)
			{
				const auto& functor = _derivedType::getCtorFunctors().at(pFunctorId);
				if (functor.first == pHashCode) {
					return functor.second(_args...);
				}
				return access::RStatus(false);
			}


			template<class ..._params>
			static access::RStatus reflectMethodCall(access::UniqueAny& pTarget, std::size_t pFunctorId, const std::size_t pHashCode, _params..._args)
			{
				const auto& functor = _derivedType::getMethodFunctors().at(pFunctorId);
				if (functor.first == pHashCode) {
					return functor.second(pTarget, _args...);
				}
				return access::RStatus(false);
			}


			template<class ..._params>
			static access::RStatus reflectMethodCall(const access::UniqueAny& pTarget, std::size_t pFunctorId, const std::size_t pHashCode, _params..._args)
			{
				const auto& functor = _derivedType::getMethodFunctors().at(pFunctorId);
				if (functor.first == pHashCode) {
					return functor.second(pTarget, _args...);
				}
				return access::RStatus(false);
			}
		};
	}
}