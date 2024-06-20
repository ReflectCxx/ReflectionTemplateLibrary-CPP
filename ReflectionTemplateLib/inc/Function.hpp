#pragma once

#include "TypeList.h"
#include "Function.h"
#include "FunctorContainer.hpp"

namespace rtl {
	
	template<class ..._args>
	inline std::unique_ptr<RObject> Function::execute(_args ...params) const
	{
		if (m_signatureId == FunctorContainer<_args...>::getContainerId()) {
			return FunctorContainer<_args...>::reflectCall(m_functorId, params...);
		}
		else {
			assert(false && "Throw bad call exception");
		}
		return nullptr;
	}


	template<class ..._args>
	inline std::unique_ptr<RObject> Function::execute(const std::unique_ptr<RObject>& pTarget, _args ...params) const
	{
		if (m_signatureId == FunctorContainer<_args...>::getContainerId()) {
			return FunctorContainer<_args...>::reflectCall(pTarget, m_functorId, params...);
		}
		else {
			assert(false && "Throw bad call exception");
		}
		return nullptr;
	}
}