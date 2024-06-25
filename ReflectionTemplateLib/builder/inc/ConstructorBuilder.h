#pragma once

namespace rtl {

	class Function;

	namespace builder 
	{
		template<class _recordType, class ..._ctorSignature>
		class ConstructorBuilder
		{
			const std::string& m_record;
			const std::string& m_namespace;

			ConstructorBuilder() = delete;

		public:

			ConstructorBuilder(const std::string& pNamespace, const std::string& pRecord);

			inline constexpr const access::Function build() const;
		};
	}
}