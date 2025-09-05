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
    struct RObjectId
    {
        bool m_isWrappingConst;
        bool m_isConstCastSafe;

        std::size_t m_typeId;
        std::size_t m_wrapperTypeId;

        alloc m_allocatedOn;
        Wrapper m_wrapperType;
        EntityKind m_containsAs;

        GETTER(std::size_t, TypeId, m_typeId)
        GETTER(EntityKind, ContainedAs, m_containsAs)

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
            constexpr EntityKind entityKind = getEntityKind<T>();
            
            const std::size_t wrapperId = _W::id();
            const std::size_t typeId = rtl::detail::TypeId<_T>::get();
            const bool isWrappingConst = (_W::type != Wrapper::None && traits::is_const_v<typename _W::value_type>);
            return RObjectId{ isWrappingConst, pIsConstCastSafe, typeId, wrapperId, _allocOn,  _W::type, entityKind };
        }
    };
}