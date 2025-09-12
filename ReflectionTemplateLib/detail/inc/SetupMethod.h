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

#include "FunctorId.h"

namespace rtl {

	namespace detail
	{
    /*  @struct: SetupMethod
        @param: _derivedType (type which inherits this class)
        * creates a lambda to perform call on the registered functor.
        * adds it to the functor-container, maintains the already added functor set as well.
        * deriving classes is MethodContainer<detail::methodQ::NonConst, _signature...> &
          MethodContainer<detail::methodQ::Const, _signature...>, which must implement -
            - std::size_t& _derived::getContainerId();
            - std::string _derivedType::getSignatureStr();
            - std::size_t& _derived::pushBack(std::function < RObject (error&, const rtl::RObject&, _signature...) >,
                                              std::function<const std::size_t()>,
                                              std::function<void(const std::size_t&)>);
        * sets up only non-static-member-function functors in lambda table.
        * called from 'ReflectionBuilder', as _derivedType member.
    */  template<class _derivedType>
        class SetupMethod
        {
            template<class ..._signature>
            using MethodLambda = std::function < Return(const rtl::RObject&, _signature...) >;

            template<class _recordType, class _returnType, class ..._signature>
            static MethodLambda<_signature...> getMethodCaller(_returnType(_recordType::* pFunctor)(_signature...));

            template<class _recordType, class _returnType, class ..._signature>
            static MethodLambda<_signature...> getMethodCaller(_returnType(_recordType::* pFunctor)(_signature...) const);

            template<class _recordType, class ..._signature>
            static MethodLambda<_signature...> getMethodCaller(void(_recordType::* pFunctor)(_signature...));

            template<class _recordType, class ..._signature>
            static MethodLambda<_signature...> getMethodCaller(void(_recordType::* pFunctor)(_signature...) const);
            
        protected:

            template<class _recordType, class _returnType, class ..._signature>
            static const detail::FunctorId addFunctor(_returnType(_recordType::* pFunctor)(_signature...));

            template<class _recordType, class _returnType, class ..._signature>
            static const detail::FunctorId addFunctor(_returnType(_recordType::* pFunctor)(_signature...) const);
        };
    }
}