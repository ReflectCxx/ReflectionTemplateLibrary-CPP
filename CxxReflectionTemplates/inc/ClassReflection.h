#pragma once

#include <string>

#include "ReflClass.h"

namespace rtl {

	struct ReflClassBuilder;

	template<class _classType>
	class ClassReflection : public ReflClass
	{
		static const ClassReflection<_classType> Instance;

		ClassReflection();
		void initInstance(const std::string& pClassName) const;

	public: friend ReflClassBuilder; friend ReflClass;

		ClassReflection(const ClassReflection&) = delete;
		ClassReflection(const ClassReflection&&) = delete;
		const ClassReflection& operator=(const ClassReflection&) = delete;
		const ClassReflection& operator=(const ClassReflection&&) = delete;

		const ClassReflection* add(const std::multimap<const std::string, const ReflMethod>& pFunctions) const;

		static const bool isReflTypeIdSame(const unsigned pTypeId);
		static const InheritanceCastFunctor getSafeUpCastFptr(unsigned pReflTypeId);
	};
}

