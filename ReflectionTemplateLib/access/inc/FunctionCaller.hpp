#pragma once

#include "RObject.h"
#include "Function.h"
#include "FunctionCaller.h"
#include "FunctorContainer.h"

namespace rtl
{
    namespace access
    {
        class RObject;

        template<class ..._signature>
        //FunctionCaller, holds only 'Method' associated with a static-member-function.
        inline FunctionCaller<_signature...>::FunctionCaller(const Function& pFunction)
            :m_function(pFunction) {
        }

        template<class ..._signature>
        template<class ..._args>
        inline std::pair<error, RObject> rtl::access::FunctionCaller<_signature...>::call(_args&&...params) const noexcept
        {
            error err;
            if constexpr (sizeof...(_signature) == 0) {
                using Container = detail::FunctorContainer<std::remove_reference_t<_args>...>;
                const std::size_t& index = m_function.hasSignatureId(Container::getContainerId());
                if (index != -1) { //true, if the arguments sent matches the functor signature associated with this 'Function' object
                    const auto& robj = Container::template forwardCall<_args...>(err, index, std::forward<_args>(params)...);
                    return { err, robj };
                }
            }
            else {
                using Container = detail::FunctorContainer<_signature...>;
                const std::size_t& index = m_function.hasSignatureId(Container::getContainerId());
                if (index != -1) { //true, if the arguments sent matches the functor signature associated with this 'Function' object
                    const auto& robj = Container::template forwardCall<_args...>(err, index, std::forward<_args>(params)...);
                    return { err, robj };
                }
            }
            //else return with error::SignatureMismatch.
            return { error::SignatureMismatch, RObject() };
        }
    }
}