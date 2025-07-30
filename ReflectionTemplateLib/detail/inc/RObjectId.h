#pragma once

#include <vector>
#include "rtl_traits.h"

namespace rtl::access {
    class RObject;
}

namespace rtl::detail
{
    class RObjectId
    {
        alloc m_allocatedOn;
        IsPointer m_isPointer;

        std::size_t m_typeId;
        std::size_t m_ptrTypeId;
        std::size_t m_wrapperTypeId;
        std::string m_typeStr;

        const std::vector<traits::ConverterPair>& m_converters;

        RObjectId()
            : m_allocatedOn(alloc::None)
            , m_isPointer(IsPointer::No)
            , m_typeId(TypeId<>::None)
            , m_ptrTypeId(TypeId<>::None)
            , m_wrapperTypeId(TypeId<>::None)
            , m_typeStr("")
            , m_converters(m_conversions)
        { }

        RObjectId(alloc pAllocOn, IsPointer pIsPtr, std::size_t pTypeId, 
                  std::size_t pPtrTypeId, std::size_t pWrapperTypeId, const std::string& pTypeStr, 
                  const std::vector<traits::ConverterPair>& pConverters)
            : m_allocatedOn(pAllocOn)
            , m_isPointer(pIsPtr)
            , m_typeId(pTypeId)
            , m_ptrTypeId(pPtrTypeId)
            , m_wrapperTypeId(pWrapperTypeId)
            , m_typeStr(pTypeStr)
            , m_converters(pConverters)
        { }

        void reset()
        {
            m_isPointer = IsPointer::No;
            m_allocatedOn = alloc::None;
            m_typeId = TypeId<>::None;
            m_ptrTypeId = TypeId<>::None;
            m_wrapperTypeId = TypeId<>::None;
            m_typeStr.clear();
        }

        RObjectId(RObjectId&&) = default;
        RObjectId(const RObjectId&) = default;
        RObjectId& operator=(RObjectId&&) = default;
        RObjectId& operator=(const RObjectId&) = default;

        static std::vector<traits::ConverterPair> m_conversions;

        //friends :)
        friend rtl::access::RObject;
    };
}