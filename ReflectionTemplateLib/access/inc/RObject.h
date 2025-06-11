#pragma once

#include <any>
#include <string>
#include <optional>
#include <functional>

#include "Constants.h"
#include "cref_view.h"


namespace rtl::access
{
    using ConverterPair = std::pair< std::size_t, Converter >;

    //Reflecting the object within.
    class RObject
    {
        const rtl::IsPointer m_isPointer;
        const std::any m_object;
        const std::size_t m_typeId;
        const std::size_t m_typePtrId;
        const std::string m_typeStr;
        const alloc m_allocatedOn;
        const std::vector<ConverterPair>& m_converters;

        RObject(std::any&& pObjRef, std::size_t pTypeId, std::size_t pTypePtrId, std::string pTypeStr,
                const std::vector<ConverterPair>& pConversions, const rtl::IsPointer pIsPtr,
                alloc pAllocOn = rtl::alloc::None);

        template<class T>
        const T& as() const;

        template <class T>
        static RObject create(T&& pVal);

        const std::size_t getConverterIndex(const std::size_t& pToTypeId) const;

    public:

        ~RObject() = default;
        RObject(const RObject&) = default;
        RObject(RObject&& pOther) = default;

        RObject& operator=(const RObject&) = delete;
        RObject& operator=(RObject&& pOther) = delete;

        GETTER(std::string, TypeStr, m_typeStr)

        template <class _asType>
        const bool canReflectAs() const;

        template<class _asType>
        std::optional<rtl::cref_view<_asType>> view() const;

        template <class T>
        static RObject reflect(T&& pVal);
    };
}