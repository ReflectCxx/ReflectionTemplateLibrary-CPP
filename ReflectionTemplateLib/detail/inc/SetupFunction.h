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
    /*  @struct: SetupFunction
        @param: _derivedType (type which inherits this class)
        * creates a functor-wrapped-lambda to perform call on the registered functor.
        * adds it to the functor-container, maintains the already added functor set as well.
        * deriving classes is FunctorContainer<...>, which must implement -
            - std::size_t& _derived::getContainerId();
            - std::string _derivedType::getSignatureStr();
            - std::size_t& _derived::pushBack(std::function<RObject(error&, _signature...)>,
                                              std::function<const std::size_t()>,
                                              std::function<void(const std::size_t&)>);
        * sets up only non-member or static-member-function functors in table.
        * called from 'ReflectionBuilder', as _derivedType member.
    */  template<class _derivedType>
        class SetupFunction
        {
            template<class ..._signature>
            using FunctionLambda = std::function < Return(_signature...) >;

            template<class _returnType, class ..._signature>
            static FunctionLambda<_signature...> getCaller(_returnType(*pFunctor)(_signature...));

        protected:

            template<class _returnType, class ..._signature>
            static const detail::FunctorId addFunctor(_returnType(*pFunctor)(_signature...), std::size_t pRecordId);
        };
    }
}