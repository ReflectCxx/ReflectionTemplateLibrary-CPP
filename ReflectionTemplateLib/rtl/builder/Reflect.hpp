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

#include "Reflect.h"
#include "Builder.hpp"
#include "RecordBuilder.hpp"

namespace rtl 
{
    inline type_ns::type_ns(const std::string& pNamespace)
        : m_recordStr("")
        , m_namespaceStr(pNamespace)
    { }

		
/*  @function: ns()
    @param: std::string, name of the 'namespace' as string.
    @return: '*this', Reflect.
    * used to group registered function, class/struct under a namespace name.
    * its an internal grouping of registered types under a 'namespace' name.
    * providing a namespace is optional. registration can be done without a namespace name, even if a type exists in one.
    * if types are registered with 'namespace' name, then it must be passed when retriving the objects from 'CxxMirror',
        check functions, CxxMirror::getFunction("name_space", "func_name") & CxxMirror::getRecord("name_space","class_name"),
        if no namespace is given, then CxxMirror::getFunction("func_name") & CxxMirror::getRecord("class_name")
*/  inline type_ns type::ns(const std::string& pNamespace)
    {
        return type_ns(pNamespace);
    }


/*  @function: function()
    @param: std::string (name of the function).
    @return: Builder<detail::member::None>
    * registers only non-member functions.
    * the 'build(..)' called on return object accepts non-member function pointer only.
    * compiler error on 'build(..)' if member function pointer is passed.
*/  template<>
    inline const builder::Builder<detail::member::None> type_ns::function(const std::string& pFunction)
    {
        return builder::Builder<detail::member::None>(traits::uid<>::none, pFunction, m_namespaceStr);
    }

		
/*  @function: record()
    @param: std::string (name of class/struct)
    @return: RecordBuilder<_recordType>
    * provides object of 'RecordBuilder', which provides interface to registers member functions of class/struct of '_recordType'.
    * the 'build(..)' called on return object accepts non-member function pointer only.
    * compiler error on 'build(..)' if function pointer passed is not a member of class/struct- '_recordType'.
*/  template<class _recordType>
    inline constexpr const builder::RecordBuilder<_recordType> type_ns::record(const std::string& pClass)
    {
        return builder::RecordBuilder<_recordType>(m_namespaceStr, pClass, traits::uid<_recordType>::value);
    }

		
/*  @method: function<...>()
    @param: std::string (name of function)
    @return: Builder<detail::member::None, _signature...>
    * registers only non-member functions.
    * used for registering overloads, if unique member function, use non-templated version 'function()'.
    * template parameters must be explicitly specified, should be exactly same as the function being registered.
    * the 'build(..)' called on return object accepts non-member function pointer only.
    * compiler error on 'build(..)' if any member function pointer is passed.
*/  template<class ..._signature>
    inline constexpr const builder::Builder<detail::member::None, _signature...> type_ns::function(const std::string& pFunction)
    {
        return builder::Builder<detail::member::None, _signature...>(traits::uid<>::none, pFunction, m_namespaceStr);
    }
}