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

#include <optional>
#include <iostream>
#include <cassert>

#include "view.hpp"
#include "RObject.h"
#include "RObjectUPtr.h"
#include "ReflectCast.h"
#include "RObjExtracter.h"
#include "RObjectBuilder.h"

namespace rtl::access
{
    inline RObject::RObject(std::any&& pObject, Cloner&& pCloner, const detail::RObjectId& pRObjectId)
        : m_getClone(std::forward<Cloner>(pCloner))
        , m_object(std::forward<std::any>(pObject))
        , m_objectId(pRObjectId)
    { }

    inline RObject::RObject(RObject&& pOther) noexcept
        : m_object(std::move(pOther.m_object))
        , m_getClone(std::move(pOther.m_getClone))
        , m_objectId(pOther.m_objectId)
    {
        // Explicitly clear moved-from source
        pOther.m_object.reset();
        pOther.m_objectId.reset();
        pOther.m_getClone = nullptr;
    }

    inline std::atomic<std::size_t>& RObject::getInstanceCounter()
    {
        static std::atomic<std::size_t> instanceCounter = {0};
        return instanceCounter;
    }

    template<class T>
    inline bool RObject::canViewAs() const
    {
        if constexpr (traits::is_bare_type<T>()) {
            if constexpr (traits::std_wrapper<T>::type != detail::Wrapper::None) {
                if (m_objectId.m_wrapperTypeId == traits::std_wrapper<T>::id()) {
                    return true;
                }
            }
            const auto& typeId = detail::TypeId<T>::get();
            return (m_objectId.m_typeId == typeId || m_objectId.getConverterIndex(typeId) != index_none);
        }
    }


    template<class T>
    inline std::optional<rtl::view<T>> RObject::performConversion(const std::size_t pIndex) const
    {
        detail::EntityKind newKind = detail::EntityKind::None;
        const traits::Converter& convert = m_objectId.m_converters[pIndex].second;
        const std::any& viewObj = convert(m_object, m_objectId.m_containsAs, newKind);
        const T* viewRef = detail::RObjExtractor::getPointer<T>(viewObj, newKind);

        if (viewRef != nullptr && newKind == detail::EntityKind::Ref) {
            return std::optional<rtl::view<T>>(std::in_place, *viewRef);
        }
        else if (viewRef != nullptr && newKind == detail::EntityKind::Value) {
            if constexpr (std::is_copy_constructible_v<T>) {
                return std::optional<rtl::view<T>>(std::in_place, T(*viewRef));
            }
        }
        return std::nullopt;
    }


    template <class T, std::enable_if_t<traits::is_unique_ptr_v<T>, int>>
    std::optional<rtl::view<T>> RObject::view() const
    {
        if constexpr (traits::is_bare_type<T>())
        {
            if (detail::TypeId<T>::get() == m_objectId.m_wrapperTypeId)
            {
                using U = detail::RObjectUPtr<typename traits::std_wrapper<T>::value_type>;
                const U& uptrRef = *(detail::RObjExtractor(this).getWrapper<T>());
                return std::optional<rtl::view<T>>(std::in_place, static_cast<const U&>(uptrRef));
            }
        }
        return std::nullopt;
    }


    template <class T, std::enable_if_t<traits::is_shared_ptr_v<T>, int>>
    std::optional<rtl::view<T>> RObject::view() const
    {
        if constexpr (traits::is_bare_type<T>())
        {
            if (detail::TypeId<T>::get() == m_objectId.m_wrapperTypeId)
            {
                const T& sptrRef = *(detail::RObjExtractor(this).getWrapper<T>());
                return std::optional<rtl::view<T>>(std::in_place, const_cast<T&>(sptrRef));
            }
        }
        return std::nullopt;
    }


    template <class T, std::enable_if_t<traits::is_not_any_wrapper_v<T>, int>>
    inline std::optional<rtl::view<T>> RObject::view() const
    {
        if constexpr (traits::is_bare_type<T>())
        {
            const std::size_t asTypeId = detail::TypeId<T>::get();
            if (asTypeId == m_objectId.m_typeId)
            {
                const T* valRef = detail::RObjExtractor(this).getPointer<T>();
                if (valRef != nullptr) {
                    return std::optional<rtl::view<T>>(std::in_place, *valRef);
                }
            }
            else
            {
                const std::size_t index = m_objectId.getConverterIndex(asTypeId);
                if (index != index_none) {
                    return performConversion<T>(index);
                }
            }
        }
        return std::nullopt;
    }
}



namespace rtl::access 
{
    template<>
    inline std::pair<error, RObject> RObject::createCopy<alloc::Heap, detail::EntityKind::Value>() const
    {
        error err = error::None;
        return { err, m_getClone(err, *this, alloc::Heap) };
    }


    template<>
    inline std::pair<error, RObject> RObject::createCopy<alloc::Stack, detail::EntityKind::Value>() const
    {
        error err = error::None;
        return { err, m_getClone(err, *this, alloc::Stack) };
    }


    template<>
    inline std::pair<error, RObject> RObject::createCopy<alloc::Heap, detail::EntityKind::Wrapper>() const
    {
        return { error::StlWrapperHeapAllocForbidden, RObject() };
    }


    template<>
    inline std::pair<error, RObject> RObject::createCopy<alloc::Stack, detail::EntityKind::Wrapper>() const
    {
        if (m_objectId.m_wrapperType == detail::Wrapper::None) {
            return { error::NotWrapperType, RObject() };
        }
        else if (m_objectId.m_wrapperType == detail::Wrapper::Unique) 
        {
            return { error::TypeNotCopyConstructible, RObject() };
        }
        else {
            return { error::None, RObject(*this) };
        }
    }


    template<alloc _allocOn, copy _copyTarget>
    inline std::pair<error, RObject> RObject::clone() const
    {
        if (isEmpty()) {
            return { error::EmptyRObject, RObject() };
        }
        if constexpr (_copyTarget == copy::Value) {
            return createCopy<_allocOn, detail::EntityKind::Value>();
        }
        else if constexpr (_copyTarget == copy::Wrapper) {
            return createCopy<_allocOn, detail::EntityKind::Wrapper>();
        }
        else if constexpr (_copyTarget == copy::Auto) {
            // RTL wraps the objects allocated on heap in 'std::unique_ptr'. Which by default is transparent to RTL itself.
            // 'std::unique_ptr' acquired via any other source, (e.g. return value) are not transparent. hence the second condition.
            if (m_objectId.m_wrapperType != detail::Wrapper::None && !isAllocatedByRtl()) 
            {
                return createCopy<_allocOn, detail::EntityKind::Wrapper>();
            }
            else {
                return createCopy<_allocOn, detail::EntityKind::Value>();
            }
        }
    }
}
