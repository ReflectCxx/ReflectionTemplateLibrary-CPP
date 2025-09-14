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

#include "Constants.h"
#include "FunctorRegistry.h"


namespace rtl::detail
{
    template<methodQ>
    struct functor_cache;
}

namespace rtl::detail
{
    template<>
    struct functor_cache<methodQ::None>
    {
        template<class return_t, class ...signature_ts>
        static functor_registry<return_t, signature_ts...>& get()
        {
            static functor_registry<return_t, signature_ts...> functors;
            return functors;
        }
    };

    template<>
    struct functor_cache<methodQ::Const>
    {
        template<class record_t, class return_t, class ...signature_ts>
        static functor_registry_m<methodQ::Const, record_t, return_t, signature_ts...>& get()
        {
            static functor_registry_m<methodQ::Const, record_t, return_t, signature_ts...> functors;
            return functors;
        }
    };

    template<>
    struct functor_cache<methodQ::NonConst>
    {
        template<class record_t, class return_t, class ...signature_ts>
        static functor_registry_m<methodQ::NonConst, record_t, return_t, signature_ts...>& get()
        {
            static functor_registry_m<methodQ::NonConst, record_t, return_t, signature_ts...> functors;
            return functors;
        }
    };
}