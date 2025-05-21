#pragma once

#include <any>
#include <string>
#include <optional>
#include <functional>

#include "Constants.h"

#include "RObjectConverters.hpp"

namespace rtl::access
{
    //Reflecting the object within.
    class RObject
    {
        const std::any m_object;
        const std::size_t m_typeId;
        const std::string m_typeStr;
        const alloc m_allocatedOn;

        using Converter = std::pair<std::size_t, rtl::detail::Converter>;
        const std::vector<Converter>& m_converters;

        RObject(std::any pObjRef, std::size_t pTypeId, std::string pTypeStr, alloc pAllocOn, 
                const std::vector<Converter>& pConversions);

        template<class T>
        T& as();

        template <alloc _allocOn, class T>
        static RObject create(T&& pVal);

        template<class T>
        const std::size_t getTypeId();

        const std::size_t getConverterIndex(const std::size_t& pToTypeId);

    public:

        ~RObject() = default;
        RObject(const RObject&) = default;
        RObject(RObject&& pOther) = default;

        RObject& operator=(const RObject&) = delete;
        RObject& operator=(RObject&& pOther) = delete;

        GETTER(std::string, TypeStr, m_typeStr)

        template <class _asType>
        const bool isReflecting();

        template <class _asType>
        const _asType* view();

        template <alloc _allocOn, class T>
        static RObject reflect(T&& pVal);

        //friends :)
        template<class _fromType>
        friend class rtl::detail::RObjectConverter;
    };
}