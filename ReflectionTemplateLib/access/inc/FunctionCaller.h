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
        class RObject;
        class Function;
		
        template<class ..._signature>
        class FunctionCaller
        {
            //the function to be called.
            const Function& m_function;

            FunctionCaller(const Function& pFunction);

        public:

            template<class ..._args>
            std::pair<error, RObject> call(_args&&...) const noexcept;

            friend Function;
        };
    }
}