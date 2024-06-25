#pragma once

#include "RObject.h"

namespace rtl {

	extern std::size_t g_rObjectTypeIdCounter;

	namespace access
	{
		template<class _objType>
		class ReturnObject : public RObject
		{
			friend RObject;

			_objType m_value;

			static const std::size_t m_typeId;

		public:

			~ReturnObject() override {
			}

			ReturnObject(const std::string& pType, const _objType& pValue)
				: m_value(pValue)
				, RObject(m_typeId, pType)
			{
			}
		};


		/*
		* TODO
		* FixMe: if instead of object pointers, raw pointers are returned (like const char*)
		* test for:
		*	const char* someFunction() {
		*		return "char_litrals_must_not_b_deleted_explicitly";
		*	}
		* Reflect, call & get return test.
		*/
		template<class _objType>
		class ReturnObject<_objType*> : public RObject
		{
			friend RObject;

			_objType* m_value;

			static const std::size_t m_typeId;

		public:

			~ReturnObject() override {
				delete m_value;
			}

			ReturnObject(const std::string& pType, _objType* pValuePtr)
				: m_value(pValuePtr)
				, RObject(m_typeId, pType)
			{
			}
		};


		template<class _type>
		inline std::optional<_type> RObject::get()
		{
			const auto& typeId = ReturnObject<_type>::m_typeId;
			if (getTypeId() == typeId) {

				auto upCastObj = dynamic_cast<ReturnObject<_type>*>(this);
				if (upCastObj != nullptr) {
					return std::optional(upCastObj->m_value);
				}
			}
			return std::nullopt;
		}

		template<class _objType>
		const std::size_t ReturnObject<_objType>::m_typeId = g_rObjectTypeIdCounter++;

		template<class _objType>
		const std::size_t ReturnObject<_objType*>::m_typeId = g_rObjectTypeIdCounter++;
	}
}