#pragma once
#include "Proxy.h"

namespace proxy_test
{
    /**
     * @brief Forwards a call to a method of the Original class instance.
     *
     * This method uses reflection to dynamically invoke a method on the Original class instance.
     * It checks if the method exists and if the signature matches the provided arguments.
     *
     * @tparam _args The types of the arguments to be forwarded.
     * @param pFunctionName The name of the function to call.
     * @param params The parameters to pass to the function.
     * @return The result of the function call as a std::any object. If the method does not exist or the signature does not match, returns an empty std::any object.
     */
    template<class ..._args>
    inline std::pair<rtl::error, rtl::access::RObject> Proxy::forwardCall(const std::string& pFunctionName, _args&& ...params)
    {
        const auto orgMethod = OriginalReflection::getClass()->getMethod(pFunctionName);
        if (!orgMethod.has_value()) {
            return { rtl::error::FunctionNotRegisterdInRtl, rtl::access::RObject() };
        }
        if (orgMethod->hasSignature<_args...>()) {
            return orgMethod->bind(m_originalObj).call(std::forward<_args>(params)...);
        }
        return { rtl::error::SignatureMismatch, rtl::access::RObject() };
    }


    /**
     * @brief Forwards a call to a static method of the Original class.
     *
     * This method uses reflection to dynamically invoke a static method on the Original class.
     * It checks if the method exists and if the signature matches the provided arguments.
     *
     * @tparam _args The types of the arguments to be forwarded.
     * @param pFunctionName The name of the static function to call.
     * @param params The parameters to pass to the function.
     * @return The result of the function call as a std::any object. If the method does not exist or the signature does not match, returns an empty std::any object.
     */
    template<class ..._args>
    inline std::pair<rtl::error, rtl::access::RObject> Proxy::forwardStaticCall(const std::string& pFunctionName, _args&& ...params)
    {
        const auto orgMethod = OriginalReflection::getClass()->getMethod(pFunctionName);
        if (!orgMethod.has_value()) {
            return { rtl::error::FunctionNotRegisterdInRtl, rtl::access::RObject() };
        }
        if (orgMethod->hasSignature<_args...>()) {
            return orgMethod->bind().call(std::forward<_args>(params)...);
        }
        return { rtl::error::SignatureMismatch, rtl::access::RObject() };
    }
}
