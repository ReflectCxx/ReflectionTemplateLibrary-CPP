
#include "Proxy.h"
#include "OriginalReflection.h"

namespace proxy_test 
{
	Proxy::Proxy()
	{		
		auto [status, obj] = OriginalReflection::obj().classRef()->instance();
		if (status == rtl::Error::None) {
			m_originalObj = obj;
		}
	}
}