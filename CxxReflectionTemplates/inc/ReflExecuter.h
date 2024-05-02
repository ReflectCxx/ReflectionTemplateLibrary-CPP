#pragma once

#include "TypeConstants.h"

namespace rtl 
{
	template<typeQ _targetType>
	class ReflExecuter;

	class ReflMethod;

	class Executer 
	{
	protected:

		void* const m_targetObj;
		const unsigned m_targetTypeId;
		const ReflMethod& m_reflMethod;

		Executer() = delete;
		Executer(const ReflMethod& pReflMethod, const unsigned pTargetTypeId, void* const pTarget);
	};

	template<>
	class ReflExecuter<typeQ::CONST> : public Executer
	{
		ReflExecuter(const ReflMethod& pReflMethod, const unsigned pTargetTypeId, const void* pTarget);

	public: friend ReflMethod;

		template<class _retType = void, class..._args>
		_retType invoke(_args...params) const;
	};

	template<>
	class ReflExecuter<typeQ::MUTABLE> : public Executer
	{
		ReflExecuter(const ReflMethod& pReflMethod, const unsigned pTargetTypeId, void* pTarget);

	public: friend ReflMethod;

		template<class _retType = void, class..._args>
		_retType invoke(_args...params) const;
	};
}
