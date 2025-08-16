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

#pragma once

#include "error_codes.h"

namespace rtl {

    static constexpr std::size_t index_none = static_cast<std::size_t>(-1);

    // MethodQ: Method qualifier + static marker.
    enum class methodQ
    {
        None,       // Static method (no const/non-const qualifier)
        Const,      // Const-qualified instance method
        NonConst    // Non-const instance method
    };


    //Allocation type.
    enum class alloc
    {
        None,       //assigned to empty/moved-from 'RObject's.
        Heap,       //assigned to only rtl-allocated heap objects
        Stack,      //assigned to return-values & rtl-allocated stack objects
        UnwrapHeap,
        UnwrapStack
    };
}


namespace rtl::detail 
{
    enum class Wrapper
    {
        None,
        Any,
        Weak,
        Unique,
        Shared,
        Variant,
        Optional,
        Reference
    };

    enum class EntityKind
    {
        None,
        Value,
        Pointer,
        Wrapper,
        ConstValWrapper
    };


    inline static const std::string ctor_name(const std::string& pRecordName) {
        return (pRecordName + "::" + pRecordName + "()");
    }

#define GETTER(_varType, _name, _var)                       \
    inline constexpr const _varType& get##_name() const {   \
        return _var;                                        \
    }

#define GETTER_REF(_varType, _name, _var)       \
    inline _varType& get##_name() const {       \
        return _var;                            \
    }

#define GETTER_CREF(_varType, _name, _var)       \
    inline const _varType& get##_name() const {  \
        return _var;                             \
    }

#define GETTER_BOOL(_name, _var)              \
    inline const bool is##_name() const {     \
        return _var;                          \
    }

    constexpr const std::string_view NAMESPACE_GLOBAL = "namespace_global";
}