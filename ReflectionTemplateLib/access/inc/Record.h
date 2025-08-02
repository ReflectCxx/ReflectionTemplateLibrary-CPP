#pragma once

#include <memory>
#include <optional>
#include <unordered_map>

#include "Method.h"
#include "Constants.h"

namespace rtl {

	//forward decls
    namespace detail {
        class CxxReflection;
    }

    namespace access
    {
        //forward decls
        class Method;
        class RObject;

    /*  @class: Record
        * represents a reflected class/struct.
        * contains registered member-functions as 'Method' objects.
        * provides interface to access methods by name.
        * provides interface to construct instances of the class/struct using the registered constructors.
    */  class Record
        {
            using MethodMap = std::unordered_map< std::string, access::Method >;

            mutable std::size_t m_recordId;
            mutable std::string m_recordName;
            mutable MethodMap m_methods;

        private:

            Record(const std::string& pRecordName, const std::size_t pRecordId)
                : m_recordId(pRecordId)
                , m_recordName(pRecordName)
            { }

            GETTER_REF(MethodMap, FunctionsMap, m_methods)

        public:

            Record() = delete;
            Record(Record&&) = default;
            Record(const Record&) = default;
            Record& operator=(Record&&) = default;
            Record& operator=(const Record&) = default;

            GETTER_CREF(MethodMap, MethodMap, m_methods)

    /*      @method: getMethod
            @param: const std::string& (name of the method)
            @return: std::optional<Method>
            * if the method isn't found by the given name, std::nullopt is returned.
    */      std::optional<Method> getMethod(const std::string& pMethod) const
            {
                const auto& itr = m_methods.find(pMethod);
                if (itr != m_methods.end()) {
                    return std::optional(itr->second);
                }
                return std::nullopt;
            }


    /*      @method: create
            @param: ...params (any number/type of arguments)
            @return: std::pair<error, RObject>
            * calls the constructor of the calss/struct represented by this 'Record' object.
            * returns the dynamically allocated object of the calss/struct along with the status.
            * only default or any other overloaded constructor is called, except copy (for that check, Record::clone()).
            * if the signature(...params) did not match any registered ctor, error::SignatureMismatch is returned as RStatus.
            * if no constructor found, error::ReflecetdConstructorNotFound is returned as RStatus.
            * in case of reflected call failure, empty 'RObject' will be returned.
            * on success error::None will be returned along with the newly constructed object wrapped under 'RObject' (type erased).
    */      template<alloc _alloc, class ..._ctorArgs>
            std::pair<error, RObject> create(_ctorArgs&& ...params) const
            {
                static_assert(_alloc != rtl::alloc::None, "Instance cannot be created with 'rtl::alloc::None' option.");
                static_assert(_alloc != rtl::alloc::Heap_viaReflection,"'rtl::alloc::Heap_ViaReflection' is internal to RTL and must not be used explicitly.");

                const auto& itr = m_methods.find(CtorName::ctor(m_recordName));
                //if registered constructor is found for the class/struct represented by this 'Record' object.
                return itr != m_methods.end()
                           //invoke the constructor, forwarding the arguments.
                           ? itr->second.invokeCtor(_alloc, std::forward<_ctorArgs>(params)...)
                           //if no constructor found, return with empty 'RObject'.
                           : std::make_pair(error::ConstructorNotRegisteredInRtl, RObject());
            }

            //only class which can create objects of this class & manipulates 'm_methods'.
            friend class detail::CxxReflection;
        };
    }
}