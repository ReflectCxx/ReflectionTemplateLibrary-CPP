#pragma once

#include <any>
#include <array>
#include <memory>
#include <string>
#include <optional>
#include <functional>

#include "view.h"
#include "Constants.h"


namespace rtl::access
{
    class Function;

    using ConverterPair = std::pair< std::size_t, Converter >;

    //Reflecting the object within.
    class RObject
    {
        const rtl::TypeQ m_typeQ;
        const rtl::IsPointer m_isPointer;
        const std::any m_object;
        const std::size_t m_typeId;
        const std::size_t m_typePtrId;
        const std::string m_typeStr;
        const alloc m_allocatedOn;
        const std::vector<ConverterPair>& m_converters;
        const std::shared_ptr<std::size_t> m_deallocator;

        explicit RObject(std::any&& pObjRef, std::size_t pTypeId, std::size_t pTypePtrId, std::string pTypeStr,
                         const rtl::TypeQ& pTypeQ, const rtl::IsPointer pIsPtr, const std::vector<ConverterPair>& pConversions);

        //explicit RObject(std::any pObjectPtr, const Function& pDctor);

        template<class T>
        const T& as() const;

        const std::size_t getConverterIndex(const std::size_t& pToTypeId) const;

    public:

        RObject();
        ~RObject() = default;
        RObject(const RObject&) = default;
        RObject(RObject&& pOther) = default;

        RObject& operator=(const RObject&) = delete;
        RObject& operator=(RObject&& pOther) = delete;

        GETTER(std::string, TypeStr, m_typeStr)
        GETTER_BOOL(Empty, (m_object.has_value() == false))

        template <class _asType>
        const bool canReflectAs() const;

        template<class _asType>
        std::optional<rtl::view<_asType>> view() const;

        template <class T>
        static RObject create(T&& pVal, const rtl::TypeQ& pTypeQ = rtl::TypeQ::Mute);
    };
}