#pragma once

#include "RObjectConverters.h"

namespace rtl::detail
{
    template<class _fromType>
    std::vector<std::pair<std::size_t, Converter>> RObjectConverter<_fromType>::m_conversions;
}