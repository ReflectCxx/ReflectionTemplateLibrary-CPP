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
#include "rtl_constants.h"
#include "FunctorId.h"

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
        FORCE_INLINE static Return forwardCall(const detail::FunctorId& pFunctorId, _params&&..._args)
        {
            //'getOverloads()' must be implemented by _derivedType (FunctorContainer).
            return _derivedType::getOverloads()[pFunctorId.m_lambdaIndex](pFunctorId, std::forward<_params>(_args)...);
        }


    /*  @method: forwardCall
        @param: pFunctorIndex (index of the lambda), _args...(arguments to be passed to that lambda)
        * gets the lambda vector from '_derivedType' and calls the lambda at given index with '_args'.
        * this 'forwardCall' is for calling lambda containing constructors.
    */  template<class ..._params>
        FORCE_INLINE static Return forwardCall(const detail::FunctorId& pFunctorId, rtl::alloc pAllocType, const detail::FunctorId& pClonerId, _params&&..._args)
        {
            //'getOverloads()' must be implemented by _derivedType (FunctorContainer).
            return _derivedType::getOverloads()[pFunctorId.m_lambdaIndex](pFunctorId, pAllocType, pClonerId, std::forward<_params>(_args)...);
        }


        template<class ..._params>
        FORCE_INLINE static Return forwardCall(const detail::FunctorId& pFunctorId, const RObject& pSrcObj, rtl::alloc pAllocType)
        {
            //'getOverloads()' must be implemented by _derivedType (FunctorContainer).
            return _derivedType::getOverloads()[pFunctorId.m_lambdaIndex](pFunctorId, pSrcObj, pAllocType);
        }


    /*  @method: forwardCall
        @param: pFunctorIndex (index of the lambda), _args...(arguments to be passed to that lambda)
        * gets the lambda vector from '_derivedType' and calls the lambda at given index with '_args'.
        * this 'forwardCall' is for calling lambda containing member-function functors.
    */  template<class ..._params>
        FORCE_INLINE static Return forwardCall(const detail::FunctorId& pFunctorId, const rtl::RObject& pTarget, _params&&..._args)
        {
            //'getMethodFunctors()' is implemented by _derivedType (MethodContainer)
            return _derivedType::getMethodFunctors()[pFunctorId.m_lambdaIndex](pFunctorId, pTarget, std::forward<_params>(_args)...);
        }
    };
}