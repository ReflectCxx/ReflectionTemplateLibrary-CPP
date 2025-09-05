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
    /*  @struct: SetupConstructor
        @param: _derivedType ('FunctorContainer')
        * creates a constructor-call-wrapped-lambda to perform constructor call.
        * adds it to the functor-container, maintains the already added constructor set as well.
        * called from 'ReflectionBuilder', as _derivedType member.
    */  template<class _derivedType>
        class SetupConstructor
        {	
            template<class ..._signature>
            using CtorLambda = std::function < Return(alloc, _signature...) >;

            template<class _recordType, class ..._signature>
            static CtorLambda<_signature...> getConstructorCaller();

        protected:

            //adds the lambda, wrapping constructor call, recordType(_signature...), to '_derivedType' (FunctorContainer)
            template<class _recordType, class ..._signature>
            static const detail::FunctorId addConstructor();
        };
    }
}