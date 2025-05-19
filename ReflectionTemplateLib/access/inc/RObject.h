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
        std::any m_object;
        std::size_t m_typeId;
        std::string m_typeStr;
        alloc m_allocatedOn;

        const std::vector<std::pair<std::size_t, rtl::detail::Converter>>& m_converters;

        RObject() = default;

        RObject(std::any pObjRef, std::size_t pTypeId, std::string pTypeStr, alloc pAllocOn, 
                const std::vector<std::pair<std::size_t, rtl::detail::Converter>>& pConversions);

        const std::size_t getConverterIndex(const std::size_t& pToTypeId) const;

        template<class T>
        T& as();

        template <alloc _allocOn, class T>
        static RObject create(T&& pVal);

    public:

        ~RObject() = default;

        //Copy not allowed.
        RObject(const RObject&) = delete;
        RObject& operator=(const RObject&) = delete;

        //Only move allowed.
        RObject(RObject&& pOther) noexcept;
        RObject& operator=(RObject&& pOther) noexcept;

        GETTER(std::string, TypeStr, m_typeStr)

        template <class T>
        const bool isReflecting();

        template <class T>
        std::optional<std::reference_wrapper<const T>> view();

        template <alloc _allocOn, class T>
        static RObject reflect(T pVal);

        template <alloc _allocOn, class T, std::size_t N>
        static RObject reflect(const T(&pStr)[N]);

        //friends :)
        template<class _fromType>
        friend class rtl::detail::RObjectConverter;
    };
}