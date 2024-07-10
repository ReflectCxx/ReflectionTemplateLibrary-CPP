#pragma once

#include "RStatus.h"
#include "Function.h"
#include "Instance.h"
#include "FunctorContainer.h"

namespace rtl {

	namespace access
	{
		template<class _arg0, class ..._args>
		inline const bool Function::hasSignature() const
		{
			std::size_t index, hashCode;
			const std::size_t& signId = detail::FunctorContainer<_arg0, _args...>::getContainerId();
			return hasSignatureId(signId, index, hashCode);
		}


		template<>
		inline const bool Function::hasSignature<void>() const
		{
			std::size_t index, hashCode;
			const std::size_t& signId = detail::FunctorContainer<>::getContainerId();
			return hasSignatureId(signId, index, hashCode);
		}


		template<class ..._args>
		inline RStatus Function::operator()(_args ...params) const noexcept
		{
			std::size_t index, hashCode;
			const std::size_t& signId = detail::FunctorContainer<_args...>::getContainerId();
			if (hasSignatureId(signId, index, hashCode))
			{
				return detail::FunctorContainer<_args...>::reflectFunctionCall(index, hashCode, params...);
			}
			return RStatus(false);
		}
	}
}