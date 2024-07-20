#pragma once

#include <string>
#include "Constants.h"
#include "Builder.h"

namespace rtl {

    namespace builder 
    {
        template<class _recordType>
        class RecordBuilder;

    /*  @class: Reflect
        * provides interface to register all kinds of functions (member/non-member).
    */  class Reflect
        {
            //name of the class, struct being registered as string.
            std::string m_record;

            //name of the namespace being registered as string.
            std::string m_namespace;

        public:

            Reflect();
            Reflect(const Reflect&) = delete;
            Reflect& operator=(const Reflect&) = delete;

            Reflect& nameSpace(const std::string& pNamespace);

            template<class ..._signature>
            constexpr const Builder<TypeQ::None, _signature...> function(const std::string& pFunction);

            template<class _recordType>
            constexpr const RecordBuilder<_recordType> record(const std::string& pClass);
        };
    }
}