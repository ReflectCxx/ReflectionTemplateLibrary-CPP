/*_________________________________________________________________________
* Copyright 2025 Neeraj Singh
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
___________________________________________________________________________*/


#include "RObject.h"
#include "CxxMirror.h"
#include "ReflectCast.h"

namespace rtl::detail 
{
    //type id counter, statically initializes a unique-id to TypeId<...>.
    std::atomic<std::size_t> g_typeIdCounter = TypeId<>::None + 1;

    //type id counter, statically initializes a unique-id to FunctorContainer<...> and MethodContainer<...>.
    std::atomic<std::size_t> g_containerIdCounter = TypeId<>::None + 1;
}


namespace rtl::access {

    std::atomic<std::size_t> RObject::m_rtlManagedInstancesCount = 0;

    /*  @Constructor: CxxMirror
        @params: 'const std::vector<Function>&'
        * accepts vector of 'Function' objects, which are hash-key to lookup a functor.
        * the only constructor to construct 'CxxMirror' object.
        * Syntax for constructing - CxxMirror({ Reflect().function("func_name").build(), ..., ... })
        * '.build()' function will return a 'Function' object, and passed to std::vector initializer list.
        * the vector is simply forwarded to the base class constructor.
    */  CxxMirror::CxxMirror(const std::vector<Function>& pFunctions) : detail::CxxReflection(pFunctions)
    {
        rtl::detail::ReflectedConversions::init();
    }
}