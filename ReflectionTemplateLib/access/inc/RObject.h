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

#include <memory>
#include <atomic>
#include <functional>

#include "view.h"
#include "TypeId.h"
#include "RObjectId.h"
#include "rtl_traits.h"


namespace rtl::detail
{
    template<class  T>
    struct RObjectUPtr;

    class RObjExtractor;

    struct RObjectBuilder;
}


namespace rtl::access
{
    class Function;

    //Reflecting the object within.
    class RObject
    {
        using Cloner = std::function<RObject(error&, const RObject&, rtl::alloc, detail::EntityKind)>;

        mutable Cloner m_getClone;
        mutable std::any m_object;
        mutable detail::RObjectId m_objectId;

        static std::atomic<std::size_t> m_rtlManagedInstancesCount;

        RObject(const RObject&) = default;
        RObject(std::any&& pObject, Cloner&& pCloner, const detail::RObjectId& pRObjectId);

        template<rtl::alloc _allocOn, detail::EntityKind _entityKind>
        std::pair<rtl::error, RObject> createCopy() const;

        template<class T>
        std::optional<rtl::view<T>> performConversion(const std::size_t pIndex) const;

    public:

        RObject() = default;
        ~RObject() = default;
        RObject(RObject&&) noexcept;
        RObject& operator=(RObject&&) = delete;
        RObject& operator=(const RObject&) = delete;

        GETTER(std::size_t, TypeId, m_objectId.m_typeId)
        GETTER_BOOL(Empty, (m_object.has_value() == false))
        GETTER_BOOL(OnHeap, (m_objectId.m_allocatedOn == alloc::Heap))
        GETTER_BOOL(AllocatedByRtl, (m_objectId.m_allocatedOn == alloc::Heap))

    /*  Reflection Const Semantics:
    *   - All reflected objects default to mutable internally; API enforces logical constness.
    *   - RTL may 'const_cast' its own objects(allocated via RTL) but preserves logical constness.
    *   - External objects (e.g. returned via Reflected call) keep original qualifier; if const, then const_cast is unsafe.
    */  GETTER_BOOL(ConstCastSafe, m_objectId.m_isConstCastSafe)

        template <class _asType>
        bool canViewAs() const;

        template<rtl::alloc _allocOn, rtl::copy _copyTarget = rtl::copy::Auto>
        std::pair<rtl::error, RObject> clone() const;

        template<class T, std::enable_if_t<traits::is_unique_ptr_v<T>, int> = 0>
        std::optional<rtl::view<T>> view() const;

        template<class T, std::enable_if_t<traits::is_shared_ptr_v<T>, int> = 0>
        std::optional<rtl::view<T>> view() const;

        template<class T, std::enable_if_t<traits::is_not_any_wrapper_v<T>, int> = 0>
        std::optional<rtl::view<T>> view() const;

        //friends :)
        template<class T>
        friend struct detail::RObjectUPtr;
        friend detail::RObjExtractor;
        friend detail::RObjectBuilder;
    };
}