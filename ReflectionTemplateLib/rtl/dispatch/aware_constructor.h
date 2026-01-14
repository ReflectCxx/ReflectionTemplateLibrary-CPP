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

#include <detail/inc/RObjectBuilder.hpp>

namespace rtl::dispatch
{
    template<class record_t, class ...signature_t>
    struct aware_constructor
    {
        static Return overloaded_ctor(alloc p_alloc_on, traits::normal_sign_t<signature_t>&&...params)
        {
            if (p_alloc_on == alloc::Stack)
            {
                if constexpr (std::is_copy_constructible_v<record_t>)
                {
                    return {
                        error::None,
                        detail::RObjectBuilder<record_t>::template 
                        build<alloc::Stack>(record_t(std::forward<signature_t>(params)...), true)
                    };
                }
            }
            else if (p_alloc_on == alloc::Heap)
            {
                return {
                    error::None,
                    detail::RObjectBuilder<record_t*>::template
                    build<alloc::Heap>(new record_t(std::forward<signature_t>(params)...), true)
                };
            }
            return { error::EmptyRObject, RObject{} };   //dead code. compiler warning omitted.
        }


        static Return default_ctor(alloc p_alloc_on)
        {
            if constexpr (std::is_default_constructible_v<record_t>)
            {
                switch (p_alloc_on)
                {
                case alloc::Stack:
                    if constexpr (std::is_copy_constructible_v<record_t>)
                    {
                        return {
                            error::None,
                            detail::RObjectBuilder<record_t>::template 
                            build<alloc::Stack>(record_t(), true)
                        };
                    }
                    else return { error::TypeNotCopyConstructible, RObject{} };
                case alloc::Heap:
                    return {
                        error::None,
                        detail::RObjectBuilder<record_t*>::template 
                        build<alloc::Heap>(new record_t(), true)
                    };
                default:
                    return { error::EmptyRObject, RObject{} };
                }
            }
            else 
            {
                return { error::TypeNotDefaultConstructible, RObject{} };
            }
        }
	};
}