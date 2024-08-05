#pragma once

#include <any>
#include <memory>
#include <unordered_map>

#include "TypeId.h"
#include "Constants.h"

namespace rtl {

    namespace access
    {
		//forward decls
        class Record;
        class RStatus;
        class Function;
		
    /*  @class: Instance
        * type erased wrapper for objects created on heap via reflection.
        * 'Instance' objects are only returned from Record::clone() & Recoed::instance()
        * empty 'Instance' is returned if constructor is not found or if called with wrong args.
        * 'Instance' objects are never created on heap, only the underlying object is created on heap.
        * the lifetime of the underlying object is managed by std::shared_ptr.
    */  class Instance
        {
            //indicates if object const/non-const.
            mutable TypeQ m_qualifier;

            //type id of the containd object.
            mutable std::size_t m_typeId;

            //allocated object, stored without type info.
            mutable std::any m_anyObject;

        /*  shared_ptr, wil be shared between the copies of the 'Instance'.
            does not holds the objcet constructed via reflection.
            it only contains a custom deleter to be called on the underlying object.
        */  mutable std::shared_ptr<void> m_destructor;

            //private constructors, only class 'Record' can access.
            explicit Instance(const std::any& pRetObj, const RStatus& pStatus, const Function& pDctor);

        public:

            //create empty instance.
            explicit Instance();

            //creating copies.
            Instance(const Instance&);

            //assignment
            Instance& operator=(const Instance&);

            //simple inlined getters.
            GETTER(std::any, , m_anyObject);
            GETTER(std::size_t, TypeId, m_typeId);
            GETTER(TypeQ, Qualifier, m_qualifier);

            //checks if it contains object constructed via reflection.
            const bool isEmpty() const;

            //check the contained object is const or not.
            const bool isConst() const;

            //treat the object constructed via reflection as const or non-const.
            void makeConst(const bool& pCastAway = false);

            //get the current number of objects constructed via reflection.
            static std::size_t getInstanceCount();

            friend Record;
        };
    }
}