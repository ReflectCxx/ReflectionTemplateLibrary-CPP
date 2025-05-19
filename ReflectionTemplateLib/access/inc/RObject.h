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

        template <class T>
        T& as();

        template <class T>
        const T& as() const;

        const std::size_t getConverterIndex(const std::size_t& pToTypeId) const;

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

        //RObject clone();

        template <class T>
        std::optional<T> getAs();

        template <class _asType>
        std::optional<RObject> cloneAs();

        template <class T>
        std::optional<std::reference_wrapper<T>> viewAs();

        template <class _asType>
        const bool canBeClonedAs();

        template <class T>
        const bool isReflectingType();

        template <alloc _allocOn, class T>
        static RObject reflect(T pVal);

        template <alloc _allocOn, class T, std::size_t N>
        static RObject reflect(const T(&pStr)[N]);
    };
}