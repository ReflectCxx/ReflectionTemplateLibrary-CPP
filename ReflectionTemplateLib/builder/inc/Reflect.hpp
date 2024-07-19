#pragma once

#include "Reflect.h"
#include "Builder.hpp"
#include "RecordBuilder.hpp"

namespace rtl {

    namespace builder 
    {
        inline Reflect::Reflect()
            : m_record("")
            //If no namespace is given, types are kept under defaultr namespace name: NAMESPACE_GLOBAL.
            , m_namespace(NAMESPACE_GLOBAL) {
        }

		
    /*  @function: record()
        @param: std::string, name of the 'namespace' as string.
        @return: 'this', Reflect.
		* used to group registered function, class/struct under namespace name.
        * its a logical grouping of registered types under a 'namespace' name.
        * optional- function, class/struct can be registered without given namespace name, even if they exists in one.
        * if types are registered with namespace name, then that name should be passed when retriving the objects from cxxMirror objects.
        * check functions CxxMirror::getMethod() & CxxMirror::getFunction().
    */  inline Reflect& Reflect::nameSpace(const std::string& pNamespace)
        {
            m_namespace = pNamespace;
            return *this;
        }


    /*  @function: method()
        @param: std::string, name of function as string.
        @return: Builder<TypeQ::None>
		* registers only non-member functions.
        * the 'build(..)' called on return object will accepts non-member function pointer only.
        * compiler error on 'build(..)' if member function pointer is passed.
    */  template<>
        inline const Builder<TypeQ::None> Reflect::function(const std::string& pFunction)
        {
            return Builder<TypeQ::None>(m_namespace, m_record, pFunction);
        }

		
    /*  @function: record()
        @param: std::string, name of class/struct as string.
        @return: RecordBuilder<_recordType>
		* provides object of 'RecordBuilder', which provides interface to registers member functions of class/struct of '_recordType'.
        * the 'build(..)' called on return object will accepts non-member function pointer only.
        * compiler error on 'build(..)' if function pointer passed is not a member of class/struct- '_recordType'.
    */  template<class _recordType>
        inline constexpr const RecordBuilder<_recordType> Reflect::record(const std::string& pClass)
        {
            return RecordBuilder<_recordType>(m_namespace, pClass);
        }

		
    /*  @method: function<...>()
        @param: std::string, name of function as string.
        @return: Builder<TypeQ::None, _signature...>
        * registers only non-member functions.
        * used for registering overloads, if unique member function, use non-templated version 'function()'.
        * template parameters must be explicitly specified, should be exactly same as the function being registered.
        * the 'build(..)' called on return object will accepts non-member function pointer only.
        * compiler error on 'build(..)' if any member function pointer is passed.
    */  template<class ..._signature>
        inline constexpr const Builder<TypeQ::None, _signature...> Reflect::function(const std::string& pFunction) 
        {
            return Builder<TypeQ::None, _signature...>(m_namespace, m_record, pFunction);
        }
    }
}