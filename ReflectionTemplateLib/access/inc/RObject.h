#pragma once

#include <any>
#include <string>
#include <optional>
#include <functional>

#include "Constants.h"
#include "cref_view.h"

namespace rtl::detail 
{
    template<class _fromType>
    class RObjectConverter;
}


namespace rtl::access
{
    using Converter = std::pair<std::size_t, std::function< std::any(const std::any&) >>;

    //Reflecting the object within.
    class RObject
    {
        const std::any m_object;
        const std::size_t m_typeId;
        const std::string m_typeStr;
        const alloc m_allocatedOn;
        const std::vector<Converter>& m_converters;

        RObject(std::any&& pObjRef, std::size_t pTypeId, std::string pTypeStr, 
                const std::vector<Converter>& pConversions, alloc pAllocOn = rtl::alloc::None);

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

        template <class T>
        const bool isTrueType() const;

        template <class _asType>
        const bool canReflectAs() const;

        template<class _asType>
        std::optional<rtl::cref_view<_asType>> view() const;

        template <class T>
        static RObject reflect(T&& pVal);

        //friends :)
        template<class _fromType>
        friend class rtl::detail::RObjectConverter;
    };
}