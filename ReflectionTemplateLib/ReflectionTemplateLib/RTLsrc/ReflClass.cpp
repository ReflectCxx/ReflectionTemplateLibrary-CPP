
#include <iostream>

#include "ReflClass.h"
#include "CppMirror.h"
#include "ReflMethod.hpp"

using namespace std;

namespace rtl {

	unsigned ReflClass::instanceCount = 0;

	ReflClass::ReflClass(const char* pTypeName)
	: m_reflClassId(instanceCount++)
	, m_className(pTypeName)
	, m_deleteFunctor(nullptr)
	{
	}

	void ReflClass::initReflectedMethods(const multimap<const string, const ReflMethod>& pFunctions) const
	{
		for (const auto& itr : pFunctions)
		{
			auto reflFuncItr = m_reflFunctions.emplace(itr);
			if (!reflFuncItr.second)
			{
				reflFuncItr.first->second.mergeOverloads(itr.second);
			}
			else
			{
				reflFuncItr.first->second.setOwnerClass(*this);
			}
		}
	}

	void ReflClass::inheritMembersFromBase() const
	{
		//cout << "\n[Inheriting]..\t" << m_className << "\t\t->{ ";
		for (const ReflClass* const baseClass : m_baseReflTypes)
		{
			for (const auto& itr : baseClass->m_reflFunctions)
			{
				auto reflFuncItr = m_reflFunctions.emplace(itr);
				if (!reflFuncItr.second)
				{
					auto& reflMethod = reflFuncItr.first->second;
					const bool isAlreadyInherited = (reflMethod.m_ownerReflClass != this);
					reflMethod.mergeInheritedOverloads(itr.second, isAlreadyInherited);
				}
			}
			//cout << " " << baseClass->m_className << ",";
		}
		//cout << (m_baseReflTypes.size() == 0 ? " }" : "\b }") << "(" << m_baseReflTypes.size() << ")";
	}

	void ReflClass::removeRedundentBaseTypes() const
	{
		for (size_t index = 0; index < m_baseReflTypes.size(); index++)
		{
			if (m_baseReflTypes.at(index) != nullptr)
			{
				for (const ReflClass* const baseClass : m_baseReflTypes)
				{
					if (baseClass != nullptr)
					{
						const auto& superBaseClasses = baseClass->m_baseReflTypes;
						if (find(superBaseClasses.begin(), superBaseClasses.end(), m_baseReflTypes.at(index)) != superBaseClasses.end())
						{
							m_baseReflTypes.at(index) = nullptr;
							break;
						}
					}
				}
			}
		}
		m_baseReflTypes.erase(remove(m_baseReflTypes.begin(), m_baseReflTypes.end(), nullptr), m_baseReflTypes.end());
		m_baseReflTypes.shrink_to_fit();
	}
}