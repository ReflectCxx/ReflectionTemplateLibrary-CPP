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

#include <any>
#include "rtl_forward_decls.h"

namespace rtl::erase
{
    template<class ...signature_ts>
    struct erasure_base
    {
        virtual void hop_v(signature_ts&&...) const noexcept = 0;
        virtual std::any hop_r(signature_ts&&...) const noexcept = 0;
    };
}