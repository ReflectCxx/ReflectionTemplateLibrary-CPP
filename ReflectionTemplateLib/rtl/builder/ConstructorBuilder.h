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

#include "rtl_constants.h"

namespace rtl {

    namespace builder 
    {
    /*  @class: ConstructorBuilder
        @param: _recordType - struct/class type. 
        *       _signature...- constructor args type (none/_record&/const _record& or any combination of parameters) 
        * provides interface to register constructors of a class/struct.
        * when the very first constructor(any- default/parametrized) is registered, copy-constructor gets registered implicitly.
        * all the objects are created via reflection are on heap, using 'new'.
        * the constructed objects are returned wrapped in 'Instance' object, with type erased.
        * lifetime of created objects are managed using 'shared_ptr'.
    */  template<class _recordType, class ..._ctorSignature>
        struct ConstructorBuilder
        {
            //given name of the class/struct.
            const std::string m_recordStr;

            //given name of the namespace.
            const std::string m_namespaceStr;

        public:

            ConstructorBuilder()
                : m_recordStr("")
                , m_namespaceStr("")
            { }

            ConstructorBuilder(const std::string& pNamespace, const std::string& pRecord)
                : m_recordStr(pRecord)
                , m_namespaceStr(pNamespace)
            { }

        /*  @method: build()
            @param: none
            @return: 'Function' object.
            * constructs temparory object of class Builder<detail::member::NonConst> with given class/struct, namespace name & constructor type.
            * forwards the call to Builder<detail::member::NonConst>::build().
        */  const Function build() const
            {
                // Check if the constructor is not deleted and publicly accessible (excluding default constructor).
                const bool isAccessible = (sizeof...(_ctorSignature) == 0 || std::is_constructible_v<_recordType, _ctorSignature...>);
                static_assert(isAccessible, "The specified constructor is either deleted or not publicly accessible.");

                return CtorBuilder( m_namespaceStr, m_recordStr,
                                    std::string(detail::ctor_name(m_recordStr)),
                                    traits::uid<_recordType>::value ).build<_recordType, _ctorSignature...>();
            }
        };
    }
}