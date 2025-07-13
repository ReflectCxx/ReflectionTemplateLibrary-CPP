
#include "RObject.h"

namespace rtl::access {

    std::vector<ConverterPair> RObject::m_conversions = { };

    const std::size_t RObject::getConverterIndex(const std::size_t& pToTypeId) const
    {
        for (std::size_t index = 0; index < m_converters.size(); index++)
        {
            if (m_converters[index].first == pToTypeId) {
                return index;
            }
        }
        return -1;
    }
}