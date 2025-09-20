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
#include "RObjectId.h"

#include "rtl_typeid.h"
#include "rtl_traits.h"
#include "forward_decls.h"

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
        const std::vector<traits::ConverterPair>* m_converters = nullptr;

        RObject(const RObject&) = default;
        RObject(std::any&& pObject, detail::RObjectId&& pRObjId,
                const std::vector<traits::ConverterPair>* pConverters) noexcept;

        std::size_t getConverterIndex(const std::size_t pToTypeId) const;

        template<rtl::alloc _allocOn, detail::EntityKind _entityKind>
        Return createCopy() const;

        template<class T>
        std::optional<rtl::view<T>> performConversion(const std::size_t pIndex) const;

    public:

        RObject() = default;
        ~RObject() = default;
        RObject& operator=(const RObject&) = delete;

        RObject(RObject&&) noexcept;
        RObject& operator=(RObject&&) noexcept;
        
        GETTER_BOOL(Empty, (m_object == std::nullopt))
        GETTER_BOOL(OnHeap, (m_objectId.m_allocatedOn == alloc::Heap))
        GETTER_BOOL(AllocatedByRtl, (m_objectId.m_allocatedOn == alloc::Heap))
        GETTER(std::size_t, TypeId, m_objectId.m_typeId)
        GETTER_CREF(std::optional<std::any>, Any, m_object)

    /*  Reflection Const Semantics:
    *   - All reflected objects default to mutable internally; API enforces logical constness.
    *   - RTL may 'const_cast' its own objects(allocated via RTL) but preserves logical constness.
    *   - External objects (e.g. returned via Reflected call) keep original qualifier; if const, then const_cast is unsafe.
    */  GETTER_BOOL(ConstCastSafe, m_objectId.m_isConstCastSafe)

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

        static std::atomic<std::size_t>& getInstanceCounter();

        //friends :)
        friend CxxMirror;
        friend detail::RObjExtractor;

        template<class T>
        friend struct detail::RObjectUPtr;

        template<class T>
        friend struct detail::RObjectBuilder;
    };

    struct [[nodiscard]] Return {
        error err;
        RObject rObject;
    };
}