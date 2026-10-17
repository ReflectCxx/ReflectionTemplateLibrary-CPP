/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#pragma once

#include <inc/RObject.h>

namespace rtl::detail
{
    template<class T>
    struct RObjectBuilder
    {
        RObjectBuilder() = delete;
        RObjectBuilder(const RObjectBuilder&) = delete;

        template <rtl::alloc _allocOn> requires (_allocOn == alloc::Heap)
        static RObject build(T&& pVal, traits::cloner_t pClonerFn, bool pIsConstCastSafe) noexcept;

        template <rtl::alloc _allocOn> requires (_allocOn == alloc::Stack)
        static RObject build(T&& pVal, traits::cloner_t pClonerFn, bool pIsConstCastSafe) noexcept;

        template <rtl::alloc _allocOn>
        static RObject build(T&& pVal, bool pIsConstCastSafe) noexcept;
    };
}


namespace rtl
{
    static inline std::size_t getRtlManagedHeapInstanceCount()
    {
        return RObject::getInstanceCounter();
    }

    template<class T, std::size_t N>
    static inline RObject reflect(T(&pArr)[N]) noexcept
    {
        if constexpr (std::is_same_v<traits::raw_t<T>, char>) {
            return detail::RObjectBuilder<std::string_view>::template
                    build<alloc::Stack>(std::string_view(pArr, N - 1), !traits::is_const_v<T>);
        }
        else {
            return detail::RObjectBuilder<std::vector<T>>::template
                    build<alloc::Stack>(std::vector(pArr, pArr + N), !traits::is_const_v<T>);
        }
    }

    template <class T>
    static inline RObject reflect(T&& pVal) noexcept
    {
        using _T = traits::raw_t<T>;
        if constexpr (traits::std_wrapper<_T>::type == detail::Wrapper::None)
        {
            return detail::RObjectBuilder<T>::template 
                build<alloc::Stack>(std::forward<T>(pVal), !traits::is_const_v<T>);
        }
        else
        {
            constexpr bool isConstCastSafe = !traits::is_const_v<typename traits::std_wrapper<_T>::value_type>;
            return detail::RObjectBuilder<T>::template
                build<alloc::Stack>(std::forward<T>(pVal), isConstCastSafe);
        }
    }
}