#pragma once

#include "ReflectionBuilder.h"
#include "FunctorContainer.h"
#include "MethodContainer.h"

namespace rtl {
	
    namespace detail
    {	
        inline ReflectionBuilder::ReflectionBuilder(const std::string& pNamespace, const std::string& pRecord,
                                                    const std::string& pFunction)
            : m_record(pRecord)
            , m_function(pFunction)
            , m_namespace(pNamespace) {
        }

    /*  @method: buildFunctor()
        @return: 'Function', object associated with the given functor.
        @param: 'pFunctor', function pointer with,
        *       '_returnType' & '_signature...'(auto deduced).
        * adds the function pointer in 'FunctorContainer'
        * accepts only a non-member or static-member function pointer.
        * builds the 'Function' object containing hash-key & meta-data for the given functor.
    */  template<class _returnType, class ..._signature>
        inline const access::Function ReflectionBuilder::buildFunctor(_returnType(*pFunctor)(_signature...)) const
        {
            const std::string& typeStr = detail::TypeId<_signature...>::toString();
            const detail::FunctorId functorId = detail::FunctorContainer<_signature...>::addFunctor(pFunctor);
            return access::Function(m_namespace, m_record, m_function, functorId, TypeId<>::None, TypeQ::None);
        }


    /*  @method: buildFunctor()
        @return: 'Function', object associated with the given functor.
        @param: 'pFunctor', function pointer with, '_recordType' (class/struct),
        *       '_returnType' & '_signature...'(auto deduced).
        * adds the function pointer in 'MethodContainer'
        * accepts only a non-static, non-const member function pointer.
        * builds the 'Function' object containing hash-key & meta-data for the given functor.
    */  template<class _recordType, class _returnType, class ..._signature>
        inline const access::Function ReflectionBuilder::buildMethodFunctor(_returnType(_recordType::* pFunctor)(_signature...)) const
        {
            const std::string& typeStr = detail::TypeId<_signature...>::toString();
            const detail::FunctorId functorId = detail::MethodContainer<TypeQ::Mute, _signature...>::addFunctor(pFunctor);
            return access::Function(m_namespace, m_record, m_function, functorId, TypeId<_recordType>::get(), TypeQ::Mute);
        }


    /*  @method: buildMethodFunctor()
        @return: 'Function', object associated with the given functor.
        @param: 'pFunctor', function pointer with, '_recordType' (class/struct),
        *       '_returnType' & '_signature...'(auto deduced).
        * adds the function pointer in 'MethodContainer'
        * accepts only a const member function pointer.
        * builds the 'Function' object containing hash-key & meta-data for the given functor.
    */  template<class _recordType, class _returnType, class ..._signature>
        inline const access::Function ReflectionBuilder::buildMethodFunctor(_returnType(_recordType::* pFunctor)(_signature...) const) const
        {
            const std::string& typeStr = detail::TypeId<_signature...>::toString();
            const detail::FunctorId functorId = detail::MethodContainer<TypeQ::Const, _signature...>::addFunctor(pFunctor);
            return access::Function(m_namespace, m_record, m_function, functorId, TypeId<_recordType>::get(), TypeQ::Const);
        }


    /*  @method: buildConstructor()
        @return: 'Function', object associated with the (specified parametrized) constructor.
        @param: '_recordType'(class/struct type) & '_ctorSignature...' (explicitly specified),
        * adds the lambda invoking constructor (type-erased) in 'FunctorContainer'
        * builds the 'Function' object containing hash-key & meta-data for the constructor.
        * also adds the lambda for invoking the destructor and returns its hash-key with the constructor's 'Function'.
    */  template<typename _recordType, class ..._ctorSignature>
        inline const access::Function ReflectionBuilder::buildConstructor() const
        {
            const detail::FunctorId functorId = detail::FunctorContainer<_ctorSignature...>::template addConstructor<_recordType, _ctorSignature...>();
            const std::string& typeStr = detail::TypeId<_ctorSignature...>::toString();
            const access::Function constructor = access::Function(m_namespace, m_record, m_function, functorId, TypeId<_recordType>::get(), TypeQ::None);
            //add the destructor's 'FunctorId' to the constructor's functorIds list.
            constructor.getFunctorIds().emplace_back(detail::FunctorContainer<std::any>::addDestructor<_recordType>());
            return constructor;
        }


    /*  @method: buildCopyConstructor()
        @return: 'Function', object associated with the copy constructor.
        @param: '_recordType'(class/struct type) & '_ctorSignature...' ('_recordType&', explicitlly specified internally),
        * adds the lambda invoking copy constructor (type-erased) in 'FunctorContainer'
        * builds the 'Function' object containing hash-key & meta-data for the copy constructor.
        * also adds the lambda for invoking the destructor and returns its hash-key with the constructor's 'Function'.
    */  template<class _recordType, class ..._ctorSignature>
        inline const access::Function ReflectionBuilder::buildCopyConstructor() const
        {
            const detail::FunctorId functorId = detail::FunctorContainer<std::any>::addCopyConstructor<_recordType>();
            const std::string& typeStr = detail::TypeId<_ctorSignature...>::toString();
            const access::Function constructor = access::Function(m_namespace, m_record, m_function, functorId, TypeId<_recordType>::get(), TypeQ::None);
            //add the destructor's 'FunctorId' to the constructor's functorIds list.
            constructor.getFunctorIds().emplace_back(detail::FunctorContainer<std::any>::addDestructor<_recordType>());
            return constructor;
        }
		
		
    /*  @method: buildConstCopyConstructor()
        @return: 'Function', object associated with the copy constructor.
        @param: '_recordType'(class/struct type) & '_ctorSignature...' ('const _recordType&', explicitlly specified internally),
        * adds the lambda invoking copy constructor (type-erased) taking const-ref in 'FunctorContainer'
        * builds the 'Function' object containing hash-key & meta-data for the const-copy constructor.
        * also adds the lambda for invoking the destructor and returns its hash-key with the constructor's 'Function'.
    */  template<class _recordType, class ..._ctorSignature>
        inline const access::Function ReflectionBuilder::buildConstCopyConstructor() const
        {
            const detail::FunctorId functorId = detail::FunctorContainer<std::any>::addConstCopyConstructor<_recordType>();
            const std::string& typeStr = detail::TypeId<_ctorSignature...>::toString();
            const access::Function constructor = access::Function(m_namespace, m_record, m_function, functorId, TypeId<_recordType>::get(), TypeQ::None);
            //add the destructor's 'FunctorId' to the constructor's functorIds list.
            constructor.getFunctorIds().emplace_back(detail::FunctorContainer<std::any>::addDestructor<_recordType>());
            return constructor;
        }
    }
}