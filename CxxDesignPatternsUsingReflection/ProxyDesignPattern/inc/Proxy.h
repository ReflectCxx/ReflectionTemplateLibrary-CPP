#pragma once

#include <any>
#include "OriginalReflection.h"

namespace proxy_test {

    /**
     * @brief The Proxy class provides a mechanism to forward calls to an instance of the "Original" class.
     */
    class Proxy
    {
        rtl::access::Instance m_originalObj; //Reflected type instance of the "Original" class.

    public:

        /**
         * @brief Constructs a new Proxy object.
         *
         * Initializes the m_originalObj with an instance of the "Original" class.
         */
        Proxy();

        /**
         * @brief Forwards a call to a method of the "Original" class instance.
         *
         * @tparam _args The types of the arguments to be forwarded.
         * @param pFunctionName The name of the function to call.
         * @param params The parameters to pass to the function.
         * @return The result of the function call as a std::any object.
         */
        template<class ..._args>
        std::any forwardCall(const std::string& pFunctionName, _args ...params);

        /**
         * @brief Forwards a call to a static method of the "Original" class.
         *
         * @tparam _args The types of the arguments to be forwarded.
         * @param pFunctionName The name of the static function to call.
         * @param params The parameters to pass to the function.
         * @return The result of the function call as a std::any object.
         */
        template<class ..._args>
        static std::any forwardStaticCall(const std::string& pFunctionName, _args ...params);
    };
}
