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
			return (m_signatureId == FunctorContainer<_arg0, _args...>::getContainerId());
		}

		template<>
		inline const bool Function::hasSignature<void>() const
		{
			return (m_signatureId == FunctorContainer<>::getContainerId());
		}

		template<class ..._args>
		inline std::unique_ptr<RObject> Function::operator()(_args ...params) const noexcept
		{
			if (m_signatureId == FunctorContainer<_args...>::getContainerId()) {
				return FunctorContainer<_args...>::reflectCall(m_functorId, params...);
			}
			return nullptr;
		}


		template<class ..._args>
		inline std::unique_ptr<RObject> Function::operator()(const std::unique_ptr<RObject>& pTarget, _args ...params) const
		{
			if (m_signatureId == FunctorContainer<_args...>::getContainerId()) {
				return FunctorContainer<_args...>::reflectCall(pTarget, m_functorId, params...);
			}
			return nullptr;
		}
	}
}