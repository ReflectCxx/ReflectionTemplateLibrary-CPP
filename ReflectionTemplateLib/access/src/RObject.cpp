
#include "RObject.h"

namespace rtl::access
{
    std::atomic<std::size_t> RObject::m_rtlOwnedRObjectInstanceCount = 0;

    std::size_t RObject::getConverterIndex(const std::size_t pToTypeId) const
    {
        if (!isEmpty()) 
        {
            for (std::size_t index = 0; index < m_objectId.m_converters.size(); index++) {
                if (m_objectId.m_converters[index].first == pToTypeId) {
                    return index;
                }
            }
        }
        return rtl::index_none;
    }
}