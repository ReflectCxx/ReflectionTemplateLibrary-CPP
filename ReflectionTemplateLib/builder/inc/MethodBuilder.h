#pragma once

namespace rtl {

	class Function;

	namespace builder 
	{
		template<class _recordType, class ..._signature>
		class MethodBuilder
		{
			const std::string& m_record;
			const std::string& m_method;
			const std::string& m_namespace;

			MethodBuilder() = delete;

		public:

			MethodBuilder(const std::string& pNamespace, const std::string& pRecord, const std::string& pMethod);

			template<class _returnType>
			inline constexpr const access::Function build(_returnType(_recordType::* pFunctor)(_signature...)) const;
		};
	}
}