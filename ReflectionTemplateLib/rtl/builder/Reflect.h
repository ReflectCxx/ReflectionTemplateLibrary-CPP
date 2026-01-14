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

#include <builder/RecordBuilder.h>

namespace rtl
{
/*  @class: Reflect
    * provides interface to register all kinds of functions (member/non-member).
*/  struct type_ns
    {
        type_ns() = delete;
        type_ns(type_ns&&) = delete;
        type_ns(const type_ns&) = delete;
        type_ns& operator=(type_ns&&) = delete;
        type_ns& operator=(const type_ns&) = delete;

        type_ns(const std::string& pNamespace) 
            : m_recordStr("")
            , m_namespaceStr(pNamespace)
        { }

    /*  @function: record()
        @param: std::string (name of class/struct)
        @return: RecordBuilder<record_t>
        * provides object of 'RecordBuilder', which provides interface to registers member functions of class/struct of 'record_t'.
        * the 'build(..)' called on return object accepts non-member function pointer only.
        * compiler error on 'build(..)' if function pointer passed is not a member of class/struct- 'record_t'.
    */  template<class record_t>
        constexpr const builder::RecordBuilder<record_t> record(const std::string& pClass)
        {
            return builder::RecordBuilder<record_t>(m_namespaceStr, pClass, traits::uid<record_t>::value);
        }

    /*  @method: function<...>()
        @param: std::string (name of function)
        @return: Builder<detail::member::None, signature_t...>
        * registers only non-member functions.
        * used for registering overloads, if unique member function, use non-templated version 'function()'.
        * template parameters must be explicitly specified, should be exactly same as the function being registered.
        * the 'build(..)' called on return object accepts non-member function pointer only.
        * compiler error on 'build(..)' if any member function pointer is passed.
    */  template<class ...signature_t>
        constexpr const builder::Builder<detail::member::None, signature_t...> function(const std::string& pFunction)
        {
            return builder::Builder<detail::member::None, signature_t...>(traits::uid<>::none, pFunction, m_namespaceStr);
        }

    /*  @function: function()
        @param: std::string (name of the function).
        @return: Builder<detail::member::None>
        * registers only non-member functions.
        * the 'build(..)' called on return object accepts non-member function pointer only.
        * compiler error on 'build(..)' if member function pointer is passed.
    */  const builder::Builder<detail::member::None> function(const std::string& pFunction)
        {
            return builder::Builder<detail::member::None>(traits::uid<>::none, pFunction, m_namespaceStr);
        }

    private:

        //name of the class, struct being registered.
        std::string m_recordStr;

        //name of the namespace being registered.
        std::string m_namespaceStr;
    };



/*  @class: Reflect
    * provides interface to register all kinds of functions (member/non-member).
*/  struct type
    {
        type() = default;
        type(type&&) = delete;
        type(const type&) = delete;
        type& operator=(type&&) = delete;
        type& operator=(const type&) = delete;

    /*  @function: ns()
        @param: std::string, name of the 'namespace' as string.
        @return: '*this', Reflect.
        * used to group registered function, class/struct under a namespace name.
        * its an internal grouping of registered types under a 'namespace' name.
        * providing a namespace is optional. registration can be done without a namespace name, even if a type exists in one.
        * if types are registered with 'namespace' name, then it must be passed when retriving the objects from 'CxxMirror',
            check functions, CxxMirror::getFunction("name_space", "func_name") & CxxMirror::getRecord("name_space","class_name"),
            if no namespace is given, then CxxMirror::getFunction("func_name") & CxxMirror::getRecord("class_name")
    */  type_ns ns(const std::string& pNamespace)
        {
            return type_ns(pNamespace);
        }

        template<class record_t>
        constexpr const builder::MethodBuilder<record_t> member() 
        {
            return builder::MethodBuilder<record_t>();
        }

        template<class record_t>
        constexpr const builder::RecordBuilder<record_t> record(const std::string& pClass) 
        {
            return ns(detail::NAMESPACE_GLOBAL).record<record_t>(pClass);
        }

        template<class ...signature_t>
        constexpr const builder::Builder<detail::member::None, signature_t...> function(const std::string& pFunction) 
        {
            constexpr bool hasConstRValueRef = ((std::is_const_v<std::remove_reference_t<signature_t>> && std::is_rvalue_reference_v<signature_t>) || ...);
            static_assert(!hasConstRValueRef, "Registration of functions with 'const T&&' parameters is not allowed.");

            return ns(detail::NAMESPACE_GLOBAL).function<signature_t...>(pFunction);
        }
    };
}