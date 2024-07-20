#pragma once

#include <string>
#include <optional>
#include <unordered_map>

#include "CxxReflection.h"

namespace rtl {

    namespace access 
    {
        //forward decls
        class Record;
        class Function;

    /*  @class: CxxMirror
        * provides interface to access registered functions/methods by name.
        * its the single point of access to whole reflection system.
        * all the type registration is done while constructing its object.
        * its objects can be createed locally and will be destroyed as regular object, at scope's end.
        * deleted copy constructor and assignment operator, can only be passed around as reference or wrapped in a smart pointer.
        * the inherited data members are freed upon destruction, except the functors (function/method pointer) tables, they have static lifetime.
        * functor tables are not member of this or base class, this class contains 'Function' objects which is a hash-key for looking up a particular functor.
        * creating multiple objects of CxxMirror and registring the same functor will not increase the functor tables size.
        * once a functor is registered, no entry will be added to the functor table for the same functor, it acts as a set.
        * registring the same functor will create duplicate hash-key 'Function' object, which will be ignored if in the same 'CxxMirror' object.
          if two different 'CxxMirror' objects are created and registering the same functor, the functor table will have only one entry for the functor
          but two duplicate 'Function' objects will be created, held by respective 'CxxMirror' object.
    */  class CxxMirror : public detail::CxxReflection 
        {
        public:

            //constructor, taking function objects, other constructors are disabled.
            CxxMirror(const std::vector<Function>& pFunctions);

            //get the class/struct's member-functions hash-keys wrapped in a 'Record' object.
            std::optional<Record> getRecord(const std::string& pRecordName) const;

            //get the non-member functions hash-keys.
            std::optional<Function> getFunction(const std::string& pFunctionName) const;

            //get the class/struct's member-functions hash-keys wrapped in a 'Record' object, registered with a namespace name.
            std::optional<Record> getRecord(const std::string& pNameSpaceName, const std::string& pRecordName) const;

            //get the non-member functions hash-keys, registered with a namespace name.
            std::optional<Function> getFunction(const std::string& pNameSpaceName, const std::string& pFunctionName) const;
        };
    }
}