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
    class RObjectBuilder
    {
        using Cloner = std::function<access::RObject(error&, const access::RObject&, rtl::alloc)>;

        template <class T>
        static Cloner buildCloner();

    public:

        RObjectBuilder() = delete;
        RObjectBuilder(const RObjectBuilder&) = delete;

        static const std::size_t rtlManagedInstanceCount();

        template <class T, rtl::alloc _allocOn>
        static access::RObject build(T&& pVal, const bool pIsConstCastSafe);
    };
}


namespace rtl
{
    inline const std::size_t getRtlManagedHeapInstanceCount()
    {
        return detail::RObjectBuilder::rtlManagedInstanceCount();
    }


    template<class T, std::size_t N>
    inline access::RObject reflect(T(&pArr)[N])
    {
        if constexpr (std::is_same_v<traits::raw_t<T>, char>) {
            return detail::RObjectBuilder::build<std::string_view, alloc::Stack>(std::string_view(pArr, N - 1), !traits::is_const_v<T>);
        }
        else {
            return detail::RObjectBuilder::build<std::vector<T>, alloc::Stack>(std::vector(pArr, pArr + N), !traits::is_const_v<T>);
        }
    }


    template <class T>
    inline access::RObject reflect(T&& pVal)
    {
        using _T = traits::raw_t<T>;
        if constexpr (traits::std_wrapper<_T>::type == detail::Wrapper::None)
        {
            return detail::RObjectBuilder::build<T, alloc::Stack>(std::forward<T>(pVal), !traits::is_const_v<T>);
        }
        else
        {
            constexpr bool isConstCastSafe = !traits::is_const_v<typename traits::std_wrapper<_T>::value_type>;
            return detail::RObjectBuilder::build<T, alloc::Stack>(std::forward<T>(pVal), isConstCastSafe);
        }
    }
}