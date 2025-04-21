#pragma once

#include "TypeId.h"
#include "Constants.h"
#include "RStatus.h"

namespace rtl {

    namespace access
    {
        //forward decls
        class Method;
        class Record;

    /*  @class: MethodInvoker
        @param: <FunctorType _type>, can be any 'FunctorType' other than FunctorType::Static.
        * invokes the assigned method on the assigned object.
        * invokes only non-static member function via reflection.
        * its objects are only cretaed and returned by 'Method::on()' method.
        * purpose of this class is only to provide method call syntax like, 'method.on(target).call(params...)'
    */  template<FunctorType _type, class ..._signature>
        class MethodInvoker
        {
            //the method to be called.
            const Method& m_method;

            //the object on which, the method needs to be called.
            const Instance& m_target;

            MethodInvoker(const Method& pMethod, const Instance& pTarget);

        public:

            template<class ..._args>
            RStatus call(_args&&...) const noexcept;

            friend Method;
        };


    /*  @class: MethodInvoker
        @param: FunctorType::Static (explicitly specialized)
        * invokes the assigned method on the assigned object.
        * invokes only static member function via reflection.
        * its objects are only cretaed and returned by 'Method::on()' method.
        * purpose of this class is only to provide method call syntax like, 'method.on().call(params...)'
        * 'on()' will take no target as parameter, since the method being called is 'static'.
    */  template<class ..._signature>
        class MethodInvoker<FunctorType::Static, _signature...>
        {
            const Method& m_method;

            MethodInvoker(const Method& pMethod);

        public:

            template<class ..._args>
            RStatus call(_args&&...) const noexcept;

            friend Method;
        };
    }
}