#pragma once

#include "SmartAny.h"
#include "Function.h"
#include "FunctorContainer.hpp"

namespace rtl {
	
	namespace access 
	{
		template<class _arg0, class ..._args>
		inline const bool Function::hasSignature() const
		{
			auto hash = std::pair<signatureId, functorIndex>();
			const auto& signId = detail::FunctorContainer<_arg0, _args...>::getContainerId();
			return hasSignatureId(signId, hash);
		}


		template<>
		inline const bool Function::hasSignature<void>() const
		{
			auto hash = std::pair<signatureId, functorIndex>();
			const auto& signId = detail::FunctorContainer<>::getContainerId();
			return hasSignatureId(signId, hash);
		}


		template<class ..._args>
		inline SmartAny Function::operator()(_args ...params) const noexcept
		{
			auto hash = std::pair<signatureId, functorIndex>(-1, -1);
			const auto& signId = detail::FunctorContainer<_args...>::getContainerId();
			if (hasSignatureId(signId, hash)) 
			{
				return detail::FunctorContainer<_args...>::reflectFunctionCall(hash.second, params...);
			}
			return SmartAny();
		}


		template<class ..._args>
		inline SmartAny Function::invokeMethod(const SmartAny& pTarget, _args ...params) const
		{
			auto hash = std::pair<signatureId, functorIndex>(-1, -1);
			const auto& signId = detail::FunctorContainer<_args...>::getContainerId();
			if (hasSignatureId(signId, hash))
			{
				return detail::FunctorContainer<_args...>::reflectMethodCall(pTarget, hash.second, params...);
			}
			return SmartAny();
		}


		template<class ..._args>
		inline SmartAny Function::invokeConstructor(const AllocType pAllocTy, _args ...params) const
		{
			auto hash = std::pair<signatureId, functorIndex>(-1, -1);
			const auto& signId = detail::FunctorContainer<_args...>::getContainerId();
			if (hasSignatureId(signId, hash))
			{
				return detail::FunctorContainer<_args...>::reflectConstructorCall(pAllocTy, hash.second, params...);
			}
			return SmartAny();
		}
	}
}