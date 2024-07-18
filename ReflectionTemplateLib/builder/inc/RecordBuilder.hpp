#pragma once

#include "RecordBuilder.h"
#include "ConstructorBuilder.hpp"

namespace rtl {

    namespace builder
    {
        template<class _recordType>
        inline RecordBuilder<_recordType>::RecordBuilder(const std::string& pNamespace, const std::string& pRecord)
            : m_record(pRecord)
            , m_namespace(pNamespace) {
        }


        template<class _recordType>
        template<class ..._signature>
        inline constexpr const ConstructorBuilder<_recordType, _signature...> RecordBuilder<_recordType>::constructor() const
        {
            if constexpr (std::is_same_v<_recordType&, typename detail::TypeId<_signature...>::HEAD>) 
            {
                return ConstructorBuilder<_recordType, _signature...>(m_namespace, m_record, FunctorType::CopyCtor);
			      }
            else if constexpr (std::is_same_v<const _recordType&, typename detail::TypeId<_signature...>::HEAD>) 
            {
                return ConstructorBuilder<_recordType, _signature...>(m_namespace, m_record, FunctorType::CopyCtorConst);
            }
            else 
            {
                return ConstructorBuilder<_recordType, _signature...>(m_namespace, m_record, FunctorType::Ctor);
            }
        }


        template<class _recordType>
        inline constexpr const Builder<TypeQ::None> RecordBuilder<_recordType>::methodStatic(const std::string& pFunction) const
        {
            return Builder<TypeQ::None>(m_namespace, m_record, pFunction);
        }


        template<class _recordType>
        template<class ..._signature>
        inline constexpr const Builder<TypeQ::None, _signature...> RecordBuilder<_recordType>::methodStatic(const std::string& pFunction) const 
        {
            return Builder<TypeQ::None, _signature...>(m_namespace, m_record, pFunction);
        }


        template<class _recordType>
        inline constexpr const Builder<TypeQ::Mute> RecordBuilder<_recordType>::method(const std::string& pFunction) const
        {
            return Builder<TypeQ::Mute>(m_namespace, m_record, pFunction);
        }


        template<class _recordType>
        inline constexpr const Builder<TypeQ::Const> RecordBuilder<_recordType>::methodConst(const std::string& pFunction) const
        {
            return Builder<TypeQ::Const>(m_namespace, m_record, pFunction);
        }


        template<class _recordType>
        template<class ..._signature>
        inline constexpr const Builder<TypeQ::Mute, _signature...> RecordBuilder<_recordType>::method(const std::string& pFunction) const 
        {
            return Builder<TypeQ::Mute, _signature...>(m_namespace, m_record, pFunction);
        }


        template<class _recordType>
        template<class ..._signature>
        inline constexpr const Builder<TypeQ::Const, _signature...> RecordBuilder<_recordType>::methodConst(const std::string& pFunction) const 
        {
            return Builder<TypeQ::Const, _signature...>(m_namespace, m_record, pFunction);
        }
    }
}