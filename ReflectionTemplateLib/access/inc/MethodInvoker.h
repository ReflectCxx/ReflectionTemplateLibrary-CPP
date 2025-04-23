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
            const Instance& m_target;

            MethodInvoker(const Method& pMethod, const Instance& pTarget);

            template<class ..._finalSignature>
            struct Invoker {

                template<class ..._args>
                static RStatus invoke(const Method& pMethod, const Instance& pTarget, _args&&...);
            };

        public:

            template<class ..._args>
            RStatus call(_args&&...) const noexcept;

            friend Method;
        };
    }
}