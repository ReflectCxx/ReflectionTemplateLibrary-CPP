/*************************************************************************
 *                                                                       *
 *  Reflection Template Library (RTL) - Modern C++ Reflection Framework  *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP          *
 *                                                                       *
 *  Copyright (c) 2025 Neeraj Singh <reflectcxx@outlook.com>             *
 *  SPDX-License-Identifier: MIT                                         *
 *                                                                       *
 *************************************************************************/

#include <atomic>

#include "Record.h"
#include "CxxMirror.h"
#include "ReflectCast.h"

namespace rtl
{
    namespace detail
    {
        std::size_t generate_unique_id()
        {
            // Starts with ONE, ZERO denotes TypeId<>::None. [Never change, critical.]
            static std::atomic<std::size_t> counter{ TypeId<>::None + 1 };
            return counter.fetch_add(1, std::memory_order_relaxed);
        }
    }

/*  @Constructor: CxxMirror
    @params: 'const std::vector<Function>&'
    * accepts vector of 'Function' objects, which are hash-key to lookup a functor.
    * the only constructor to construct 'CxxMirror' object.
    * Syntax for constructing - CxxMirror({ type().function("func_name").build(), ..., ... })
    * '.build()' function will return a 'Function' object, and passed to std::vector initializer list.
    * the vector is simply forwarded to the base class constructor.
*/
    CxxMirror::CxxMirror(const std::vector<Function>& pFunctions) : detail::CxxReflection(pFunctions)
    {
        rtl::detail::ReflectedConversions::init();
    }
}