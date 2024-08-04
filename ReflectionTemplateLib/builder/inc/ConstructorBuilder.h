#pragma once

#include "Constants.h"

namespace rtl {

    namespace builder 
    {
    /*  @class: ConstructorBuilder
        @param: _recordType - struct/class type. 
        *       _signature...- constructor args type (none/_record&/const _record& or any combination of parameters) 
        * provides interface to register constructors/destructor of a class/struct.
        * when the very first constructor(any- copy/default/parametrized) is registered, destructor gets registered implicitly.
        * all the objects are created via reflection are on heap, using 'new'.
        * the constructed objects are returned wrapped in 'Instance' object, with type erased.
        * lifetime of created objects are managed using 'shared_ptr'.
    */  template<class _recordType, class ..._ctorSignature>
        class ConstructorBuilder
        {
            //given name of the class/struct.
            const std::string& m_record;

            //given name of the namespace.
            const std::string& m_namespace;

        /*  type of constructor to be registered.
            FunctorType::Ctor - default/parametrized constructor.
            FunctorType::CopyCtor - copy constructor args, '_recordType&'
            FunctorType::CopyCtorConst - copy constructor args, 'const _recordType&'
        */  const FunctorType m_ctorType;

            ConstructorBuilder() = delete;

        public:

            ConstructorBuilder(const std::string& pNamespace, const std::string& pRecord,
                               const FunctorType& pCtorType);
          
            inline constexpr const access::Function build() const;
		};
	}
}