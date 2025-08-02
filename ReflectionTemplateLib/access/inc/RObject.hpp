#pragma once

#include <optional>
#include <iostream>
#include <cassert>

#include "RObject.h"
#include "ReflectCast.h"

namespace rtl::traits
{
    template<class T>
    constexpr bool is_view_suported() 
    {
        using _T = traits::remove_const_n_ref_n_ptr<T>;
        constexpr bool isReference = std::is_reference_v<T>;
        constexpr bool isWrapperPtr = (std::is_pointer_v<T> && std_wrapper<_T>::type != Wrapper::None);
        constexpr bool isNonConstPtr = (std::is_pointer_v<T> && !std::is_const_v<std::remove_pointer_t<T>>);
        return (!isReference && !isWrapperPtr && !isNonConstPtr);
    }

    template<class T>
    constexpr void validate_view()
    {
        using _T = traits::remove_const_n_ref_n_ptr<T>;
        constexpr bool isReference = std::is_reference_v<T>;
        constexpr bool isWrapperPtr = (std::is_pointer_v<T> && std_wrapper<_T>::type != Wrapper::None);
        constexpr bool isNonConstPtr = (std::is_pointer_v<T> && !std::is_const_v<std::remove_pointer_t<T>>);

        static_assert(!isReference, "explicit reference views are not supported.");
        static_assert(!isWrapperPtr, "viewing standard wrappers (like std::optional or smart pointers) as raw pointers, not supported.");
        static_assert(!isNonConstPtr, "non-const pointers not supported, Only read-only (const) pointer views are supported.");
    }
}


namespace rtl::access
{
    inline RObject::RObject(std::any&& pObject, std::any&& pWrapper, std::shared_ptr<void>&& pDeleter,
                            Cloner&& pCopyCtor, const detail::RObjectId& pRObjectId)
        : m_object(std::forward<std::any>(pObject))
        , m_wrapper(std::forward<std::any>(pWrapper))
        , m_deallocator(std::forward<std::shared_ptr<void>>(pDeleter))
        , m_getClone(std::forward<Cloner>(pCopyCtor))
        , m_objectId(pRObjectId)
    {
    }


    inline RObject::RObject(RObject&& pOther) noexcept
        : m_object(std::move(pOther.m_object))
        , m_wrapper(std::move(pOther.m_wrapper))
        , m_deallocator(std::move(pOther.m_deallocator))
        , m_getClone(std::move(pOther.m_getClone))
        , m_objectId(pOther.m_objectId)
    {
        // Explicitly clear moved-from source
        pOther.m_object.reset();
        pOther.m_wrapper.reset();
        pOther.m_deallocator.reset();
        pOther.m_objectId.reset();
        pOther.m_getClone = nullptr;
    }


    inline bool RObject::isOnHeap() const
    {
        return (m_objectId.m_allocatedOn == alloc::Heap ||
                m_objectId.m_allocatedOn == alloc::Heap_viaReflection);
    }


    template<alloc _allocOn>
    inline std::pair<error, RObject> RObject::clone() const
    {
        static_assert(_allocOn != alloc::None, "Instance cannot be created with 'alloc::None' option.");
        if (isEmpty()) {
            return { error::EmptyRObject, RObject() };
        }
        else if (m_objectId.m_wrapperType == Wrapper::Unique) {
            return { error::ReflectingUniquePtrCopyDisallowed, RObject() };
        }
        else if(!m_getClone){
            return { error::Instantiating_typeNotCopyConstructible, RObject() };
        }

        if constexpr (_allocOn == alloc::Stack)
        {
            if (m_objectId.m_allocatedOn == alloc::Stack) {
                return { error::None, RObject(*this) };
            }
            else if (m_objectId.m_allocatedOn == alloc::Heap_viaReflection) {
                error err = error::None;
                return { err, m_getClone(err, *this, _allocOn) };
            }
            assert(false && "no alloc info.");
        }
        else if constexpr (_allocOn == alloc::Heap)
        {
            error err = error::None;
            return { err, m_getClone(err, *this, _allocOn) };
        }
    }


    template<class T>
    inline const T& RObject::as(bool pGetFromWrapper/* = false*/) const
    {
        if (pGetFromWrapper) {
            return std::any_cast<const T&>(m_wrapper);
        }
        if (m_objectId.m_isPointer == IsPointer::Yes) {

            using _ptrT = std::add_pointer_t<std::add_const_t<T>>;
            return *(std::any_cast<_ptrT>(m_object));
        }
        return std::any_cast<const T&>(m_object);
    }


    inline std::size_t RObject::getConverterIndex(const std::size_t pToTypeId) const
    {
        if (!isEmpty())
        {
            for (std::size_t index = 0; index < m_objectId.m_converters.size(); index++) {
                if (m_objectId.m_converters[index].first == pToTypeId) {
                    return index;
                }
            }
        }
        return index_none;
    }


    template<class T>
    inline bool RObject::canViewAs() const
    {
        if (!traits::is_view_suported<T>()) {
            return false;
        }

        using _T = traits::remove_const_n_ref_n_ptr<T>;
        if constexpr (std::is_pointer_v<T> && std::is_const_v<std::remove_pointer_t<T>>)
        {
            if (m_objectId.m_ptrTypeId == detail::TypeId<_T*>::get()) {
                return true;
            }
        }
        else if constexpr (traits::std_wrapper<_T>::type != Wrapper::None)
        {
            if (m_objectId.m_wrapperTypeId == traits::std_wrapper<_T>::id()) {
                return true;
            }
        }

        const auto& typeId = detail::TypeId<T>::get();
        return (typeId == m_objectId.m_typeId || getConverterIndex(typeId) != index_none);
    }


