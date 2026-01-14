/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#include <iostream>
#include <inc/Function.h>
#include <inc/type_meta.h>

namespace rtl 
{
/*  @constructor: Function()
    @params: pNamespace - given namespace while registering the type.
    *        pRecord - given class/struct name, empty if this 'Function' represents a non-member functor
    *        pFunction - given name of the function as string.
    *        pFunctorId - 'FunctorId', generated for every functor being registered.
    *        pRecordTypeId - type id of class/struct if the functor is member-function, '0' for non-member-functions.
    *        pQualifier - whether the member-function is const or non-const. member::None for non-member & static-member functions.
    * 'Function' object is created for every functor (member/non-member) being registered.
*/  Function::Function(const std::string& pNamespace, const std::string& pRecord,
                       const std::string& pFunction, const type_meta& pFunctorsMeta,
                       const traits::uid_t pRecordTypeId, const detail::member pQualifier)
        : m_member_kind(pQualifier)
        , m_recordTypeId(pRecordTypeId)
        , m_recordStr(pRecord)
        , m_function(pFunction)
        , m_namespaceStr(pNamespace)
        , m_functorsMeta({ pFunctorsMeta }) {
    }


/*  @method: addOverload()
    @param: 'Function' object
    * every 'Function' object produced while registration will have a single 'FunctorId' object, except constructors.
    * for overloads, registered with the same name, the 'FunctorId' from the 'pOtherFunc' object will be added to this.
    * if the same functor is registered again with the same name, it will be ignored.
*/	void Function::addOverload(const Function& pOtherFunc) const
    {
        const auto& otherFnMeta = pOtherFunc.m_functorsMeta.back();
        //simple linear-search, efficient for small set of elements.
        for (const auto& functorId : m_functorsMeta)
        {
            if (functorId.get_member_kind() == otherFnMeta.get_member_kind() &&
                functorId.get_strict_args_id() == otherFnMeta.get_strict_args_id()) {

                std::cout << "\n[WARNING] Multiple registrations of the same function-pointer detected."
                          << "\n          function-pointer already registered as \"" << m_function << "\""
                          << "\n          This registration is ignored.\n";

                return; //ignore and return since its already registered.
            }
        }
        //add the 'type_meta' of the overloaded functor.
        m_functorsMeta.push_back(pOtherFunc.m_functorsMeta.back());
    }
}