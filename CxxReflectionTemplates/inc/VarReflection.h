#pragma once

// IN PROGRESS

/*
#include <vector>
#include <functional>


namespace rtl {

	template<class _retType, class _fieldType>
	class VarReflection
	{
		static std::vector<std::function<_retType(void*)>> m_functors;

	public:

		VarReflection() = delete;
		VarReflection(const VarReflection&) = delete;
		VarReflection& operator=(const FunctionReflection&) = delete;

		template<class _lambdaTy>
		static std::size_t addField(_lambdaTy pFunctor);

		static _retType access(std::size_t pFunctorIndex, void* pTarget);
	};
}



namespace rtl {

	template<class _fieldType>
	class VarReflection<void, _fieldType>
	{
		static std::vector<std::function<void (void*, _fieldType)>> m_functors;

	public:

		VarReflection() = delete;
		VarReflection(const VarReflection&) = delete;
		VarReflection& operator=(const FunctionReflection&) = delete;

		template<class _lambdaTy>
		static std::size_t addField(_lambdaTy pFunctor);

		static void access(std::size_t pFunctorIndex, void* pTarget);
	};
}

*/