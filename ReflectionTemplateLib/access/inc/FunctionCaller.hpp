#pragma once

#include "Function.h"
#include "FunctionCaller.h"
#include "FunctorContainer.h"

namespace rtl 
{
    namespace access
    {
        template<class ..._signature>
        //FunctionCaller, holds only 'Method' associated with a static-member-function.
        inline FunctionCaller<_signature...>::FunctionCaller(const Function& pFunction)
            :m_function(pFunction) {
        }

        template<class ..._signature>
        template<class ..._args>
        inline RStatus rtl::access::FunctionCaller<_signature...>::call(_args&&...params) const noexcept
        {
            if constexpr (sizeof...(_signature) == 0) {
                using Container = detail::FunctorContainer<std::remove_reference_t<_args>...>;
                const std::size_t& index = m_function.hasSignatureId(Container::getContainerId());
                if (index != -1) { //true, if the arguments sent matches the functor signature associated with this 'Function' object
                    return Container::template forwardCall<_args...>(index, std::forward<_args>(params)...);
                }
            }
            else {
                using Container = detail::FunctorContainer<_signature...>;
                const std::size_t& index = m_function.hasSignatureId(Container::getContainerId());
                if (index != -1) { //true, if the arguments sent matches the functor signature associated with this 'Function' object
                    return Container::template forwardCall<_args...>(index, std::forward<_args>(params)...);
                }
            }
            //else return with Error::SignatureMismatch.
            return RStatus(Error::SignatureMismatch);
        }
    }
}