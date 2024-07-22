#pragma once

#include <functional>

#include "Function.h"
#include "Instance.h"

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
    */  template<FunctorType _type>
        class MethodInvoker
        {
            //the method to be called.
            const Method& m_method;

            //the object on which, the method needs to be called.
            const Instance& m_target;
			
            MethodInvoker(const Method& pMethod, const Instance& pTarget);

        public:

            template<class ..._args>
            RStatus call(_args...) const noexcept;

            friend Method;
        };


    /*  @class: MethodInvoker
        @param: FunctorType::Static (explicitly specialized)
        * invokes the assigned method on the assigned object.
        * invokes only static member function via reflection.
        * its objects are only cretaed and returned by 'Method::on()' method.
        * purpose of this class is only to provide method call syntax like, 'method.on().call(params...)'
        * 'on()' will take no target as parameter, since the method being called is 'static'.
    */  template<>
        class MethodInvoker<FunctorType::Static>
        {
            const Method& m_method;

            MethodInvoker(const Method& pMethod);

        public:

            template<class ..._args>
            RStatus call(_args...) const noexcept;

            friend Method;
        };


    /*  @class: Method
        * extends 'Function' class and adds interfaces to call member function.
        * invokes only static & non-static member functions via reflection.
        * deletes the base's 'operator()()'.
        * redefines 'operator()()', to accept only target object and returns lambda.
        * the returned lambda is then called with the arguments corresponding to the functor associated with it.
    */  class Method : public Function
        {
            //private ctor, called by 'Record' class.
            Method(const Function& pFunction);

            //private ctor, called by 'Record' class.
            Method(const Function& pFunction, const detail::FunctorId& pFunctorId, const std::string& pFunctorName);

            //invokes the constructor associated with this 'Method'
            template<class ..._args>
            RStatus invokeCtor(_args...params) const;

            //invokes the member-function associated with this 'Method'
            template<class ..._args>
            RStatus invoke(const Instance& pTarget, _args...params) const;

            //invokes only const member-function associated with this 'Method'
            template<class ..._args>
            RStatus invokeConst(const Instance& pTarget, _args...params) const;
            
            //invokes only static member-function associated with this 'Method'
            template<class ..._args>
            RStatus invokeStatic(_args...params) const;

            //called from class 'Record', creates a 'Method' object for destructor.
            static Method getDestructorMethod(const Function& pFunction, const detail::FunctorId& pFunctorId);

        public:

            //indicates if a particular set of arguments accepted by the functor associated with it.
            template<class _arg0, class ..._args>
            const bool hasSignature() const;

            //set 'no' object to call static method. (takes no parameter)
            const MethodInvoker<FunctorType::Static> on() const;

            //set 'target' object on which the functor associated with this will be called.
            const MethodInvoker<FunctorType::Method> on(const Instance& pTarget) const;

            
        /*  @method: operator()()
            @return: lambda
            * accepts no arguments for 'target', since associated functor is static-member-functions.
            * returns a lambda, which forwards the call to finally call the associated static-member-function functor.
            * provides syntax like,'method()(params...)', first'()' is empty & second'()' takes the actual params.
        */  constexpr auto operator()() const
            {
                return [this](auto...params) {
                    return Function::operator()(params...);
                };
            }


        /*  @method: operator()(const Instance&)
            @param: const Instance& (target object)
            @return: lambda
            * accepts 'pTarget', which contains the actual object on which the member-function functor associated with 'this' is invoked.
            * returns a lambda, which forwards the call to finally call the associated non-static-member-function functor.
            * provides syntax like, 'method(pTarget)(params...)', keeping the target & params seperate.
        */  constexpr auto operator()(const Instance& pTarget) const
            {
                return [&](auto...params)->RStatus
                {
                    if (pTarget.isEmpty()) {
                        //if the target is empty.
                        return RStatus(Error::EmptyInstance);
                    }

                    if (pTarget.getTypeId() != getRecordTypeId()) {
                        //if the target type-id & type-id of the 'class/struct' owner of the associated functor do not match.
                        return RStatus(Error::InstanceTypeMismatch);
                    }

                    switch (pTarget.getQualifier())
                    {
                        //if the target is non-const, const & non-const member function can be invoked on it.
                        case TypeQ::Mute: return invoke(pTarget, params...);

                        //if the target is const, only const member function can be invoked on it.
                        case TypeQ::Const: return invokeConst(pTarget, params...);
                    }

                    //only an empty 'Instance' will have TypeQ::None.
                    return RStatus(Error::EmptyInstance);
                };
            }

            //deletes base class 'operator()()'
            template<class ..._args>
            RStatus operator()(_args...) const noexcept = delete;

            //deletes base class 'call()'
            template<class ..._args>
            RStatus call(_args...) const noexcept = delete;

            //friends :)
            template<FunctorType _type>
            friend class MethodInvoker;
            friend detail::CxxReflection;
            friend Record;
        };
    }
}