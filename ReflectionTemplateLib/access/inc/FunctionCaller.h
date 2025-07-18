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