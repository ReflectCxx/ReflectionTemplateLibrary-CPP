#pragma once

#include <any>
#include <vector>
#include "ReflectCast.h"

namespace rtl::access {
    class RObject;
}

namespace rtl::detail
{
    class RObjectBuilder;

    struct RObjectId
    {
        friend RObjectBuilder;
        friend access::RObject;

        GETTER(std::size_t, TypeId, m_typeId)
        GETTER(Contains, ContainedAs, m_containsAs)

    private:

        static std::vector<traits::ConverterPair> m_conversions;

        bool m_isWrappingConst;
        bool m_isConstCastSafe;

        alloc m_allocatedOn;
        Wrapper m_wrapperType;
        Contains m_containsAs;

        std::size_t m_typeId;
        std::size_t m_ptrTypeId;
        std::size_t m_wrapperTypeId;
        std::string m_typeStr;

        const std::vector<traits::ConverterPair>& m_converters;

        RObjectId(RObjectId&&) = default;
        RObjectId(const RObjectId&) = default;
        RObjectId& operator=(RObjectId&&) = delete;
        RObjectId& operator=(const RObjectId&) = delete;

        RObjectId()
            : m_isWrappingConst(false)
            , m_isConstCastSafe(false)
            , m_allocatedOn(alloc::None)
            , m_wrapperType(Wrapper::None)
            , m_containsAs(Contains::None)
            , m_typeId(TypeId<>::None)
            , m_ptrTypeId(TypeId<>::None)
            , m_wrapperTypeId(TypeId<>::None)
            , m_typeStr("")
            , m_converters(m_conversions)
        { }

        RObjectId(alloc pAllocOn, bool pIsConstCastSafe, Wrapper pWrapperType, bool pIsStoredConst,
                  Contains pContainsAs, std::size_t pTypeId, const std::string& pTypeStr, std::size_t pPtrTypeId,
                  const std::vector<traits::ConverterPair>& pConverters, std::size_t pWrapperTypeId)
            : m_isWrappingConst(pIsStoredConst)
            , m_isConstCastSafe(pIsConstCastSafe)
            , m_allocatedOn(pAllocOn)
            , m_wrapperType(pWrapperType)
            , m_containsAs(pContainsAs)
            , m_typeId(pTypeId)
            , m_ptrTypeId(pPtrTypeId)
            , m_wrapperTypeId(pWrapperTypeId)
            , m_typeStr(pTypeStr)
            , m_converters(pConverters)
        { }

        void reset()
        {
            m_isWrappingConst = false;
            m_isConstCastSafe = false;
            m_allocatedOn = alloc::None;    //very important, identifies empty/moved-from RObject.
            m_wrapperType = Wrapper::None;
            m_containsAs = Contains::None;
            m_typeId = TypeId<>::None;
            m_ptrTypeId = TypeId<>::None;
            m_wrapperTypeId = TypeId<>::None;
            m_typeStr.clear();
        }

        template<class T>
        static constexpr Contains getContainingAsType()
        {
            using W = traits::std_wrapper<traits::raw_t<T>>;
            using _T = traits::raw_t<std::conditional_t<(W::type == Wrapper::None), T, typename W::value_type>>;
            constexpr bool isConst = traits::is_const_v<T>;
            constexpr bool isRawPtr = traits::is_raw_ptr_v<T>;
            constexpr bool isWrapper = (W::type != Wrapper::None);

            if constexpr (isWrapper && !isRawPtr) {
                return (isConst ? Contains::ConstWrapper : Contains::Wrapper);
            }
            else if constexpr (isRawPtr && !isWrapper) {
                return Contains::Pointer;
            }
            else if constexpr (!isWrapper && !isRawPtr) {
                return Contains::Value;
            }
            else {
                static_assert(false, "Pointer to STL wrapper (e.g., pointer to smart-pointer) is not supported.");
            }
        }

        template<class T, rtl::alloc _allocOn>
        static RObjectId create(bool pIsConstCastSafe)
        {
            // extract wrapper info.
            using _W = traits::std_wrapper<traits::raw_t<T>>;
            // extract Un-Qualified raw type.
            using _T = traits::raw_t<std::conditional_t<(_W::type == Wrapper::None), T, typename _W::value_type>>;
            constexpr Contains containedAs = getContainingAsType<T>();
            
            const std::size_t wrapperId = _W::id();
            const std::size_t typeId = rtl::detail::TypeId<_T>::get();
            const std::size_t typePtrId = rtl::detail::TypeId<_T*>::get();
            const auto& typeStr = rtl::detail::TypeId<_T>::toString();
            const auto& conversions = rtl::detail::ReflectCast<_T>::getConversions();
            const bool isWrappingConst = (_W::type != Wrapper::None && traits::is_const_v<typename _W::value_type>);

            return RObjectId(_allocOn, pIsConstCastSafe, _W::type, isWrappingConst, containedAs,
                             typeId, typeStr, typePtrId, conversions, wrapperId);
        }
    };
}