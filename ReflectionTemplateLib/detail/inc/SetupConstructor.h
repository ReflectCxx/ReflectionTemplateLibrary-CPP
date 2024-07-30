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
        protected:

            //adds the lambda wrapping destructor call to '_derivedType' (FunctorContainer)
            template<class _recordType>
            static const detail::FunctorId addDestructor();

            //adds the lambda, wrapping constructor call, recordType(_signature...), to '_derivedType' (FunctorContainer)
            template<class _recordType, class ..._signature>
            static const detail::FunctorId addConstructor();

            //adds the lambda, wrapping constructor call, _recordType(_recordType&') to '_derivedType' (FunctorContainer)
            template<class _recordType>
            static const detail::FunctorId addCopyConstructor();

            //adds the lambda, wrapping constructor call, _recordType(const _recordType&'), to '_derivedType' (FunctorContainer)
            template<class _recordType>
            static const detail::FunctorId addConstCopyConstructor();
        };
    }
}