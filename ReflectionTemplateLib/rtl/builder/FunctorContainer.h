/*************************************************************************
 *                                                                       *
 *  Reflection Template Library (RTL) - Modern C++ Reflection Framework  *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP          *
 *                                                                       *
 *  Copyright (c) 2025 Neeraj Singh <reflectcxx@outlook.com>             *
 *  SPDX-License-Identifier: MIT                                         *
 *                                                                       *
 *************************************************************************/


#pragma once

#include <mutex>
#include <vector>
#include <functional>

#include "rtl_traits.h"

namespace rtl {

    namespace detail
    {
        template<class ..._signature>
        class FunctorContainer
        {
        public:

            ForceInline static std::size_t getContainerId() {
                static const std::size_t containerId = generate_unique_id();
                return containerId;
            }
        };
    }
}