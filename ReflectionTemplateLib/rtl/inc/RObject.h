/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#pragma once

#include <inc/view.h>
#include <detail/inc/RObjectId.h>

namespace rtl::detail
{
    template<class  T>
    struct RObjectUPtr;

    class RObjExtractor;

    template<class  T>
    struct RObjectBuilder;
}


namespace rtl
{
    //Reflecting the object within.
    class RObject
    {
        std::optional<std::any> m_object = std::nullopt;
        detail::RObjectId m_objectId = {};

        RObject(const RObject&) = default;
        RObject(std::any&& pObject, const detail::RObjectId& pRObjId) noexcept;

        std::size_t getConverterIndex(const std::size_t pToTypeId) const;

        template<rtl::alloc _allocOn, detail::EntityKind _entityKind>
        Return createCopy() const;

        template<class T>
        std::optional<rtl::view<T>> performConversion(const std::size_t pIndex) const;

        GETTER_BOOL(ConstCastSafe, m_objectId.m_isConstCastSafe)

    public:

        RObject() = default;
        ~RObject() = default;
        RObject& operator=(const RObject&) = delete;

        RObject(RObject&&) noexcept;
        RObject& operator=(RObject&&) noexcept;
        
        GETTER_BOOL(Empty, (m_object == std::nullopt || !m_object->has_value()))
        GETTER_BOOL(OnHeap, (m_objectId.m_allocatedOn == alloc::Heap))
        GETTER_BOOL(AllocatedByRtl, (m_objectId.m_allocatedOn == alloc::Heap))
        GETTER(std::size_t, TypeId, m_objectId.m_typeId)
        GETTER_CREF(std::optional<std::any>, Any, m_object)

        template <class _asType>
        bool canViewAs() const;

        template<rtl::alloc _allocOn, rtl::copy _copyTarget = rtl::copy::Auto>
        Return clone() const;

        template<class T, std::enable_if_t<traits::is_unique_ptr_v<T>, int> = 0>
        std::optional<rtl::view<T>> view() const noexcept;

        template<class T, std::enable_if_t<traits::is_shared_ptr_v<T>, int> = 0>
        std::optional<rtl::view<T>> view() const noexcept;

        template<class T, std::enable_if_t<traits::is_not_any_wrapper_v<T>, int> = 0>
        std::optional<rtl::view<T>> view() const noexcept;

        static std::size_t& /*std::atomic<std::size_t>&*/ getInstanceCounter()
        {
            static std::size_t/*std::atomic<std::size_t>*/ instanceCounter = {0};
            return instanceCounter;
        }

        //friends :)
        friend CxxMirror;
        friend detail::RObjExtractor;

        template<class>
        friend struct detail::RObjectUPtr;

        template<class>
        friend struct detail::RObjectBuilder;

        template<class, class ...>
        friend struct function;

        template<class , class, class ...>
        friend struct method;
    };

    struct [[nodiscard]] Return {
        error err;
        RObject robject;
    };
}