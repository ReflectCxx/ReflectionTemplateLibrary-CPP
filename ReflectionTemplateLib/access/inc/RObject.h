#pragma once

#include <memory>

#include "view.h"
#include "TypeId.h"
#include "Constants.h"
#include "rtl_traits.h"

namespace rtl::detail {
    class RObjectBuilder;
}

namespace rtl::access
{
    class Function;

    using ConverterPair = std::pair< std::size_t, Converter >;

    //Reflecting the object within.
    class RObject
    {
        static std::vector<rtl::access::ConverterPair> m_conversions;

        rtl::IsPointer m_isPointer;
        std::size_t m_typeId;
        std::size_t m_ptrTypeId;
        std::size_t m_wrapperTypeId;
        std::string m_typeStr;
        alloc m_allocatedOn;
        const std::vector<ConverterPair>& m_converters;

        std::any m_object;
        std::any m_wrapper;
        std::shared_ptr<void> m_deallocator;

        explicit RObject(std::any&& pObject, std::any&& pWrapper, std::size_t pTypeId, std::size_t pPtrTypeId, std::size_t pWrapperTypeId,
                         const std::string& pTypeStr, rtl::IsPointer pIsPtr, rtl::alloc pAllocOn, std::shared_ptr<void>&& pDeleter,
                         const std::vector<ConverterPair>& pConversions);

        template<class T>
        const T& as(bool pGetFromWrapper = false) const;

        std::size_t getConverterIndex(const std::size_t pToTypeId) const;

    protected:

        template <class T>
        static RObject create(T&& pVal, std::shared_ptr<void>&& pDeleter, rtl::alloc pAllocOn);

        template <class W>
        static RObject create(W&& pWrapper, rtl::alloc pAllocOn);

    public:

        explicit RObject();
        RObject(RObject&&) noexcept;

        ~RObject() = default;
        RObject(const RObject&) = default;

        RObject& operator=(RObject&&) = delete;
        RObject& operator=(const RObject&) = delete;

        GETTER(std::any,,m_object)
        GETTER(std::size_t, TypeId, m_typeId);

        //checks if object constructed via reflection on heap or stack.
        GETTER_BOOL(OnHeap, (m_allocatedOn == rtl::alloc::Heap));
        GETTER_BOOL(Empty, (m_object.has_value() == false))

        template <class _asType>
        bool canViewAs() const;

        //Returns std::nullopt if type not viewable. Use canViewAs<T>() to check.
        template<class _asType>
        std::optional<rtl::view<_asType>> view() const;

        friend rtl::detail::RObjectBuilder;
    };


    inline RObject::RObject()
        : m_isPointer(rtl::IsPointer::No)
        , m_typeId(rtl::detail::TypeId<>::None)
        , m_ptrTypeId(rtl::detail::TypeId<>::None)
        , m_wrapperTypeId(rtl::detail::TypeId<>::None)
        , m_allocatedOn(rtl::alloc::None)
        , m_converters(m_conversions)
        , m_deallocator(nullptr)
    {
    }


    inline RObject::RObject(std::any&& pObject, std::any&& pWrapper, std::size_t pTypeId, std::size_t pPtrTypeId, std::size_t pWrapperTypeId,
                            const std::string& pTypeStr, rtl::IsPointer pIsPtr, rtl::alloc pAllocOn, std::shared_ptr<void>&& pDeleter,
                            const std::vector<ConverterPair>& pConversions)
        : m_isPointer(pIsPtr)
        , m_typeId(pTypeId)
        , m_ptrTypeId(pPtrTypeId)
        , m_wrapperTypeId(pWrapperTypeId)
        , m_typeStr(pTypeStr)
        , m_allocatedOn(pAllocOn)
        , m_converters(pConversions)
        , m_object(std::forward<std::any>(pObject))
        , m_wrapper(std::forward<std::any>(pWrapper))
        , m_deallocator(std::forward<std::shared_ptr<void>>(pDeleter))
    {
    }


    inline RObject::RObject(RObject&& pOther) noexcept
        : m_isPointer(pOther.m_isPointer)
        , m_typeId(pOther.m_typeId)
        , m_ptrTypeId(pOther.m_ptrTypeId)
        , m_wrapperTypeId(pOther.m_wrapperTypeId)
        , m_typeStr(pOther.m_typeStr)
        , m_allocatedOn(pOther.m_allocatedOn)
        , m_converters(pOther.m_converters)
        , m_object(std::move(pOther.m_object))
        , m_wrapper(std::move(pOther.m_wrapper))
        , m_deallocator(std::move(pOther.m_deallocator))
    {
        pOther.m_isPointer = rtl::IsPointer::No;
        pOther.m_typeId = rtl::detail::TypeId<>::None;
        pOther.m_ptrTypeId = rtl::detail::TypeId<>::None;
        pOther.m_wrapperTypeId = rtl::detail::TypeId<>::None;
        pOther.m_allocatedOn = alloc::None;
        // Explicitly clear moved-from source
        pOther.m_object.reset();
        pOther.m_wrapper.reset();
        pOther.m_deallocator.reset();
        pOther.m_typeStr.clear();
    }
}