#pragma once

#include <memory>
#include <optional>
#include <unordered_map>

#include "Method.h"

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
            mutable std::size_t m_recordId;

            mutable std::string m_recordName;

            mutable std::unordered_map< std::string, access::Method > m_methods;

        private:

            explicit Record(const std::string& pRecordName, const std::size_t pRecordId);

            std::unordered_map< std::string, access::Method >& getFunctionsMap() const;

        public:

            Record() = delete;

            Record& operator=(const Record& pOther);

            std::optional<Method> getMethod(const std::string& pMethod) const;

            //creates dynamic, deep-copy instance, calling copy ctor, using new.
            std::pair<error, RObject> clone(RObject& pOther) const;

            //creates dynamic instance, using new.
            template<alloc _alloc, class ..._ctorArgs>
            std::pair<error, RObject> create(_ctorArgs&& ...params) const;

            const std::unordered_map< std::string, access::Method >& getMethodMap() const;

            //only class which can create objects of this class & manipulates 'm_methods'.
            friend class detail::CxxReflection;
        };
    }
}