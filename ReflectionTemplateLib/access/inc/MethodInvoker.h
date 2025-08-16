/*_________________________________________________________________________
* Copyright 2025 Neeraj Singh
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
___________________________________________________________________________*/

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