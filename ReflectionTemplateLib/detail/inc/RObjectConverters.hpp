#pragma once

#include "RObjectConverters.h"

namespace rtl::detail
{
    template<class _fromType>
    inline const std::vector<std::pair<std::size_t, Converter>>& RObjectConverter<_fromType>::getConversions()
    {
        return m_converters;
    }
}