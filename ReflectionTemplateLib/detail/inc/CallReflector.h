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

#include <optional>
#include "RObject.h"
#include "Constants.h"

namespace rtl::detail {


/*  @struct: CallReflector
    @param: _derivedType (type which inherits this class)
    * retrieves the lambda at given index and calls it with the arguments supplied.
    * deriving classes are, MethodContainer & FunctorContainer.
*/  template<class _derivedType>
    struct CallReflector
    {
    /*  @method: forwardCall
        @param: pFunctorIndex (index of the lambda), _args...(arguments to be passed to that lambda)
        * gets the lambda vector from '_derivedType' and calls the lambda at given index with '_args'.
        * this 'forwardCall' is for calling lambda containing non-member-function and static-member-function functors.
    */  template<class ..._params>
        static Return forwardCall(std::size_t pFunctorIndex, _params&&..._args)
        {
            //'getFunctors()' must be implemented by _derivedType (FunctorContainer).
            return _derivedType::getFunctors().at(pFunctorIndex)(std::forward<_params>(_args)...);
        }


    /*  @method: forwardCall
        @param: pFunctorIndex (index of the lambda), _args...(arguments to be passed to that lambda)
        * gets the lambda vector from '_derivedType' and calls the lambda at given index with '_args'.
        * this 'forwardCall' is for calling lambda containing constructors.
    */  template<class ..._params>
        static Return forwardCall(std::size_t pFunctorIndex, rtl::alloc pAllocType, std::size_t pClonerIndex, _params&&..._args)
        {
            //'getFunctors()' must be implemented by _derivedType (FunctorContainer).
            return _derivedType::getFunctors().at(pFunctorIndex)(pAllocType, pClonerIndex, std::forward<_params>(_args)...);
        }


    /*  @method: forwardCall
        @param: pFunctorIndex (index of the lambda), _args...(arguments to be passed to that lambda)
        * gets the lambda vector from '_derivedType' and calls the lambda at given index with '_args'.
        * this 'forwardCall' is for calling lambda containing member-function functors.
    */  template<class ..._params>
        static Return forwardCall(const rtl::RObject& pTarget, std::size_t pFunctorIndex, _params&&..._args)
        {
            //'getMethodFunctors()' is implemented by _derivedType (MethodContainer)
            return _derivedType::getMethodFunctors().at(pFunctorIndex)(pTarget, std::forward<_params>(_args)...);
        }
    };
}