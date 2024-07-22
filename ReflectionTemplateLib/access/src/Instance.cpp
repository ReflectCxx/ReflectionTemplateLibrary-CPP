
#include <any>

#include "TypeId.hpp"
#include "RStatus.h"
#include "Instance.h"
#include "Function.hpp"

namespace {

	//global, used to assign to shared pointer with custom deleter.
	static std::size_t g_instanceCount = 0;
}

namespace rtl {

    namespace access
    {
    /*  @method: isEmpty()
        @return: bool
        * checks if std::any object has value or not.
        * objects constructed via reflection is held by std::any (instead of void*)
        * if reflected constructor call fails, 'Insatnce' object returned with empty 'm_anyObject'.
    */  const bool Instance::isEmpty() const {
            return (!m_anyObject.has_value());
        }


    /*  @method: isConst()
        @return: bool
        * tells how the object held by 'm_anyObject' should be treated.
        * every object constructed via reflected constructor call is a non-const object pointer.
        * it can be made to treated as const by calling Instance::makeConst().
    */  const bool Instance::isConst() const {
            return (m_qualifier == TypeQ::Const);
        }


    /*  @method: getInstanceCount()
        @return: std::size_t (g_instanceCount).
        * returns the number of objects constructed via reflected constructor call.
        * g_instanceCount is incremented only on successful reflected constructor call.
        * g_instanceCount is decremented only when reflected destructor call.
    */  std::size_t Instance::getInstanceCount() {
            return g_instanceCount;
        }


    /*  @method: makeConst()
        @param: bool, (true by default)
        * objects constructed via reflected constructor call, held by 'm_anyObject' as a non-const object pointer.
        * 'm_qualifier' indicates how the object should be treated- as const or non-const.
        * if 'm_qualifier' is TypeQ::Const, only const member function will be called on the object held by 'm_anyObject'
        * if 'm_qualifier' is TypeQ::Mute,, only non-const member function will be called on the objject held by 'm_anyObject'
    */  void Instance::makeConst(const bool& pCastAway) {
            m_qualifier = (pCastAway ? TypeQ::Mute : TypeQ::Const);
        }

    /*  @constructor: Instance()
        * creates 'Instance' with empty 'm_anyObject'.
        * 'm_typeId' will be zero which indicates no-type.
        * this constructor is called only when reflected constructor call fails.
    */  Instance::Instance()
            : m_qualifier(TypeQ::None)
            , m_typeId(detail::TypeId<>::None) {
        }

        //copy-constructor, public access.
        Instance::Instance(const Instance& pOther)
            : m_qualifier(pOther.m_qualifier)
            , m_typeId(pOther.m_typeId)
            , m_anyObject(pOther.m_anyObject)
            , m_destructor(pOther.m_destructor) {
        }


    /*  @constructor: Instance()
        @params: 'const std::any&', contains pointer to the allocated object via reflection constructor call.
        *        'const RStatus&', status returned via reflection constructor call.
        *        'const Function&', callable 'Function', calls the reflecetd destructor.
        * creates 'Instance' containing pointer to the allocated object via reflection constructor call.
        * this constructor is called only on successful object creation on heap via reflected constructor call.
        * 'm_destructor' (shared_ptr) is given a custom deleter, which calls destructor on the allocated(via reflection) object.
        * 'm_destructor' holds a dummy void* pointer (address of 'g_instanceCount'), for which is a primitive type.
        * this is done to avoid dynamic allocation of 'Instance' object to manage it with 'shared_ptr'.
        * shared_ptr('m_destructor') holds the dummy void* but calls the actual destructor which destroys the object constructed(via reflection).
    */  Instance::Instance(const std::any& pRetObj, const RStatus& pStatus, const Function& pDctor)
            : m_qualifier(TypeQ::Mute)
            , m_typeId(pStatus.getTypeId())
            , m_anyObject(pRetObj)
            , m_destructor(&g_instanceCount, [=](void* ptr)
            {
                pDctor(pRetObj);
                (*static_cast<std::size_t*>(ptr))--;
            })
        {
            g_instanceCount++;
        }
    }
}