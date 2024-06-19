
#include "Function.h"
#include "ConstructorBuilder.h"

namespace rtl {

	template<class _recordType>
	inline ConstructorBuilder<_recordType>::ConstructorBuilder(const std::string& pNamespace, const std::string& pRecord)
		: m_record(pRecord)
		, m_namespace(pNamespace)
	{
	}


	template<class _recordType>
	template<class ..._ctorSignature>
	inline constexpr const Function ConstructorBuilder<_recordType>::build() const
	{
		return Function::addConstructor<_recordType, _ctorSignature...>(m_namespace, m_record);
	}
}