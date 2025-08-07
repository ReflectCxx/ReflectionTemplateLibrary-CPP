/*_________________________________________________________________________
* Copyright 2025 Neeraj Singh
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
___________________________________________________________________________*/

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
            * if the signature(...params) did not match any registered ctor, error::SignatureMismatch is returned with empty 'RObject'.
            * if no constructor found, error::ConstructorNotRegisteredInRtl is returned with empty 'RObject'.
            * on success error::None and newly constructed object wrapped under 'RObject' (type erased, treated as non-const) is returned.
    */      template<alloc _alloc, class ..._ctorArgs>
            std::pair<error, RObject> create(_ctorArgs&& ...params) const
            {
                static_assert(_alloc != rtl::alloc::None, "Instance cannot be created with 'rtl::alloc::None' option.");
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