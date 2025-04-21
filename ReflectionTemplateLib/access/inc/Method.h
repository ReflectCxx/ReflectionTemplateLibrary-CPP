#pragma once

#include <functional>

#include "Function.h"
#include "Instance.h"
#include "MethodInvoker.h"

namespace rtl {

    namespace access
    {
    /*  @class: Method
        * extends 'Function' class and adds interfaces to call member function.
        * invokes only static & non-static member functions via reflection.
        * deletes the base's 'operator()()'.
        * redefines 'operator()()', to accept only target object and returns lambda.
        * the returned lambda is then called with the arguments corresponding to the functor associated with it.
    */  class Method : public Function
        {
        private:

            //private ctor, called by 'Record' class.
            explicit Method(const Function& pFunction);

            //private ctor, called by 'Record' class.
            explicit Method(const Function& pFunction, const detail::FunctorId& pFunctorId, const std::string& pFunctorName);

            //invokes the constructor associated with this 'Method'
            template<class ..._args>
            RStatus invokeCtor(_args&&...params) const;

            //invokes the member-function associated with this 'Method'
            template<class _containerMute, class _containerConst, class ..._args>
            RStatus invoke(const Instance& pTarget, _args&&...params) const;

            //invokes only const member-function associated with this 'Method'
            template<class _containerMute, class _containerConst, class ..._args>
            RStatus invokeConst(const Instance& pTarget, _args&&...params) const;
            
            //invokes only static member-function associated with this 'Method'
            template<class ..._args>
            RStatus invokeStatic(_args&&...params) const;

            //called from class 'Record', creates a 'Method' object for destructor.
            static Method getDestructorMethod(const Function& pFunction, const detail::FunctorId& pFunctorId);

        public:

            //indicates if a particular set of arguments accepted by the functor associated with it.
            template<class ..._args>
            const bool hasSignature() const;

            //set 'no' object to call static method. (takes no parameter)
            const MethodInvoker<FunctorType::Static> bind() const;

            //set 'target' object on which the functor associated with this will be called.
            const MethodInvoker<FunctorType::Method> bind(const Instance& pTarget) const;

            
            template<class ..._signature>
            const MethodInvoker<FunctorType::Static, _signature...> bind() const;

            
            template<class ..._signature>
            const MethodInvoker<FunctorType::Method, _signature...> bind(const Instance& pTarget) const;

            //friends :)
            template<FunctorType _type, class ..._signature>
            friend class MethodInvoker;
            friend detail::CxxReflection;
            friend Record;

        public:

        /*  @method: operator()()
            @return: lambda
            * accepts no arguments for 'target', since associated functor is static-member-functions.
            * returns a lambda, which forwards the call to finally call the associated static-member-function functor.
            * provides syntax like,'method()(params...)', first'()' is empty & second'()' takes the actual params.
        */  constexpr auto operator()() const
            {
                return [this](auto&&...params) {
                    return Function::operator()(std::forward<decltype(params)> (params)...);
                };
            }


        /*  @method: operator()(const Instance&)
            @param: const Instance& (target object)
            @return: lambda
            * accepts 'pTarget', which contains the actual object on which the member-function functor associated with 'this' is invoked.
            * returns a lambda, which forwards the call to 'call', finally invoking the associated non-static-member-function functor.
            * provides syntax like, 'method(pTarget)(params...)', keeping the target & params seperate.
        */  constexpr auto operator()(const Instance& pTarget) const
            {
                return [&](auto&&...params)->RStatus {
                    return bind(pTarget).call(std::forward<decltype(params)>(params)...);
                };
            }
        };
    }
}