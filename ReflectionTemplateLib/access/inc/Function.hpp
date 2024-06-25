#pragma once

#include "TypeList.h"
#include "Function.h"
#include "FunctorContainer.hpp"

namespace rtl {
	
	namespace access 
	{
		template<class _arg0, class ..._args>
		inline const bool Function::hasSignature() const
		{
			auto hash = std::pair<signatureId, functorIndex>();
			const auto& signId = FunctorContainer<_arg0, _args...>::getContainerId();
			return hasSignatureId(signId, hash);
		}


		template<>
		inline const bool Function::hasSignature<void>() const
		{
			auto hash = std::pair<signatureId, functorIndex>();
			const auto& signId = FunctorContainer<>::getContainerId();
			return hasSignatureId(signId, hash);
		}


		template<class ..._args>
		inline std::unique_ptr<RObject> Function::operator()(_args ...params) const noexcept
		{
			auto hash = std::pair<signatureId, functorIndex>(-1, -1);
			const auto& signId = FunctorContainer<_args...>::getContainerId();
			if (hasSignatureId(signId, hash)) 
			{
				return FunctorContainer<_args...>::reflectCall(hash.second, params...);
			}
			return nullptr;
		}


		template<class ..._args>
		inline std::unique_ptr<RObject> Function::operator()(const std::unique_ptr<RObject>& pTarget, _args ...params) const
		{
			auto hash = std::pair<signatureId, functorIndex>(-1, -1);
			const auto& signId = FunctorContainer<_args...>::getContainerId();
			if (hasSignatureId(signId, hash))
			{
				return FunctorContainer<_args...>::reflectCall(pTarget, hash.second, params...);
			}
			return nullptr;
		}
	}
}