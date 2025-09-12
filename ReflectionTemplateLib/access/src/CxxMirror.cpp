/*************************************************************************
 *                                                                       *
 *  Reflection Template Library (RTL) - Modern C++ Reflection Framework  *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP          *
 *                                                                       *
 *  Copyright (c) 2025 Neeraj Singh <reflectcxx@outlook.com>             *
 *  SPDX-License-Identifier: MIT                                         *
 *                                                                       *
 *************************************************************************/


#include "RObject.h"
#include "CxxMirror.h"
#include "ReflectCast.h"

namespace rtl 
{
    namespace detail
    {
        std::size_t generate_unique_id()
        {
            // Starts with ONE, ZERO denotes TypeId<>::None. [Never change, critical.]
            static std::atomic<std::size_t> counter{ TypeId<>::None + 1 };
            return counter.fetch_add(1, std::memory_order_relaxed);
        }
    }

    error CxxMirror::setupCloning(const RObject& pTarget) const
    {
        const auto& itr = getRecordIdMap().find(pTarget.getTypeId());
        if (itr != getRecordIdMap().end()) 
        {
            const Record& record = itr->second;
            Method ctors = record.getMethod(detail::ctor_name(record.getRecordName())).value();
            std::size_t copyCtorIndex = ctors.getFunctors()[detail::Index::CopyCtor].getIndex();
            const_cast<RObject&>(pTarget).m_objectId.m_clonerIndex = copyCtorIndex;
            return error::None;
        }
        return error::CloningDisabled;
    }
}