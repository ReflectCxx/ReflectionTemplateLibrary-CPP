/*************************************************************************
 *                                                                       *
 *  Reflection Template Library (RTL) - Modern C++ Reflection Framework  *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP          *
 *                                                                       *
 *  Copyright (c) 2025 Neeraj Singh <reflectcxx@outlook.com>             *
 *  SPDX-License-Identifier: MIT                                          *
 *                                                                       *
 *************************************************************************/


#pragma once


 #include "RObject.h"
 #include "rtl_traits.h"
 #include "rtl_forward_decls.h"

 namespace rtl::erase
 {
     template<class ...signature_ts>
     struct erasure_base
     {
         virtual Return forward(signature_ts&&...) = 0;
     };

     template<class return_t, class ...signature_ts>
     struct function_return : public erasure_base<signature_ts...>
     {
         Return forward(signature_ts&&...) override
         {
             return Return{ error::None, RObject{ return_t() } };
         }
     };
 }