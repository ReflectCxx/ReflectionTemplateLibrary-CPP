#pragma once

#include "Reflect.h"
#include "Builder.hpp"
#include "RecordBuilder.hpp"

namespace rtl {

    namespace builder
    {
        inline Reflect::Reflect()
            : m_record("")
            //If no namespace is given, types are kept under default name: NAMESPACE_GLOBAL.
            , m_namespace(NAMESPACE_GLOBAL) {
        }

		
    /*  @function: nameSpace()
        @param: std::string, name of the 'namespace' as string.
        @return: '*this', Reflect.
        * used to group registered function, class/struct under a namespace name.
        * its an internal grouping of registered types under a 'namespace' name.
        * providing a namespace is optional. registration can be done without a namespace name, even if a type exists in one.
        * if types are registered with 'namespace' name, then it must be passed when retriving the objects from 'CxxMirror',
          check functions, CxxMirror::getFunction("name_space", "func_name") & CxxMirror::getRecord("name_space","class_name"),
          if no namespace is given, then CxxMirror::getFunction("func_name") & CxxMirror::getRecord("class_name")
    */  inline Reflect& Reflect::nameSpace(const std::string& pNamespace)
        {
            m_namespace = pNamespace;
            return *this;
        }


    /*  @function: function()
        @param: std::string (name of the function).
        @return: Builder<TypeQ::None>
        * registers only non-member functions.
        * the 'build(..)' called on return object accepts non-member function pointer only.
        * compiler error on 'build(..)' if member function pointer is passed.
    */  template<>
        inline const Builder<TypeQ::None> Reflect::function(const std::string& pFunction)
        {
            return Builder<TypeQ::None>(m_namespace, m_record, pFunction);
        }

		
    /*  @function: record()
        @param: std::string (name of class/struct)
        @return: RecordBuilder<_recordType>
        * provides object of 'RecordBuilder', which provides interface to registers member functions of class/struct of '_recordType'.
        * the 'build(..)' called on return object accepts non-member function pointer only.
        * compiler error on 'build(..)' if function pointer passed is not a member of class/struct- '_recordType'.
    */  template<class _recordType>
        inline constexpr const RecordBuilder<_recordType> Reflect::record(const std::string& pClass)
        {
            return RecordBuilder<_recordType>(m_namespace, pClass);
        }

		
    /*  @method: function<...>()
        @param: std::string (name of function)
        @return: Builder<TypeQ::None, _signature...>
        * registers only non-member functions.
        * used for registering overloads, if unique member function, use non-templated version 'function()'.
        * template parameters must be explicitly specified, should be exactly same as the function being registered.
        * the 'build(..)' called on return object accepts non-member function pointer only.
        * compiler error on 'build(..)' if any member function pointer is passed.
    */  template<class ..._signature>
        inline constexpr const Builder<TypeQ::None, _signature...> Reflect::function(const std::string& pFunction) 
        {
            return Builder<TypeQ::None, _signature...>(m_namespace, m_record, pFunction);
        }
    }
}