
#include <cassert>

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
    : m_originalObj([&]() {
            auto [err, robj] = OriginalReflection::getClass()->create<rtl::alloc::Heap>();
            return (err == rtl::error::None ? std::move(robj) : rtl::access::RObject());
        }())
    {
        assert(!m_originalObj.isEmpty() && "Reflected instance creation failed.");
    }
}
