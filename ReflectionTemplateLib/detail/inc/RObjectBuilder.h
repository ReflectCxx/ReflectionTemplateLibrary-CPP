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

#include "rtl_traits.h"

namespace rtl::access {
    class RObject;
}

namespace rtl::detail
{
    struct RObjectBuilder
    {
        RObjectBuilder() = delete;
        RObjectBuilder(const RObjectBuilder&) = delete;

        static const std::size_t reflectedInstanceCount();

        template<class T, rtl::alloc _allocOn = alloc::Stack, traits::enable_if_std_wrapper<T> = 0>
        static access::RObject build(T&& pVal);

        template<class T, rtl::alloc _allocOn = alloc::Stack, traits::enable_if_not_std_wrapper<T> = 0>
        static access::RObject build(T&& pVal);
    };
}


namespace rtl
{
    template <class T>
    inline access::RObject reflect(T&& pVal)
    {
        return detail::RObjectBuilder::build(std::forward<T>(pVal));
    }

    template<class T, std::size_t N>
    inline access::RObject reflect(T(&pArr)[N])
    {
        if constexpr (std::is_same_v<traits::base_t<T>, char>) {
            return detail::RObjectBuilder::build<std::string_view, alloc::Stack>(std::string_view(pArr, N - 1));
        }
        else {
            return detail::RObjectBuilder::build<std::vector<T>, alloc::Stack>(std::vector(pArr, pArr + N));
        }
    }

    inline const std::size_t getReflectedHeapInstanceCount() 
    {
        return detail::RObjectBuilder::reflectedInstanceCount();
    }
}