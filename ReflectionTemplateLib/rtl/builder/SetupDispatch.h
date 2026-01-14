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

#include <mutex>

#include <inc/type_meta.hpp>

namespace rtl::builder
{
    struct SetupDispatch
    {
        template<class ...>
        static type_meta init( std::function<type_meta()> isRegistered,
                               std::function<type_meta()> doRegister ) {

            static std::mutex mtx;
            std::lock_guard<std::mutex> lock(mtx);

            auto typeMeta = isRegistered();
            if (typeMeta.is_empty()) {
                return doRegister();
            }
            return typeMeta;
        }
    };
}