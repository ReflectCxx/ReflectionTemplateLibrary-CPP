#include "Reflect.h"

namespace rtl 
{
	namespace builder 
	{
		Reflect::Reflect()
			: m_record("")
			, m_namespace(NAMESPACE_GLOBAL)
		{
		}

		Reflect& Reflect::nameSpace(const std::string& pNamespace)
		{
			m_namespace = pNamespace;
			return *this;
		}
	}
}