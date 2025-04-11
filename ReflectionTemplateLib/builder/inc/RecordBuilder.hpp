#pragma once

#include "RecordBuilder.h"
#include "ConstructorBuilder.hpp"

namespace rtl {

    namespace builder
    {
        template<class _recordType>
        inline RecordBuilder<_recordType>::RecordBuilder(const std::string& pNamespace, const std::string& pRecord)
            : m_record(pRecord)
            , m_namespace(pNamespace) {
        }


    /*  @method: methodStatic()
        @param: std::string, name of function as string.
        @return: Builder<TypeQ::None, _signature...>
        * registers only static member functions.
        * used for registering unique static member function, if overload exists, use templated version 'methodStatic<...>()'.
        * the 'build(..)' called on return object will accepts static member function pointer only.
        * compiler error on 'build(..)' if non-static member or non-member function pointer is passed.
    */  template<class _recordType>
        inline const Builder<TypeQ::None> RecordBuilder<_recordType>::methodStatic(const std::string& pFunction) const
        {
            return Builder<TypeQ::None>(m_namespace, m_record, pFunction);
        }


    /*  @method: methodStatic<...>()
        @param: std::string, name of function as string.
        @return: Builder<TypeQ::None, _signature...>
        * registers only static member functions.
        * used for registering overloads, if unique member function, use non-templated version 'methodStatic()'.
        * template parameters must be explicitly specified, should be exactly same as the member-function being registered.
        * the 'build(..)' called on return object will accepts static member function pointer only.
        * compiler error on 'build(..)' if const member or non-member function pointer is passed.
    */  template<class _recordType>
        template<class ..._signature>
        inline const Builder<TypeQ::None, _signature...> RecordBuilder<_recordType>::methodStatic(const std::string& pFunction) const
        {
            return Builder<TypeQ::None, _signature...>(m_namespace, m_record, pFunction);
        }


    /*  @method: method()
        @param: std::string, name of function as string.
        @return: Builder<TypeQ::Mute>
        * registers non-const, non-static member functions.
        * the 'build(..)' called on return object will accepts non-const, non-static member-function-pointer only.
        * compiler error on 'build(..)' if const, static member or non-member function pointer is passed.
    */  template<class _recordType>
        inline const Builder<TypeQ::Mute> RecordBuilder<_recordType>::method(const std::string& pFunction) const
        {
            return Builder<TypeQ::Mute>(m_namespace, m_record, pFunction);
        }


    /*  @method: methodConst()
        @param: std::string, name of function as string.
        @return: Builder<TypeQ::Const>
        * registers const member functions.
        * used for registering unique member function, if overload exists, use templated version 'methodConst<...>()'.
        * template parameters must be explicitly specified, should be exactly same as the member-function being registered.
        * the 'build(..)' called on return object will accepts non-const member-function-pointer only.
        * compiler error 'build(..)' if non-const, static member or non-member function pointer is passed.
    */  template<class _recordType>
        inline const Builder<TypeQ::Const> RecordBuilder<_recordType>::methodConst(const std::string& pFunction) const
        {
            return Builder<TypeQ::Const>(m_namespace, m_record, pFunction);
        }


    /*  @method: method()
        @param: std::string, name of function as string.
        @return: Builder<TypeQ::Mute, _signature...>
        * registers non-const member functions.
        * used for registering overloads, for unique member function, use non-templated version 'method()'.
        * template parameters must be explicitly specified, should be exactly same as the member-function being registered.
        * the 'build(..)' called on return object will accepts non-const member-function-pointer only.
        * compiler error on 'build(..)' if const, static member or non-member function pointer is passed.
    */  template<class _recordType>
        template<class ..._signature>
        inline const Builder<TypeQ::Mute, _signature...> RecordBuilder<_recordType>::method(const std::string& pFunction) const
        {
            return Builder<TypeQ::Mute, _signature...>(m_namespace, m_record, pFunction);
        }


    /*  @method: methodConst<...>()
        @param: std::string, name of function as string.
        @return: Builder<TypeQ::Const, _signature...>
        * registers const member functions.
        * used for registering overloads, for unique member function, use non-templated version 'methodConst()'.
        * template parameters must be explicitly specified, should be exactly same as the member-function being registered.
        * the 'build(..)' called on return object will accepts const member-function-pointer only.
        * compiler error on 'build(..)' if non-const, static member or non-member function pointer is passed.
    */  template<class _recordType>
        template<class ..._signature>
        inline const Builder<TypeQ::Const, _signature...> RecordBuilder<_recordType>::methodConst(const std::string& pFunction) const
        {
            return Builder<TypeQ::Const, _signature...>(m_namespace, m_record, pFunction);
        }


    /*  @method: constructor<...>()
        @param: none
        @return: ConstructorBuilder<_recordType, _signature...>
        * the copy constructors params are detected at compile time only.
        * template params <...> - any combination of parameters.
    */  template<class _recordType>
        template<class ..._signature>
        inline const ConstructorBuilder<_recordType, _signature...> RecordBuilder<_recordType>::constructor() const
        {
            //this code-block is retained by compiler, if copy constructor with non-const ref('_recordType&') is being registered.
            if constexpr (std::is_same_v<_recordType&, typename detail::TypeId<_signature...>::HEAD>) 
            {
                return ConstructorBuilder<_recordType, _signature...>(m_namespace, m_record, FunctorType::CopyCtor);
            }
            //this code-block is retained by compiler, if copy constructor with const-ref('const _recordType&') is being registered.
            else if constexpr (std::is_same_v<const _recordType&, typename detail::TypeId<_signature...>::HEAD>) 
            {
                return ConstructorBuilder<_recordType, _signature...>(m_namespace, m_record, FunctorType::CopyCtorConst);
            }
            //if any other constructor except, copy constructor is being registered, this code-block will be retained.
            else 
            {
                return ConstructorBuilder<_recordType, _signature...>(m_namespace, m_record, FunctorType::Ctor);
            }
        }
    }
}
