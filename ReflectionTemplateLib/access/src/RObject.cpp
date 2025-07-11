
//#include <cassert>

#include "RObject.h"
#include "TypeId.h"

namespace {
	//global, used to assign to shared pointer with custom deleter.
	static std::size_t g_reflectedInstanceCount = 0;
    static std::vector<rtl::access::ConverterPair> g_conversions = { };
}

namespace rtl::access {

    RObject::RObject()
    : m_typeQ(rtl::TypeQ::None)
    , m_isPointer(rtl::IsPointer::No)
    , m_typeId(rtl::detail::TypeId<>::None)
    , m_typePtrId(rtl::detail::TypeId<>::None)
    , m_allocatedOn(rtl::alloc::None)
    , m_converters(g_conversions)
    , m_deallocator(nullptr)
    {
    }


    RObject::RObject(std::any&& pObjRef, std::size_t pTypeId, std::size_t pTypePtrId, std::string pTypeStr,
                     const rtl::TypeQ& pTypeQ, const rtl::IsPointer pIsPtr, const std::vector<ConverterPair>& pConversions)
    : m_typeQ(pTypeQ)
    , m_isPointer(pIsPtr)
    , m_object(std::move(pObjRef))
    , m_typeId(pTypeId)
    , m_typePtrId(pTypePtrId)
    , m_typeStr(pTypeStr)
    , m_allocatedOn(rtl::alloc::Stack)
    , m_converters(pConversions)
    , m_deallocator(nullptr)
    {
    }


    const std::size_t RObject::getConverterIndex(const std::size_t& pToTypeId) const
    {
        for (std::size_t index = 0; index < m_converters.size(); index++)
        {
            if (m_converters[index].first == pToTypeId) {
                return index;
            }
        }
        return -1;
    }


    //RObject::RObject(std::any pObjectPtr, const Function& pDctor)
 //   : m_isPointer(rtl::IsPointer::Yes)
 //   , m_object(pObjectPtr)
 //   , m_typeId(pDctor.getRecordTypeId())
 //   , m_typePtrId(rtl::detail::TypeId<>::None)
 //   , m_typeStr(pDctor.getRecordName())
 //   , m_allocatedOn(rtl::alloc::Heap)
 //   , m_converters(g_conversions)
 //   , m_deallocator(&g_reflectedInstanceCount, [=](std::size_t* pReflectedInstanceCount) {

 //       const auto& retStatus = pDctor.bind<std::any>().call(pObjectPtr);
 //       assert(retStatus == rtl::error::None && "dctor not called. memory leak!");
 //       const auto& instanceCount = --(*pReflectedInstanceCount);
 //       assert(instanceCount >= 0 && "instance count can't be less than zero. memory leak!");
 //   })
 //   {
 //       g_reflectedInstanceCount++;
 //   }
}
