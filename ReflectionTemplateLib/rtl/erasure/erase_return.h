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


#include "erasure.h"
#include "rtl_traits.h"
#include "rtl_function.h"
#include "RObjectBuilder.hpp"

namespace rtl::erase
{
     template<class return_t, class ...signature_ts>
     struct function_return : public erasure_base<signature_ts...>
     {
         rtl::function<return_t(signature_ts...)> m_function;

         Return forward(signature_ts&&...params) override
         {
             if constexpr (std::is_void_v<return_t>)
             {
                 m_function(std::forward<signature_ts>(params)...);
                 return { error::None, RObject{} };
             }
             else
             {
                 constexpr bool isConstCastSafe = (!traits::is_const_v<return_t>);

                 if constexpr (std::is_reference_v<return_t>) {

                     auto& retObj = m_function(std::forward<signature_ts>(params)...);

                     using T = std::remove_cvref_t<decltype(retObj)>;
                     return Return {
                         error::None,
                         detail::RObjectBuilder<const T*>::template
                                 build<rtl::alloc::Stack>(&retObj, std::nullopt, isConstCastSafe)
                     };
                 }
                 else
                 {
                     auto&& retObj = fptr(std::forward<signature_ts>(params)...);

                     using T = std::remove_cvref_t<decltype(retObj)>;
                     return Return {
                         error::None,
                         detail::RObjectBuilder<const T>::template
                                 build<rtl::alloc::Stack>(std::forward<decltype(retObj)>(retObj), std::nullopt, isConstCastSafe)
                     };
                 }
             }
             return Return{ error::None, RObject{} };
         }
     };
 }