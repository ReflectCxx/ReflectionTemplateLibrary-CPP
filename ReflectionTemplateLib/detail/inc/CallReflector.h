#pragma once

#include <optional>
#include "Constants.h"

namespace rtl {

    namespace access {
        //forward decl.
        class RStatus;
    }

    namespace detail
    {
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
            static access::RStatus forwardCall(std::size_t pFunctorIndex, _params..._args)
            {
                //'getFunctors()' must be implemented by _derivedType (FunctorContainer).
                return _derivedType::getFunctors().at(pFunctorIndex)(_args...);
            }


        /*  @method: forwardCall
            @param: pFunctorIndex (index of the lambda), _args...(arguments to be passed to that lambda)
            * gets the lambda vector from '_derivedType' and calls the lambda at given index with '_args'.
            * this 'forwardCall' is for calling lambda containing member-function functors.
        */  template<class ..._params>
            static access::RStatus forwardCall(const std::any& pTarget, std::size_t pFunctorIndex, _params..._args)
            {
                //'getMethodFunctors()' is implemented by _derivedType (MethodContainer)
                return _derivedType::getMethodFunctors().at(pFunctorIndex)(pTarget, _args...);
            }
        };
    }
}