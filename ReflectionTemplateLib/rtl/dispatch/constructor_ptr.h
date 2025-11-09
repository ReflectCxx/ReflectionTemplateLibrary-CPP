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
	struct constructor_ptr
	{
		template<class ...args_t>
		static rtl::RObject create(args_t...params)
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
                            RObjectBuilder<record_t>::template
                            build<alloc::Stack>(record_t(std::forward<_signature>(params)...), pClonerId, true)
                        };
                    }
                }
                else if (pAllocType == alloc::Heap)
                {
                    return {
                        error::None,
                        RObjectBuilder<record_t*>::template
                        build<alloc::Heap>(new record_t(std::forward<_signature>(params)...), pClonerId, true)
                    };
                }
            }
            return { error::EmptyRObject, RObject{} };   //dead code. compiler warning omitted.
		}
	};
}