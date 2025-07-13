#pragma once

#include <memory>

#include "view.h"
#include "TypeId.h"
#include "Constants.h"

namespace rtl::access
{
    class Function;

    using ConverterPair = std::pair< std::size_t, Converter >;

    //Reflecting the object within.
    class RObject
    {
        static std::vector<rtl::access::ConverterPair> m_conversions;

        rtl::TypeQ m_typeQ;
        rtl::IsPointer m_isPointer;
        std::size_t m_typeId;
        std::size_t m_typePtrId;
        std::string m_typeStr;
        alloc m_allocatedOn;
        const std::vector<ConverterPair>& m_converters;

        std::any m_object;
        std::shared_ptr<void> m_deallocator;

        explicit RObject(std::any&& pObjRef, std::size_t pTypeId, std::size_t pTypePtrId, std::string pTypeStr,
                         const rtl::TypeQ& pTypeQ, const rtl::IsPointer pIsPtr, const rtl::alloc& pAllocOn,
                         std::shared_ptr<void>&& pDeleter, const std::vector<ConverterPair>& pConversions);

        template<class T>
        const T& as() const;

        const std::size_t getConverterIndex(const std::size_t& pToTypeId) const;

    protected:

        template <class T>
        static RObject create(T&& pVal, std::shared_ptr<void>&& pDeleter,
                              const rtl::TypeQ& pTypeQ, const rtl::alloc& pAllocOn);
    public:

        explicit RObject();
        RObject(RObject&&) noexcept;

        ~RObject() = default;
        RObject(const RObject&) = default;

        RObject& operator=(RObject&&) = delete;
        RObject& operator=(const RObject&) = delete;

        GETTER(std::any,,m_object)
        GETTER(std::size_t, TypeId, m_typeId);
        GETTER(rtl::TypeQ, Qualifier, m_typeQ);

        //checks if object constructed via reflection on heap or stack.
        GETTER_BOOL(OnHeap, (m_allocatedOn == rtl::alloc::Heap));
        GETTER_BOOL(Empty, (m_object.has_value() == false))

        template <class _asType>
        const bool canViewAs() const;

        //Returns std::nullopt if type not viewable. Use canViewAs<T>() to check.
        template<class _asType>
        std::optional<rtl::view<_asType>> view() const;
    };


    inline RObject::RObject()
        : m_typeQ(rtl::TypeQ::None)
        , m_isPointer(rtl::IsPointer::No)
        , m_typeId(rtl::detail::TypeId<>::None)
        , m_typePtrId(rtl::detail::TypeId<>::None)
        , m_allocatedOn(rtl::alloc::None)
        , m_converters(m_conversions)
        , m_deallocator(nullptr)
    {
    }


    inline RObject::RObject(std::any&& pObjRef, std::size_t pTypeId, std::size_t pTypePtrId, std::string pTypeStr,
                            const rtl::TypeQ& pTypeQ, const rtl::IsPointer pIsPtr, const rtl::alloc& pAllocOn, 
                            std::shared_ptr<void>&& pDeleter, const std::vector<ConverterPair>& pConversions)
        : m_typeQ(pTypeQ)
        , m_isPointer(pIsPtr)
        , m_typeId(pTypeId)
        , m_typePtrId(pTypePtrId)
        , m_typeStr(pTypeStr)
        , m_allocatedOn(pAllocOn)
        , m_converters(pConversions)
        , m_object(std::forward<std::any>(pObjRef))
        , m_deallocator(std::forward<std::shared_ptr<void>>(pDeleter))
    {
    }


    inline RObject::RObject(RObject&& pOther) noexcept
        : m_typeQ(pOther.m_typeQ)
        , m_isPointer(pOther.m_isPointer)
        , m_typeId(pOther.m_typeId)
        , m_typePtrId(pOther.m_typePtrId)
        , m_typeStr(pOther.m_typeStr)
        , m_allocatedOn(pOther.m_allocatedOn)
        , m_converters(pOther.m_converters)
        , m_object(std::move(pOther.m_object))
        , m_deallocator(std::move(pOther.m_deallocator))
    {
        pOther.m_typeQ = rtl::TypeQ::None;
        pOther.m_isPointer = rtl::IsPointer::No;
        pOther.m_typeId = rtl::detail::TypeId<>::None;
        pOther.m_typePtrId = rtl::detail::TypeId<>::None;
        pOther.m_typeStr = "";
        pOther.m_allocatedOn = alloc::None;
        // Explicitly clear moved-from source
        pOther.m_object.reset();      // Clears std::any
        pOther.m_deallocator.reset();   // Clears shared_ptr
    }
}