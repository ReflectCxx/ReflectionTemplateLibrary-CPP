#pragma once

namespace rtl {

	class RObject
	{
	public:

		virtual ~RObject() = 0;
	};


	template<class _objType>
	class ReturnObject : public RObject 
	{
		_objType m_value;

	public:

		~ReturnObject();
		ReturnObject() = delete;

		ReturnObject(const _objType& pValue);
	};


	template<class _objType>
	class ReturnObject<_objType*> : public RObject
	{
		_objType* m_valuePtr;

	public:

		~ReturnObject();
		ReturnObject() = delete;

		ReturnObject(_objType* pValuePtr);
	};
}
