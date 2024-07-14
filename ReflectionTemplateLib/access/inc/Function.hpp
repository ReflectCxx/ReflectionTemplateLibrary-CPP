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
			return (hasSignatureId(detail::FunctorContainer<_arg0, _args...>::getContainerId()) != -1);
		}


		template<>
		inline const bool Function::hasSignature<void>() const
		{
			return (hasSignatureId(detail::FunctorContainer<>::getContainerId()) != -1);
		}


		template<class ..._args>
		inline RStatus Function::operator()(_args ...params) const noexcept
		{
			const std::size_t& index = hasSignatureId(detail::FunctorContainer<_args...>::getContainerId());
			if (index != -1)
			{
				return detail::FunctorContainer<_args...>::forwardCall(index, params...);
			}
			return RStatus(Error::SignatureMismatch);
		}


		template<class ..._args>
		inline RStatus Function::call(_args ...params) const noexcept
		{
			const std::size_t& index = hasSignatureId(detail::FunctorContainer<_args...>::getContainerId());
			if (index != -1)
			{
				return detail::FunctorContainer<_args...>::forwardCall(index, params...);
			}
			return RStatus(Error::SignatureMismatch);
		}
	}
}