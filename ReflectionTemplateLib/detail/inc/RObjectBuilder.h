/*****************************************************************
 *                                                               *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP  *
 *                                                               *
 *  Copyright (c) 2025 Neeraj Singh (reflectcxx@outlook.com)     *
 *  SPDX-License-Identifier: MIT                                 *
 *                                                               *
 *****************************************************************/


#pragma once

#include "rtl_traits.h"

namespace rtl::access {
    class RObject;
}

namespace rtl::detail
{
    class RObjectBuilder
    {
        using Cloner = std::function<access::RObject(error&, const access::RObject&, rtl::alloc, rtl::entity)>;

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