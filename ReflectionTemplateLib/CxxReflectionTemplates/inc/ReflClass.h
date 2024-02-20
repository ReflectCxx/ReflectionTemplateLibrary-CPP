#pragma once

#include <map>
#include <vector>
#include <string>
#include <unordered_map>

#include "ReflMethod.h"

namespace rtl {

	template<class..._args>
	class CppMirror;

	template<class _classType>
	class ClassReflection;

	class ReflClass {

		const unsigned m_reflClassId;
		static unsigned instanceCount;

		mutable std::string m_className;
		mutable std::vector<const ReflClass*> m_baseReflTypes;
		mutable DctorFunctor m_deleteFunctor;

		mutable std::map<const std::string, const ReflMethod> m_reflFunctions;
		mutable std::unordered_map<unsigned, unsigned> m_ctorFunctorTable;

		void inheritMembersFromBase() const;
		void removeRedundentBaseTypes() const;

		template<class _objTy = void, class..._args>
		_objTy* construct(_args...params) const;

	protected:

		mutable std::unordered_map<unsigned, InheritanceCastFunctor> m_safeUpCastFunctors;

		ReflClass() = delete;
		ReflClass(const char* pTypeName);

		template<class _classTy, class _baseTy>
		void initReflectedInheritance() const;
		void initReflectedTypeName(const std::string& pTypenName) const;
		void initReflectedDestructor(const DctorFunctor pDctorFunctor) const;
		void initReflectedConstructor(const unsigned pCtorTypeId, const unsigned pCtorIndex) const;
		void initReflectedMethods(const std::multimap<const std::string, const ReflMethod>& pFunctions) const;

	public: friend CppMirror<>;

		const unsigned getReflClassId() const;
		const bool isCastSafeToTypeId(const unsigned pTypeId) const;
		const ReflMethod& getMethod(const std::string& pFuncName) const;

		const std::string& getClassName() const;
		const std::vector<const ReflClass*>& getBaseReflClasses() const;

		template<class _objTy = void, class..._args>
		ReflObject<_objTy> instance(_args...params) const;

		template<ctor _ctorTy, class _objTy = void>
		ReflObject<_objTy> instance(const ReflObject<_objTy>& pSrcObj, 
					    const sfinae_ctorT<_ctorTy, ctor::COPY>* p_null = nullptr) const;

		template<ctor _ctorTy, class _objTy = void>
		ReflObject<_objTy> instance(const ReflObject<const _objTy>& pSrcObj,
					    const sfinae_ctorT<_ctorTy, ctor::COPY>* p_null = nullptr) const;

		template<class _objTy = void, class..._args>
		ReflObject<const _objTy> instanceConst(_args...params) const;

		template<ctor _ctorTy, class _objTy = void>
		ReflObject<const _objTy> instanceConst(const ReflObject<_objTy>& pSrcObj,
						       const sfinae_ctorT<_ctorTy, ctor::COPY>* p_null = nullptr) const;

		template<ctor _ctorTy, class _objTy = void>
		ReflObject<const _objTy> instanceConst(const ReflObject<const _objTy>& pSrcObj,
						       const sfinae_ctorT<_ctorTy, ctor::COPY>* p_null = nullptr) const;
	};
}
