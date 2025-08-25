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

#include "Constants.h"

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
            const std::string_view m_record;

            //given name of the namespace.
            const std::string_view m_namespace;

        public:

            ConstructorBuilder()
                : m_record("")
                , m_namespace("")
            { }

            ConstructorBuilder(const std::string_view pNamespace, const std::string_view pRecord)
                : m_record(pRecord)
                , m_namespace(pNamespace)
            { }

        /*  @method: build()
            @param: none
            @return: 'Function' object.
            * constructs temparory object of class Builder<methodQ::NonConst> with given class/struct, namespace name & constructor type.
            * forwards the call to Builder<methodQ::NonConst>::build().
        */  const Function build() const
            {
                // Check if the constructor is not deleted and publicly accessible (excluding default constructor).
                const bool isAccessible = (sizeof...(_ctorSignature) == 0 || std::is_constructible_v<_recordType, _ctorSignature...>);
                static_assert(isAccessible, "The specified constructor is either deleted or not publicly accessible.");

                return CtorBuilder(m_namespace, m_record, std::string_view(detail::ctor_name(m_record)),
                                   detail::TypeId<_recordType>::get()).build<_recordType, _ctorSignature...>();
            }
        };
    }
}