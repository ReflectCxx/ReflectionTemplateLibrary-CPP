#pragma once

#include "TypeId.h"
#include "Constants.h"

namespace rtl
{
    namespace detail
    {
    /*  @class: FunctorId
        * 'FunctorId' object is generated for every functor (member/non-member function pointer) registered.
        * acts as a hash-key to lookup a particular functor in the functor-table.
        * first, using 'm_containerId', the functor-table container is found.
        * once table is found, the functor is accessed at index 'm_index', (never fails, noexcept)
        * 'FunctorId' generated for a each functor is unique, even for overloaded functions.
        * multiple registartion of same functor will generate same duplicate 'FunctorId'.
    */  class FunctorId
        {
            //index of the functor in the functor-table.
            std::size_t m_index;

            //return type-id of the functor registered.
            std::size_t m_returnId;

            //if functor is a member-function, type id of class/struct it belongs to.
            std::size_t m_recordId;

            //containerId of the functor-table.
            std::size_t m_containerId;

            //signature of functor as string. platform dependent, may not be very much readable format.
            std::string m_signature;

        public:

            FunctorId() 
                : m_index(rtl::index_none)
                , m_returnId(TypeId<>::None)
                , m_recordId(TypeId<>::None)
                , m_containerId(TypeId<>::None)
                , m_signature("") {
            }

            FunctorId(std::size_t pIndex,
                      std::size_t pReturnId, std::size_t pRecordId,
                      std::size_t pContainerId, const std::string& pSignature)
                : m_index(pIndex)
                , m_returnId(pReturnId)
                , m_recordId(pRecordId)
                , m_containerId(pContainerId)
                , m_signature(pSignature) {
            }

            FunctorId& operator=(const FunctorId& pOther);

            GETTER(std::size_t, Index, m_index)
            GETTER(std::size_t, ReturnId, m_returnId);
            GETTER(std::size_t, RecordId, m_recordId);
            GETTER(std::size_t, SignatureId, m_containerId)
            GETTER(std::string, SignatureStr, m_signature)
			
            //get a unique hascode representing a functor.
            std::size_t getHashCode() const;
        };
    }
}