/*************************************************************************
 *                                                                       *
 *  Reflection Template Library (RTL) - Modern C++ Reflection Framework  *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP          *
 *                                                                       *
 *  Copyright (c) 2025 Neeraj Singh <reflectcxx@outlook.com>             *
 *  SPDX-License-Identifier: MIT                                         *
 *                                                                       *
 *************************************************************************/


#pragma once

#include <any>
#include <vector>
#include "ReflectCast.h"

namespace rtl {
    class RObject;
}

namespace rtl::detail
{
    class RObjExtractor;
    class RObjectBuilder;

    struct RObjectId
    {
        friend RObjExtractor;
        friend RObjectBuilder;
        friend RObject;

        GETTER(std::size_t, TypeId, m_typeId)
        GETTER(EntityKind, ContainedAs, m_containsAs)

    private:

        mutable bool m_isWrappingConst;
        mutable bool m_isConstCastSafe;

        mutable alloc m_allocatedOn;
        mutable Wrapper m_wrapperType;
        mutable EntityKind m_containsAs;

        mutable std::size_t m_typeId;
        mutable std::size_t m_wrapperTypeId;

        RObjectId(RObjectId&&) = default;
        RObjectId(const RObjectId&) = default;
        RObjectId& operator=(RObjectId&&) = delete;
        RObjectId& operator=(const RObjectId&) = delete;


        RObjectId()
            : m_isWrappingConst(false)
            , m_isConstCastSafe(false)
            , m_allocatedOn(alloc::None)
            , m_wrapperType(Wrapper::None)
            , m_containsAs(EntityKind::None)
            , m_typeId(TypeId<>::None)
            , m_wrapperTypeId(TypeId<>::None)
        { }


        RObjectId(alloc pAllocOn, bool pIsConstCastSafe, Wrapper pWrapperType, bool pIsStoredConst, EntityKind pContainsAs,
                  std::size_t pTypeId, std::size_t pWrapperTypeId)
            : m_isWrappingConst(pIsStoredConst)
            , m_isConstCastSafe(pIsConstCastSafe)
            , m_allocatedOn(pAllocOn)
            , m_wrapperType(pWrapperType)
            , m_containsAs(pContainsAs)
            , m_typeId(pTypeId)
            , m_wrapperTypeId(pWrapperTypeId)
        { }


        void reset() const
        {
            m_isWrappingConst = false;
            m_isConstCastSafe = false;
            m_allocatedOn = alloc::None;
            m_wrapperType = Wrapper::None;
            m_containsAs = EntityKind::None;
            m_typeId = TypeId<>::None;
            m_wrapperTypeId = TypeId<>::None;
        }


        template<class T>
        static constexpr EntityKind getEntityKind()
        {
            using W = traits::std_wrapper<traits::raw_t<T>>;
            using _T = traits::raw_t<std::conditional_t<(W::type == Wrapper::None), T, typename W::value_type>>;
            constexpr bool isRawPtr = traits::is_raw_ptr_v<T>;
            constexpr bool isWrapper = (W::type != Wrapper::None);

            if constexpr (isWrapper && !isRawPtr) {
                return EntityKind::Wrapper;
            }
            else if constexpr (isRawPtr && !isWrapper) {
                return EntityKind::Ref;
            }
            else if constexpr (!isWrapper && !isRawPtr) {
                return EntityKind::Value;
            }
        }


        template<class T, rtl::alloc _allocOn>
        static RObjectId create(bool pIsConstCastSafe)
        {
            // extract wrapper info.
            using _W = traits::std_wrapper<traits::raw_t<T>>;
            // extract Un-Qualified raw type.
            using _T = traits::raw_t<std::conditional_t<(_W::type == Wrapper::None), T, typename _W::value_type>>;
            constexpr EntityKind containedAs = getEntityKind<T>();
            
            const std::size_t wrapperId = _W::id();
            const std::size_t typeId = rtl::detail::TypeId<_T>::get();
            const bool isWrappingConst = (_W::type != Wrapper::None && traits::is_const_v<typename _W::value_type>);
            return RObjectId(_allocOn, pIsConstCastSafe, _W::type, 
                             isWrappingConst, containedAs, typeId, wrapperId);
        }
    };
}