#pragma once

#include "ReflectionBuilder.h"
#include "FunctorContainer.h"
#include "MethodContainer.h"
#include "SetupMethod.hpp"
#include "SetupFunction.hpp"
#include "SetupConstructor.hpp"

namespace rtl {
	
    namespace detail
    {	
        inline ReflectionBuilder::ReflectionBuilder(const std::string& pNamespace, const std::string& pRecord,
                                                    const std::string& pFunction, std::size_t pRecordId)
            : m_record(pRecord)
            , m_function(pFunction)
            , m_namespace(pNamespace)
            , m_recordId(pRecordId){
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
            using Container = FunctorContainer< remove_const_if_not_reference<_signature>...>;
            const FunctorId& functorId = Container::template addFunctor<_returnType, _signature...>(pFunctor, m_recordId);
            return access::Function(m_namespace, m_record, m_function, functorId, m_recordId, methodQ::None);
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
            using Container = MethodContainer<methodQ::NonConst, remove_const_if_not_reference<_signature>...>;
            const FunctorId& functorId = Container::template addFunctor<_recordType, _returnType, _signature...>(pFunctor);
            return access::Function(m_namespace, m_record, m_function, functorId, m_recordId, methodQ::NonConst);
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
            using Container = MethodContainer<methodQ::Const, remove_const_if_not_reference<_signature>...>;
            const FunctorId& functorId = Container::template addFunctor<_recordType, _returnType, _signature...>(pFunctor);
            return access::Function(m_namespace, m_record, m_function, functorId, m_recordId, methodQ::Const);
        }


    /*  @method: buildConstructor()
        @return: 'Function', object associated with the (specified parametrized) constructor.
        @param: '_recordType'(class/struct type) & '_ctorSignature...' (explicitly specified),
        * adds the lambda invoking constructor (type-erased) in 'FunctorContainer'
        * builds the 'Function' object containing hash-key & meta-data for the constructor.
    */  template<typename _recordType, class ..._ctorSignature>
        inline const access::Function ReflectionBuilder::buildConstructor() const
        {
            using Container = FunctorContainer<rtl::alloc, remove_const_if_not_reference<_ctorSignature>...>;
            const FunctorId& functorId = Container::template addConstructor<_recordType, _ctorSignature...>();
            const access::Function& constructor = access::Function(m_namespace, m_record, m_function, functorId, m_recordId, methodQ::None);
            //if the _recordType has valid copy constructor.
            if constexpr (std::is_copy_constructible_v<_recordType>) {
                //Construct and push the copy constructor's functorId at pos 1, it will be accessed using FunctorIdx::ONE.
                const FunctorId& copyCtorFunctorId = FunctorContainer<access::RObject&>::template addCopyConstructor<_recordType>();
                constructor.getFunctorIds().emplace_back(copyCtorFunctorId);
            }

            return constructor;
        }
    }
}
