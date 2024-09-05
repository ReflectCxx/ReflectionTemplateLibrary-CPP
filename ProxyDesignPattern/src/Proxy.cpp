#include "Proxy.h"

namespace proxy_test 
{
	Proxy::Proxy(): m_originalClass(m_reflection.getRecord("Original"))
	{
		if (m_originalClass) 
		{
			auto [status, obj] = m_originalClass->instance();
			if (status == rtl::Error::None) {
				m_originalObj = obj;
			}
		}
	}
}