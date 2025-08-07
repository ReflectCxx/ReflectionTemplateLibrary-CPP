/*_________________________________________________________________________
* Copyright 2025 Neeraj Singh
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
___________________________________________________________________________*/

#pragma once

#include <vector>
#include "ReflectCast.h"

namespace rtl::detail
{
    class RObjectId
    {
        static std::vector<traits::ConverterPair> m_conversions;

    public:

        bool m_isTypeConst;
        alloc m_allocatedOn;
        Wrapper m_wrapperType;
        IsPointer m_isPointer;
        
        std::size_t m_typeId;
        std::size_t m_ptrTypeId;
        std::size_t m_wrapperTypeId;
        std::string m_typeStr;

        const std::vector<traits::ConverterPair>& m_converters;

        RObjectId()
            : m_isTypeConst(false)
            , m_allocatedOn(alloc::None)
            , m_wrapperType(Wrapper::None)
            , m_isPointer(IsPointer::No)
            , m_typeId(TypeId<>::None)
            , m_ptrTypeId(TypeId<>::None)
            , m_wrapperTypeId(TypeId<>::None)
            , m_typeStr("")
            , m_converters(m_conversions)
        { }

        RObjectId(bool pIsTypeConst, alloc pAllocOn, Wrapper pWrapperType, IsPointer pIsPtr, std::size_t pTypeId,
                  std::size_t pPtrTypeId, std::size_t pWrapperTypeId, const std::string& pTypeStr, 
                  const std::vector<traits::ConverterPair>& pConverters)
            : m_isTypeConst(pIsTypeConst)
            , m_allocatedOn(pAllocOn)
            , m_wrapperType(pWrapperType)
            , m_isPointer(pIsPtr)
            , m_typeId(pTypeId)
            , m_ptrTypeId(pPtrTypeId)
            , m_wrapperTypeId(pWrapperTypeId)
            , m_typeStr(pTypeStr)
            , m_converters(pConverters)
        { }

        void reset()
        {
            m_isTypeConst = false;
            m_allocatedOn = alloc::None;    //very important, identifies empty/moved-from 'RObject's.
            m_wrapperType = Wrapper::None;
            m_isPointer = IsPointer::No;
            m_typeId = TypeId<>::None;
            m_ptrTypeId = TypeId<>::None;
            m_wrapperTypeId = TypeId<>::None;
            m_typeStr.clear();
        }

        RObjectId(RObjectId&&) = default;
        RObjectId(const RObjectId&) = default;
        RObjectId& operator=(RObjectId&&) = delete;
        RObjectId& operator=(const RObjectId&) = delete;

        template<class T, rtl::alloc _allocOn>
        static RObjectId create()
        {
            using _T = traits::remove_const_n_ref_n_ptr<T>;
            using _isPointer = std::is_pointer<traits::remove_const_n_reference<T>>;

            const std::size_t typeId = rtl::detail::TypeId<_T>::get();
            const std::size_t typePtrId = rtl::detail::TypeId<_T*>::get();
            const std::size_t wrapperId = detail::TypeId<>::None;
            const auto& typeStr = rtl::detail::TypeId<_T>::toString();
            const auto& conversions = rtl::detail::ReflectCast<_T>::getConversions();
            const auto isPointer = (_isPointer::value ? IsPointer::Yes : IsPointer::No);
            constexpr auto isTypeConst = (_allocOn != alloc::Heap ? traits::is_const_v<T> : false);
            return RObjectId(isTypeConst, _allocOn, Wrapper::None, isPointer, typeId, typePtrId, wrapperId, typeStr, conversions);
        }

        template<class W>
        static RObjectId createForWrapper()
        {
            using _W = traits::std_wrapper<traits::remove_const_n_ref_n_ptr<W>>;
            using _T = _W::baseT;

            const std::size_t typeId = detail::TypeId<_T>::get();
            const std::size_t typePtrId = detail::TypeId<_T*>::get();
            const std::size_t wrapperId = _W::id();
            const auto& typeStr = detail::TypeId<_T>::toString();
            const auto& conversions = detail::ReflectCast<_T>::getConversions();
            return RObjectId(std::is_const_v<_T>, rtl::alloc::Stack, _W::type, rtl::IsPointer::Yes, typeId, typePtrId, wrapperId, typeStr, conversions);
        }
    };
}