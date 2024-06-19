#pragma once

namespace rtl {

	class Function;

	class FunctionBuilder
	{
		const std::string& m_record;
		const std::string& m_function;
		const std::string& m_namespace;

		FunctionBuilder() = delete;

	public:

		FunctionBuilder(const std::string& pNamespace, const std::string& pRecord, const std::string& pFunction);

		template<class _returnType, class ..._signature>
		inline constexpr const Function build(_returnType(*pFunctor)(_signature...)) const
		{
			return Function::addFunctor(m_namespace, m_record, m_function, pFunctor);
		}


		template<class _recordType, class _returnType, class ..._signature>
		inline constexpr const Function build(_returnType(_recordType::* pFunctor)(_signature...)) const
		{
			return Function::addFunctor(m_namespace, m_record, m_function, pFunctor);
		}
	};
}