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

#include "rtl_errors.h"
#include "RObjectBuilder.hpp"

namespace rtl::dispatch
{
	template<class record_t>
	struct aware_constructor
	{
		template<class ...args_t>
		static Return allocator(const detail::FunctorId& pFunctorId, alloc pAllocType, const detail::FunctorId& pClonerId, args_t...params)
		{
            if constexpr (sizeof...(args_t) == 0 && !std::is_default_constructible_v<record_t>)
            {   //default constructor, private or deleted.
                return { error::TypeNotDefaultConstructible, RObject{} };
            }
            else
            {
                if (pAllocType == alloc::Stack) {

                    if constexpr (!std::is_copy_constructible_v<record_t>)
                    {
                        return {
                            error::TypeNotCopyConstructible, RObject{}
                        };
                    }
                    else
                    {
                        return {
                            error::None,
                            detail::RObjectBuilder<record_t>::template build<alloc::Stack>(
                                record_t(std::forward<args_t>(params)...), pClonerId, true
                            )
                        };
                    }
                }
                else if (pAllocType == alloc::Heap)
                {
                    return {
                        error::None,
                        detail::RObjectBuilder<record_t*>::template build<alloc::Heap>(
                            new record_t(std::forward<args_t>(params)...), pClonerId, true
                        )
                    };
                }
            }
            return { error::EmptyRObject, RObject{} };   //dead code. compiler warning omitted.
		}


        static Return cloner(const detail::FunctorId& pFunctorId, const RObject& pOther, alloc pAllocOn)
        {
            if constexpr (std::is_copy_constructible_v<record_t>)
            {
                return [](const detail::FunctorId& pFunctorId, const RObject& pOther, alloc pAllocOn) -> Return
                {
                    const auto& srcObj = pOther.view<record_t>()->get();
                    switch (pAllocOn)
                    {
                    case alloc::Stack:
                        return {
                            error::None,
                            detail::RObjectBuilder<record_t>::template build<alloc::Stack>(
                                record_t(srcObj), pFunctorId, true
                            )
                        };
                    case alloc::Heap:
                        return {
                            error::None,
                            detail::RObjectBuilder<record_t*>::template build<alloc::Heap>(
                                new record_t(srcObj), pFunctorId, true
                            )
                        };
                    default:
                        return {
                            error::EmptyRObject,
                            RObject{}
                        };
                    }
                };
            }
            else
            {
                return [](const detail::FunctorId& pFunctorId, const RObject& pOther, alloc pAllocOn) -> Return
                {
                    return {
                        error::TypeNotCopyConstructible,
                        RObject{}
                    };
                };
            }
        }
	};
}