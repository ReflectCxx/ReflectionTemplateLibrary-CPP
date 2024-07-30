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
        class RStatus;
        class Instance;

    /*  @class: Record
        * represents a reflected class/struct.
        * contains registered member-functions as 'Method' objects.
        * provides interface to access methods by name.
        * provides interface to construct instances of the class/struct using the registered constructors.
    */  class Record
        {
            const std::string m_recordName;

            mutable std::unordered_map< std::string, access::Method > m_methods;

            Record(const std::string& pRecordName);

            std::unordered_map< std::string, access::Method >& getFunctionsMap() const;

        public:

            Record() = delete;

            std::optional<Method> getMethod(const std::string& pMethod) const;

            //creates dynamic instance, calling copy ctor, using new.
            const std::pair<RStatus, Instance> clone(Instance& pOther) const;

            //creates dynamic instance, using new.
            template<class ..._ctorArgs>
            const std::pair<RStatus, Instance> instance(_ctorArgs ...params) const;

            const std::unordered_map< std::string, access::Method >& getMethodMap() const;

            //only class which can create objects of this class & manipulates 'm_methods'.
            friend class detail::CxxReflection;
		};
	}
}