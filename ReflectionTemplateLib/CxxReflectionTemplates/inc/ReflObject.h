#pragma once

#include <memory>

#include "TypeConstants.h"

namespace rtl 
{
	template<class _objTy = void>
	class ReflObject : public std::unique_ptr<_objTy, DctorFunctor>
	{
		const unsigned m_objTypeId;

	public:

		ReflObject(const unsigned pObjTypeId, _objTy* pObject, DctorFunctor pDeleter);

		template<class _ptrTy>
		static ReflObject create(_ptrTy* pObject, const unsigned pReflId = -1);

		template<class _ptrTy>
		static ReflObject create(std::unique_ptr<_ptrTy> pSrcPtr, const unsigned pReflId = -1);

		template<class _ptrTy>
		static ReflObject create(std::unique_ptr<_ptrTy>& pSrcPtr, const unsigned pReflId = -1);

		const unsigned getTypeId() const;
	};
}
