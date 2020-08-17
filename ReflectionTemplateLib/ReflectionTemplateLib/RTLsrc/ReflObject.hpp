#pragma once

#include "ReflObject.h"

namespace rtl 
{
	template<class _objTy>
	inline ReflObject<_objTy>::ReflObject(const unsigned pObjTypeId, _objTy* pObject, DctorFunctor pDeleter)
	: std::unique_ptr<_objTy, DctorFunctor>(pObject, pDeleter)
	, m_objTypeId(pObjTypeId)
	{

	}

	template<class _objTy>
	inline const unsigned ReflObject<_objTy>::getTypeId() const
	{
		return m_objTypeId;
	}
	
	template<class _objTy>
	template<class _ptrTy>
	inline ReflObject<_objTy> ReflObject<_objTy>::create(_ptrTy* pObject, const unsigned pReflId)
	{
		static_assert(!std::is_same<_ptrTy, void>::value, "cannot create ReflObject with void pointer");

		return ReflObject(pReflId, pObject,
		[](const void* pTarget)->void
		{
			delete static_cast<const _ptrTy*>(pTarget);
		});
	}

	template<class _objTy>
	template<class _ptrTy>
	inline ReflObject<_objTy> ReflObject<_objTy>::create(std::unique_ptr<_ptrTy> pSrcPtr, const unsigned pReflId)
	{
		return ReflObject(pReflId, pSrcPtr.release(),
		[](const void* pTarget)->void
		{
			delete static_cast<const _ptrTy*>(pTarget);
		});
	}

	template<class _objTy>
	template<class _ptrTy>
	inline ReflObject<_objTy> ReflObject<_objTy>::create(std::unique_ptr<_ptrTy>& pSrcPtr, const unsigned pReflId)
	{
		return ReflObject(pReflId, pSrcPtr.release(),
		[](const void* pTarget)->void
		{
			delete static_cast<const _ptrTy*>(pTarget);
		});
	}
}
