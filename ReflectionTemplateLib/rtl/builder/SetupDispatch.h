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

#include <mutex>

#include "type_meta.h"

namespace rtl::detail 
{
    class SetupDispatch
    {
    protected:

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