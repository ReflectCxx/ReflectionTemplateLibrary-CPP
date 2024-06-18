#include "RObject.h"

namespace rtl {

	template<class _objType>
	inline ReturnObject<_objType>::~ReturnObject()
	{
	}

	template<class _objType>
	inline ReturnObject<_objType*>::~ReturnObject()
	{
		delete m_valuePtr;
	}

	template<class _objType>
	inline ReturnObject<_objType>::ReturnObject(const _objType& pValue)
		:m_value(pValue)
	{
	}

	template<class _objType>
	inline ReturnObject<_objType*>::ReturnObject(_objType* pValuePtr)
		:m_valuePtr(pValuePtr)
	{
	}
}