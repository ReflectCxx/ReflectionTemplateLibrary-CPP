#pragma once

#include <vector>

#include "ReflClass.hpp"
#include "ReflObject.hpp"
#include "ReflMethod.hpp"
#include "ReflExecuter.hpp"
#include "ReflInheritanceBuilder.h"

namespace rtl {

	template<class..._args>
	class CppMirror;

	template<>
	class CppMirror<> {

		mutable ReflectedClassMap m_reflTypesKeyMap;
		mutable ReflectedClassIdMap m_reflTypesIdMap;

	public :

		CppMirror() = delete;
		CppMirror(const std::vector<const ReflClass*>& pMetaClasses);

		const unsigned getClassId(const std::string& pClassName) const;
		const ReflClass& getClass(const std::string& pClassName) const;
	};

	template<class..._args>
	class CppMirror : public ReflInheritanceBuilder< TypeList<_args...> >, public CppMirror<>
	{
	public:

		CppMirror() = delete;
		CppMirror(const std::vector<const ReflClass*>& pMetaClasses) : CppMirror<>(pMetaClasses) {}
	};

	template<class..._args>
	class CppMirror< TypeList<_args...> > : public ReflInheritanceBuilder< TypeList<_args...> >, public CppMirror<>
	{
	public:

		CppMirror() = delete;
		CppMirror(const std::vector<const ReflClass*>& pMetaClasses) : CppMirror<>(pMetaClasses) {}
	};
}