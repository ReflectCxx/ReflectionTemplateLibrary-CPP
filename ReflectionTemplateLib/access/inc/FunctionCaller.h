#pragma once

namespace rtl {

    namespace access
    {
        class RStatus;
        class Function;
		
        template<class ..._signature>
        class FunctionCaller
        {
            //the function to be called.
            const Function& m_function;

            FunctionCaller(const Function& pFunction);

        public:

            template<class ..._args>
            RStatus call(_args&&...) const noexcept;

            friend Function;
        };
    }
}