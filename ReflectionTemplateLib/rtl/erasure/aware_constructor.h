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

#include "RObject.h"
#include "rtl_errors.h"
#include "erase_constructor.h"

#include "RObjectBuilder.hpp"

namespace rtl::dispatch
{
	template<class record_t, class ...signature_t>
	struct aware_constructor : public erase_constructor<traits::normal_sign_t<signature_t>...>
	{
        using this_t = aware_constructor;
        using base_t = erase_constructor<traits::normal_sign_t<signature_t>...>;

        aware_constructor(): base_t(this_t::get_allocator())
        { }

        template<class ...args_t>
		static Return get_allocator()
		{
            return [](alloc p_alloc_on, args_t...params)-> Return
            {
                if (p_alloc_on == alloc::Stack)
                {
                    if constexpr (std::is_copy_constructible_v<record_t>)
                    {
                        return {
                            error::None,
                            detail::RObjectBuilder<record_t>::template build<alloc::Stack>(
                                record_t(std::forward<args_t>(params)...), &aware_constructor<record_t>::cloner, true
                            )
                        };
                    }
                }
                else if (p_alloc_on == alloc::Heap)
                {
                    return {
                        error::None,
                        detail::RObjectBuilder<record_t*>::template build<alloc::Heap>(
                            new record_t(std::forward<args_t>(params)...), &aware_constructor<record_t>::cloner, true
                        )
                    };
                }
                return { error::EmptyRObject, RObject{} };   //dead code. compiler warning omitted.
            };
		}


        static Return allocator(alloc p_alloc_on)
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
                            detail::RObjectBuilder<record_t>::template build<alloc::Stack>(
                                record_t(), &aware_constructor<record_t>::cloner, true
                            )
                        };
                    }
                    else return { error::TypeNotCopyConstructible, RObject{} };
                case alloc::Heap:
                    return {
                        error::None,
                        detail::RObjectBuilder<record_t*>::template build<alloc::Heap>(
                            new record_t(), &aware_constructor<record_t>::cloner, true
                        )
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


        static Return cloner(alloc p_alloc_on, const RObject& p_other)
        {
            if constexpr (std::is_copy_constructible_v<record_t>)
            {
                const auto& srcObj = p_other.view<record_t>()->get();
                switch (p_alloc_on)
                {
                case alloc::Stack:
                    return {
                        error::None,
                        detail::RObjectBuilder<record_t>::template build<alloc::Stack>(
                            record_t(srcObj), &aware_constructor<record_t>::cloner, true
                        )
                    };
                case alloc::Heap:
                    return {
                        error::None,
                        detail::RObjectBuilder<record_t*>::template build<alloc::Heap>(
                            new record_t(srcObj), &aware_constructor<record_t>::cloner, true
                        )
                    };
                default:
                    return { error::EmptyRObject, RObject{} };
                }
            }
            else
            {
                return { error::TypeNotCopyConstructible, RObject{} };
            }
        }
	};
}