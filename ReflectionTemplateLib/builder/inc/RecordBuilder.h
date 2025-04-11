#pragma once

#include "Function.h"

namespace rtl {

    namespace builder 
    {
        template<class _recordType, class ..._ctorSignature>
        class ConstructorBuilder;

    /*  @class: RecordBuilder
        @param: <_recordType>, a struct/class type.
        * provides interface to register member-function & constructors/destructor of a class/struct.
    */  template<class _recordType>
        class RecordBuilder
        {
            const std::string& m_record;
            const std::string& m_namespace;

        public:

            RecordBuilder(const std::string& pNamespace, const std::string& pRecord);

            template<class ..._signature>
            const ConstructorBuilder<_recordType, _signature...> constructor() const;

            const Builder<TypeQ::Mute> method(const std::string& pFunction) const;

            const Builder<TypeQ::None> methodStatic(const std::string& pFunction) const;

            const Builder<TypeQ::Const> methodConst(const std::string& pFunction) const;

            template<class ..._signature>
            const Builder<TypeQ::Mute, _signature...> method(const std::string& pFunction) const;

            template<class ..._signature>
            const Builder<TypeQ::None, _signature...> methodStatic(const std::string& pFunction) const;

            template<class ..._signature>
            const Builder<TypeQ::Const, _signature...> methodConst(const std::string& pFunction) const;
        };
    }
}
