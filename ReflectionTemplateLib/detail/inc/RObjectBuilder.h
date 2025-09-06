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

#include "rtl_traits.h"

namespace rtl {
    class RObject;
    struct Return;
}

namespace rtl::detail
{
    class RObjectBuilder
    {
        using Cloner = std::function< Return(const RObject&, rtl::alloc) >;

        template <class T>
        static const Cloner& buildCloner();

        template <class T>
        static const std::vector<traits::ConverterPair>& getConverters();

    public:

        RObjectBuilder() = delete;
        RObjectBuilder(const RObjectBuilder&) = delete;

        static const std::size_t rtlManagedInstanceCount();

        template <class T, rtl::alloc _allocOn, bool _isConstCastSafe>
        static RObject build(T&& pVal);
    };
}


namespace rtl
{
    inline const std::size_t getRtlManagedHeapInstanceCount()
    {
        return detail::RObjectBuilder::rtlManagedInstanceCount();
    }


    template<class T, std::size_t N>
    inline RObject reflect(T(&pArr)[N])
    {
        if constexpr (std::is_same_v<traits::raw_t<T>, char>) {
            return detail::RObjectBuilder::build<std::string_view, alloc::Stack, !traits::is_const_v<T>>(std::string_view(pArr, N - 1));
        }
        else {
            return detail::RObjectBuilder::build<std::vector<T>, alloc::Stack, !traits::is_const_v<T>>(std::vector(pArr, pArr + N));
        }
    }


    template <class T>
    inline RObject reflect(T&& pVal)
    {
        using _T = traits::raw_t<T>;
        if constexpr (traits::std_wrapper<_T>::type == detail::Wrapper::None)
        {
            return detail::RObjectBuilder::build<T, alloc::Stack, !traits::is_const_v<T>>(std::forward<T>(pVal));
        }
        else
        {
            constexpr bool isConstCastSafe = !traits::is_const_v<typename traits::std_wrapper<_T>::value_type>;
            return detail::RObjectBuilder::build<T, alloc::Stack, isConstCastSafe>(std::forward<T>(pVal));
        }
    }
}