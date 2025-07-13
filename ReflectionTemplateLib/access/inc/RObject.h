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

        const rtl::TypeQ m_typeQ;
        const rtl::IsPointer m_isPointer;
        const std::any m_object;
        const std::size_t m_typeId;
        const std::size_t m_typePtrId;
        const std::string m_typeStr;
        const alloc m_allocatedOn;
        const std::vector<ConverterPair>& m_converters;
        const std::shared_ptr<void> m_deallocator;

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
        ~RObject() = default;
        RObject(const RObject&) = default;
        RObject(RObject&& pOther) = default;

        RObject& operator=(const RObject&) = delete;
        RObject& operator=(RObject&& pOther) = delete;

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
        , m_object(std::move(pObjRef))
        , m_typeId(pTypeId)
        , m_typePtrId(pTypePtrId)
        , m_typeStr(pTypeStr)
        , m_allocatedOn(pAllocOn)
        , m_converters(pConversions)
        , m_deallocator(std::move(pDeleter))
    {
    }
}