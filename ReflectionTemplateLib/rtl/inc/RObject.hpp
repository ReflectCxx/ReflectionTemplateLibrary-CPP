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

#include <inc/view.hpp>
#include <inc/RObject.h>
#include <detail/inc/RObjectUPtr.h>
#include <detail/inc/ReflectCast.h>
#include <detail/inc/RObjExtracter.h>
#include <detail/inc/RObjectBuilder.h>

namespace rtl
{
    ForceInline RObject::RObject(std::any&& pObject, const detail::RObjectId& pRObjId) noexcept
        : m_object(std::in_place, std::move(pObject))
        , m_objectId(pRObjId)
    { }

    inline RObject::RObject(RObject&& pOther) noexcept
        : m_object(std::move(pOther.m_object))
        , m_objectId(pOther.m_objectId)
    {
        // Explicitly clear moved-from source
        pOther.m_object = std::nullopt;
        pOther.m_objectId = {};
    }

    inline RObject& RObject::operator=(RObject&& pOther) noexcept
    {
        if (this == &pOther) {
            return *this;
        }

        m_object = std::move(pOther.m_object);
        m_objectId = pOther.m_objectId;

        // Explicitly clear moved-from source
        pOther.m_object = std::nullopt;
        pOther.m_objectId = {};
        return *this;
    }
    

    inline std::size_t RObject::getConverterIndex(const std::size_t pToTypeId) const
    {
        if (m_objectId.m_containsAs != detail::EntityKind::None) {
            for (std::size_t index = 0; index < m_objectId.m_converters->size(); index++) {
                if ((*m_objectId.m_converters)[index].first == pToTypeId) {
                    return index;
                }
            }
        }
        return index_none;
    }


    template<class T>
    inline bool RObject::canViewAs() const
    {
        if (isEmpty()) {
            return false;
        }

        if constexpr (traits::is_bare_type<T>()) {
            if constexpr (traits::std_wrapper<T>::type != detail::Wrapper::None) {
                if (m_objectId.m_wrapperTypeId == traits::std_wrapper<T>::id()) {
                    return true;
                }
            }
            const auto& typeId = traits::uid<T>::value;
            return (m_objectId.m_typeId == typeId || getConverterIndex(typeId) != index_none);
        }
    }


    template<class T>
    inline std::optional<rtl::view<T>> RObject::performConversion(const std::size_t pIndex) const
    {
        detail::EntityKind newKind = detail::EntityKind::None;
        const traits::Converter& convert = (*m_objectId.m_converters)[pIndex].second;
        const std::any& viewObj = convert(m_object.value(), m_objectId.m_containsAs, newKind);
        const T* viewRef = detail::RObjExtractor::getPointer<T>(viewObj, newKind);

        if (viewRef != nullptr && newKind == detail::EntityKind::Ptr) {
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
    ForceInline std::optional<rtl::view<T>> RObject::view() const noexcept
    {
        if (isEmpty()) {
            return std::nullopt;
        }

        if constexpr (traits::is_bare_type<T>())
        {
            if (traits::uid<T>::value == m_objectId.m_wrapperTypeId) [[likely]]
            {
                using U = detail::RObjectUPtr<typename traits::std_wrapper<T>::value_type>;
                const U& uptrRef = *(detail::RObjExtractor{ this }.getWrapper<T>());
                return std::optional<rtl::view<T>>(std::in_place, static_cast<const U&>(uptrRef));
            }
        }
        return std::nullopt;
    }


    template <class T, std::enable_if_t<traits::is_shared_ptr_v<T>, int>>
    ForceInline std::optional<rtl::view<T>> RObject::view() const noexcept
    {
        if (isEmpty()) {
            return std::nullopt;
        }

        if constexpr (traits::is_bare_type<T>())
        {
            if (traits::uid<T>::value == m_objectId.m_wrapperTypeId) [[likely]]
            {
                const T* sptrRef = detail::RObjExtractor{ this }.getWrapper<T>();
                if (sptrRef != nullptr) {
                    return std::optional<rtl::view<T>>(std::in_place, const_cast<T&>(*sptrRef));
                }
            }
        }
        return std::nullopt;
    }


    template <class T, std::enable_if_t<traits::is_not_any_wrapper_v<T>, int>>
    ForceInline std::optional<rtl::view<T>> RObject::view() const noexcept
    {
        if (isEmpty()) {
            return std::nullopt;
        }

        if constexpr (traits::is_bare_type<T>())
        {
            const std::size_t asTypeId = traits::uid<T>::value;
            if (asTypeId == m_objectId.m_typeId) [[likely]]
            {
                const T* valRef = detail::RObjExtractor{ this }.getPointer<T>();
                if (valRef != nullptr) {
                    return std::optional<rtl::view<T>>(std::in_place, *valRef);
                }
            }
            else
            {
                const std::size_t index = getConverterIndex(asTypeId);
                if (index != index_none) {
                    return performConversion<T>(index);
                }
            }
        }
        return std::nullopt;
    }
}



namespace rtl 
{
    template<>
    inline Return RObject::createCopy<alloc::Heap, detail::EntityKind::Value>() const
    {
        return m_objectId.m_clonerFn(alloc::Heap, *this);
    }


    template<>
    inline Return RObject::createCopy<alloc::Stack, detail::EntityKind::Value>() const
    {
        return m_objectId.m_clonerFn(alloc::Stack, *this);
    }


    template<>
    inline Return RObject::createCopy<alloc::Heap, detail::EntityKind::Wrapper>() const
    {
        return { error::StlWrapperHeapAllocForbidden, RObject{} };
    }


    template<>
    inline Return RObject::createCopy<alloc::Stack, detail::EntityKind::Wrapper>() const
    {
        if (m_objectId.m_wrapperType == detail::Wrapper::None) {
            return { error::NotWrapperType, RObject{} };
        }
        else if (m_objectId.m_wrapperType == detail::Wrapper::Unique) 
        {
            return { error::TypeNotCopyConstructible, RObject{} };
        }
        else {
            return { error::None, RObject(*this) };
        }
    }


    template<alloc _allocOn, copy _copyTarget>
    inline Return RObject::clone() const
    {
        if (isEmpty()) {
            return { error::EmptyRObject, RObject{} };
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
            if (m_objectId.m_wrapperType != detail::Wrapper::None && !isAllocatedByRtl()) {
                return createCopy<_allocOn, detail::EntityKind::Wrapper>();
            }
            else {
                return createCopy<_allocOn, detail::EntityKind::Value>();
            }
        }
    }
}