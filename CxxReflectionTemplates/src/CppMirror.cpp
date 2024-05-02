
#include <cassert>
#include <algorithm>

#include "CppMirror.h"
#include "MethodReflection.h"
#include "ConstructorReflection.h"

using namespace std;

namespace rtl {

	unsigned CtorIdCreater::m_ctorIdCounter = 0;
	unsigned MethodIdCreater::m_methodIdCounter = 0;

	const unsigned CppMirror<>::getClassId(const std::string& pClassName) const
	{
		return (*m_reflTypesKeyMap.at(pClassName)).getReflClassId();
	}

	const ReflClass& CppMirror<>::getClass(const string& pClassName) const
	{
		return *m_reflTypesKeyMap.at(pClassName);
	}

	CppMirror<>::CppMirror(const vector<const ReflClass*>& pReflClasses)
	{
		std::vector<const ReflClass*> reflClasses;
		for (const ReflClass* const reflClass : pReflClasses)
		{
			reflClasses.push_back(reflClass);
			const bool classNameUnambiguous = m_reflTypesKeyMap.emplace(make_pair(reflClass->getClassName(), reflClass)).second;
			assert(classNameUnambiguous && "Class/Type name ambiguous.");
			m_reflTypesIdMap.emplace(make_pair(reflClass->getReflClassId(), reflClass));
		}

		sort(reflClasses.begin(), reflClasses.end(),
		[](const ReflClass* pClass_a, const ReflClass* pClass_b)
		{
			return (pClass_a->getBaseReflClasses().size() < pClass_b->getBaseReflClasses().size());
		});

		for (auto itr = reflClasses.rbegin(); itr != reflClasses.rend(); itr++)
		{
			(*itr)->removeRedundentBaseTypes();
		}

		for (const ReflClass* const reflClass : reflClasses)
		{
			reflClass->inheritMembersFromBase();
			m_reflTypesKeyMap.insert(make_pair(reflClass->getClassName(), reflClass));
		}
	}
}
