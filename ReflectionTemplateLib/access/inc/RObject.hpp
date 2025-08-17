/*****************************************************************
 *                                                               *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP  *
 *  Copyright (c) 2025 Neeraj Singh (reflectcxx@outlook.com)     *
 *  SPDX-License-Identifier: MIT                                 *
 *                                                               *
 *****************************************************************/


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


    template<>
    inline std::pair<error, RObject> RObject::createCopy<alloc::Heap, entity::Value>() const
    {
        error err = error::None;
        return { err, m_getClone(err, *this, alloc::Heap, entity::Value) };
    }


    template<>
    inline std::pair<error, RObject> RObject::createCopy<alloc::Stack, entity::Wrapper>() const
    {
        return { error::None, RObject(*this) };
    }


    template<>
    inline std::pair<error, RObject> RObject::createCopy<alloc::Stack, entity::Value>() const
    {
        error err = error::None;
        return { err, m_getClone(err, *this, alloc::Stack, entity::Value) };
    }
    

    template<class T>
    inline std::optional<rtl::view<T>> RObject::performConversion(const std::size_t pIndex) const
    {
        entity newKind = entity::None;
        const traits::Converter& convert = m_objectId.m_converters[pIndex].second;
        const std::any& viewObj = convert(m_object, m_objectId.m_containsAs, newKind);
        const T* viewRef = detail::RObjExtractor::getPointer<T>(viewObj, newKind);
        
        if (viewRef != nullptr && newKind == entity::Pointer) {
            return std::optional<rtl::view<T>>(std::in_place, *viewRef);
        }
        else if (viewRef != nullptr && newKind == entity::Value) {
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


    template<alloc _allocOn, entity _entityKind>
    inline std::pair<error, RObject> RObject::clone() const
    {
        static_assert(_entityKind != entity::None, "Invalid rtl::entity. use rtl::entity::Value or rtl::entity::Wrapper");

        if (isEmpty()) {
            return { error::EmptyRObject, RObject() };
        }
        if constexpr (_allocOn == alloc::Heap && _entityKind == entity::Wrapper) {
            static_assert(false, "Heap allocation forbidden for STL-Wrappers (e.g. smart pointers/optionals/reference_wrappers).");
        }
        else if constexpr (_allocOn == alloc::Stack && _entityKind == entity::Wrapper) 
        {
            if (m_objectId.m_wrapperType == detail::Wrapper::Unique) {
                return { error::TypeNotCopyConstructible, RObject() };
            }
            else if (m_objectId.m_wrapperType == detail::Wrapper::None) {
                return { error::NotWrapperType, RObject() };
            }
            else {
                return createCopy<_allocOn, _entityKind>();
            }
        }
        else if constexpr (_allocOn == alloc::Stack || _allocOn == alloc::Heap)
        {
            if (m_objectId.m_wrapperType != detail::Wrapper::None) 
            {
                if (_allocOn == alloc::Stack) {
                    if (m_objectId.m_wrapperType == detail::Wrapper::Unique)
                    {
                        if (isAllocatedByRtl()) {
                            return createCopy<_allocOn, entity::Value>();
                        }
                        else {
                            return { error::TypeNotCopyConstructible, RObject() };
                        }
                    }
                    else return createCopy<_allocOn, _entityKind>();
                }
                else {
                    if (isAllocatedByRtl()) {
                        return createCopy<_allocOn, entity::Value>();
                    }
                    return { error::StlWrapperHeapAllocForbidden, RObject() };
                }
            }
            else return createCopy<_allocOn, _entityKind>();
        }
        else
        {
            static_assert(false, "Invalid allocation type (alloc::None) used for cloning.");
            return { error::EmptyRObject, RObject() };
        }
    }
}