    template <class _asType>
    inline std::optional<view<_asType>> RObject::view() const
    {
        traits::validate_view<_asType>();

        std::size_t toTypeId = detail::TypeId<_asType>::get();
        if (toTypeId == m_objectId.m_typeId) {
            const auto& viewRef = as<_asType>();
            return std::optional<rtl::view<_asType>>(std::in_place, viewRef);
        }

        using _T = traits::remove_const_n_reference<_asType>;
        if constexpr (std::is_pointer_v<_T>)
        {
            using T = traits::remove_const_n_ref_n_ptr<_asType>;
            std::size_t typePtrId = detail::TypeId<T*>::get();
            if (typePtrId == m_objectId.m_ptrTypeId) {
                auto& viewRef = as<T>();
                return std::optional<rtl::view<const T*>>(&viewRef);
            }
        }
        else if constexpr (traits::std_wrapper<_T>::type != Wrapper::None)
        {
            if (traits::std_wrapper<_T>::id() == m_objectId.m_wrapperTypeId) {
                const _asType& viewRef = as<_asType>(true);
                return std::optional<rtl::view<_asType>>(viewRef);
            }
        }

        std::size_t index = getConverterIndex(toTypeId);
        if (index != index_none)
        {
            ConversionKind conversionKind = ConversionKind::NotDefined;
            const std::any& viewObj = m_objectId.m_converters[index].second(m_object, m_objectId.m_isPointer, conversionKind);
            if (viewObj.has_value())  //if true, 'conversionKind' can only be 'ConversionKind::ByRef/ByValue'
            {
                const _asType& viewRef = std::any_cast<const _asType&>(viewObj);
                if (conversionKind == ConversionKind::ByRef) {
                    return std::optional<rtl::view<_asType>>(std::in_place, viewRef);
                }
                else /*if (ConversionKind == ConversionKind::ByValue)*/ {
                    return std::optional<rtl::view<_asType>>(std::in_place, _asType(viewRef));
                }
            }
            else {/* This ought to be a dead code block, still..TODO: handle ConversionKind::NoDefined/BadAnyCast */}
        }
        return std::nullopt;
    }
}


//static functions.
namespace rtl::access
{
    template<class T>
    inline std::shared_ptr<void> RObject::getDeallocator(T* pObject)
    {
        m_rtlOwnedRObjectInstanceCount.fetch_add(1);
        auto deleter = [pObject](void*) {
            delete pObject;
            m_rtlOwnedRObjectInstanceCount.fetch_sub(1);
            assert(m_rtlOwnedRObjectInstanceCount >= 0 && "instance count can't be less than zero. memory leak alert!");
        };
        static char dummy;
        return std::shared_ptr<void>(static_cast<void*>(&dummy), deleter);
    }


    template <class T, alloc _allocOn>
    inline RObject RObject::create(T&& pVal)
    {
        using _T = traits::base_t<T>;
        const detail::RObjectId& robjId = detail::RObjectId::create<T, _allocOn>();
        if constexpr (_allocOn == alloc::Heap_viaReflection) {
            auto&& deleter = getDeallocator(static_cast<const _T*>(pVal));
            return RObject(std::any(static_cast<const _T*>(pVal)), std::any(), std::move(deleter), getCloner<_T>(), robjId);
        }
        else if constexpr (std::is_pointer_v<traits::remove_const_n_reference<T>>) {
            return RObject(std::any(static_cast<const _T*>(pVal)), std::any(), nullptr, getCloner<_T>(), robjId);
        }
        else {
            static_assert(std::is_copy_constructible_v<_T>, "T must be copy-constructible (std::any requires this).");
            return RObject(std::any(std::forward<T>(pVal)), std::any(), nullptr, getCloner<_T>(), robjId);
        }
    }


    template<class W>
    inline RObject RObject::createWithWrapper(W&& pWrapper)
    {
        using _W = traits::std_wrapper<traits::remove_const_n_ref_n_ptr<W>>;
        using _T = _W::baseT;
        const detail::RObjectId& robjId = detail::RObjectId::createForWrapper<W>();

        if constexpr (_W::type == Wrapper::Unique) {
            auto rawPtr = static_cast<const _T*>(pWrapper.get());
            return RObject(std::any(rawPtr), std::any(std::unique_ptr<_T>(std::move(pWrapper))), nullptr, nullptr, robjId);
        }
        else if constexpr (_W::type == Wrapper::Weak || _W::type == Wrapper::Shared) {
            auto rawPtr = static_cast<const _T*>(pWrapper.get());
            return RObject(std::any(rawPtr), std::any(std::forward<W>(pWrapper)), nullptr, getCloner<_T>(), robjId);
        }
        else {
            auto obj = pWrapper.value();
            return RObject(std::any(obj), std::any(std::forward<W>(pWrapper)), nullptr, getCloner<_T>(), robjId);
        }
    }


    template<class T>
    inline RObject::Cloner RObject::getCloner()
    {
        return [](error& pError, const RObject& pOther, alloc pAllocOn)-> RObject
        {
            if constexpr (!std::is_copy_constructible_v<T>) {
                pError = error::Instantiating_typeNotCopyConstructible;
                return access::RObject();
            }
            else {
                pError = error::None;
                const auto& srcObj = pOther.view<T>()->get();
                if (pAllocOn == alloc::Stack) {
                    return detail::RObjectBuilder::template build<T, alloc::Stack>(T(srcObj));
                }
                else if (pAllocOn == alloc::Heap) {
                    return detail::RObjectBuilder::template build<const T*, alloc::Heap_viaReflection>(new T(srcObj));
                }
                assert(false && "pAllocOn must never be anything else other than alloc::Stack/Heap here.");
            }
            return RObject(); //dead code. compiler warning ommited.
        };
    }
}