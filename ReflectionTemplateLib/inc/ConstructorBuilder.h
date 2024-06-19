#pragma once

namespace rtl {

	class Function;

	template<class _recordType>
	class ConstructorBuilder
	{
		const std::string& m_record;
		const std::string& m_namespace;

		ConstructorBuilder() = delete;

	public:

		ConstructorBuilder(const std::string& pNamespace, const std::string& pRecord);

		template<class ..._ctorSignature>
		inline constexpr const Function build() const;
	};
}