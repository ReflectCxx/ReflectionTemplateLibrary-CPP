/*************************************************************************
 *                                                                       *
 *  Reflection Template Library (RTL) - Modern C++ Reflection Framework  *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP          *
 *                                                                       *
 *  Copyright (c) 2025 Neeraj Singh <reflectcxx@outlook.com>             *
 *  SPDX-License-Identifier: MIT                                         *
 *                                                                       *
 *************************************************************************/


#include "RObject.h"
#include "CxxMirror.h"
#include "ReflectCast.h"

namespace rtl::detail 
{
    std::size_t generate_unique_id()
    {
        // Starts with ONE, ZERO denotes TypeId<>::None. [Never change, critical.]
        static std::atomic<std::size_t> counter{ TypeId<>::None + 1 };
        return counter.fetch_add(1, std::memory_order_relaxed);
    }
}