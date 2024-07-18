#pragma once

#include "Constants.h"

namespace rtl {

	namespace builder 
	{
		template<class _recordType, class ..._ctorSignature>
		class ConstructorBuilder
		{
			const std::string& m_record;
			const std::string& m_namespace;
			const FunctorType m_ctorType;

			ConstructorBuilder() = delete;

		public:

			ConstructorBuilder(const std::string& pNamespace, const std::string& pRecord,
					   const FunctorType& pCtorType);

			inline constexpr const access::Function build() const;
		};
	}
}