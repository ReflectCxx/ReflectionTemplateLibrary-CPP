/*****************************************************************
 *                                                               *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP  *
 *  Copyright (c) 2025 Neeraj Singh (reflectcxx@outlook.com)     *
 *  SPDX-License-Identifier: MIT                                 *
 *                                                               *
 *****************************************************************/


#pragma once

namespace rtl {

    namespace access
    {
        //forward decls
        class Method;


        template<class ..._signature>
        class MethodInvoker
        {
            //the method to be called.
            const Method& m_method;

            //the object on which, the method needs to be called.
            const RObject& m_target;

            MethodInvoker(const Method& pMethod, const RObject& pTarget);

            template<class ..._finalSignature>
            struct Invoker {

                template<class ..._args>
                static RObject invoke(error& pError, const Method& pMethod, const RObject& pTarget, _args&&...);
            };

        public:

            template<class ..._args>
            std::pair<error, RObject> call(_args&&...) const noexcept;

            friend Method;
        };


        template<methodQ _Q, class ..._signature>
        class MethodInvokerQ
        {
            //the method to be called.
            const Method& m_method;

            //the object on which, the method needs to be called.
            const RObject& m_target;

            MethodInvokerQ(const Method& pMethod, const RObject& pTarget);

            template<class ..._finalSignature>
            struct Invoker {

                template<class ..._args>
                static RObject invoke(error& pError, const Method& pMethod, const RObject& pTarget, _args&&...);
            };

        public:

            template<class ..._args>
            std::pair<error, RObject> call(_args&&...) const noexcept;

            friend Method;
        };
    }
}