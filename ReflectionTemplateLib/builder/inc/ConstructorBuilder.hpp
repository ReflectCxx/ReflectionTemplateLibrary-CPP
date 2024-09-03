#pragma once

#include "Function.h"
#include "Builder.hpp"
#include "ConstructorBuilder.h"

namespace rtl {

    namespace builder 
    {
        template<class _recordType, class ..._ctorSignature>
        inline ConstructorBuilder<_recordType, _ctorSignature...>::ConstructorBuilder(const std::string& pNamespace, const std::string& pRecord,
                                                                                      const FunctorType& pCtorType)
            : m_record(pRecord)
            , m_namespace(pNamespace)
            , m_ctorType(pCtorType)
        {
        }


    /*  @method: build()
        @param: none
        @return: 'Function' object.
        * constructs temparory object of class Builder<TypeQ::Mute> with given class/struct, namespace name & constructor type.
        * forwards the call to Builder<TypeQ::Mute>::build().
    */  template<class _recordType, class ..._ctorSignature>
        inline const access::Function ConstructorBuilder<_recordType, _ctorSignature...>::build() const
        {
            const auto& ctorName = (m_ctorType == FunctorType::CopyCtor ? CtorName::copy(m_record) : 
                                   (m_ctorType == FunctorType::CopyCtorConst ? CtorName::constCopy(m_record) : CtorName::ctor(m_record)));

            return Builder<TypeQ::Mute>(m_namespace, m_record, ctorName).build<_recordType, _ctorSignature...>();
        }
    }
}
