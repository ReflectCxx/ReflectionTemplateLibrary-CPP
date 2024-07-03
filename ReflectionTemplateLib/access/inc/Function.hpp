#pragma once

#include "RStatus.h"
#include "Function.h"
#include "UniqueAny.h"
#include "FunctorContainer.h"
#include "ConstructorContainer.h"

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
		inline RStatus Function::operator()(_args ...params) const noexcept
		{
			auto hash = std::pair<signatureId, functorIndex>(-1, -1);
			const auto& signId = detail::FunctorContainer<_args...>::getContainerId();
			if (hasSignatureId(signId, hash))
			{
				return detail::FunctorContainer<_args...>::reflectFunctionCall(hash.second, params...);
			}
			return RStatus(false);
		}


		template<class ..._args>
		inline RStatus Function::invokeMethod(UniqueAny& pTarget, _args ...params) const
		{
			auto hash = std::pair<signatureId, functorIndex>(-1, -1);
			const auto& signId = detail::MethodContainer<typeQ::Vol, _args...>::getContainerId();
			if (hasSignatureId(signId, hash))
			{
				return detail::MethodContainer<typeQ::Vol, _args...>::reflectMethodCall(pTarget, hash.second, params...);
			}
			return RStatus(false);
		}


		template<class ..._args>
		inline RStatus Function::invokeMethod(const UniqueAny& pTarget, _args ...params) const
		{
			auto hash = std::pair<signatureId, functorIndex>(-1, -1);
			const auto& signId = detail::MethodContainer<typeQ::Const, _args...>::getContainerId();
			if (hasSignatureId(signId, hash))
			{
				//detail::MethodContainer<_args...>::reflectMethodCall(pTarget, hash.second, params...);
			}
			return RStatus(false);
		}


		template<class ..._args>
		inline RStatus Function::invokeConstructor(_args ...params) const
		{
			auto hash = std::pair<signatureId, functorIndex>(-1, -1);
			const auto& signId = detail::ConstructorContainer<_args...>::getContainerId();
			if (hasSignatureId(signId, hash))
			{
				return detail::ConstructorContainer<_args...>::reflectConstructorCall(hash.second, params...);
			}
			return RStatus(false);
		}
	}
}