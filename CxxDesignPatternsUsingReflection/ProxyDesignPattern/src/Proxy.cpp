#include "Proxy.h"
#include "OriginalReflection.h"

namespace proxy_test
{
    /**
     * @brief Constructs a new Proxy object.
     *
     * Initializes the m_originalObj with an instance of the "Original" class.
     * If the instance creation is successful, m_originalObj is set to the created instance.
     */
    Proxy::Proxy()
    {
        auto [status, obj] = OriginalReflection::getClass()->instance<rtl::access::AllocOn::Heap>();
        if (status == rtl::Error::None) {
            m_originalObj = obj;
        }
    }
}
