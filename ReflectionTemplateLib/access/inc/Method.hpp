#pragma once
#include "Method.h"
#include "MethodInvoker.hpp"

namespace rtl
{
    namespace access
    {
        template<class ..._signature>
        inline const MethodInvoker<_signature...> Method::bind(const RObject& pTarget) const
        {
            return MethodInvoker<_signature...>(*this, pTarget);
        }


    /*  @method: invokeCtor()
        @params: variable arguments.
        @return: RStatus
        * calls the constructor with given arguments.
    */  template<class ..._args>
        inline std::pair<error, RObject> Method::invokeCtor(alloc pAllocType, _args&& ...params) const
        {
            return Function::bind().call<alloc, _args...>(std::move(pAllocType), std::forward<_args>(params)...);
        }


    /*  @method: hasSignature<...>()
        @params: template params, <_arg0, ..._args> (expects at least one args- _args0)
        @return: bool
        * checks if the member-function functor associated with this 'Method', takes template specified arguments set or not.
    */  template<class ..._args>
        inline bool Method::hasSignature() const
        {
            switch (getQualifier())
            {
                case TypeQ::None: {
                    return Function::hasSignature<_args...>();
                }
                case TypeQ::Mute: {
                    using Container = detail::MethodContainer<TypeQ::Mute, _args...>;
                    return (hasSignatureId(Container::getContainerId()) != -1);
                }
                case TypeQ::Const: {
                    using Container = detail::MethodContainer<TypeQ::Const, _args...>;
                    return (hasSignatureId(Container::getContainerId()) != -1);
                }
            }
            return false;
        }
    }
}