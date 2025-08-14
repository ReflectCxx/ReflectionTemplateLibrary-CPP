
#include "RObject.h"
#include "CxxMirror.h"
#include "ReflectCast.h"

namespace rtl::detail 
{
    //type id counter, statically initializes a unique-id to TypeId<...>.
    std::atomic<std::size_t> g_typeIdCounter = TypeId<>::None + 1;

    //type id counter, statically initializes a unique-id to FunctorContainer<...> and MethodContainer<...>.
    std::atomic<std::size_t> g_containerIdCounter = TypeId<>::None + 1;
}


namespace rtl::access {

    std::atomic<std::size_t> RObject::m_rtlManagedInstancesCount = 0;

    /*  @Constructor: CxxMirror
        @params: 'const std::vector<Function>&'
        * accepts vector of 'Function' objects, which are hash-key to lookup a functor.
        * the only constructor to construct 'CxxMirror' object.
        * Syntax for constructing - CxxMirror({ Reflect().function("func_name").build(), ..., ... })
        * '.build()' function will return a 'Function' object, and passed to std::vector initializer list.
        * the vector is simply forwarded to the base class constructor.
    */  CxxMirror::CxxMirror(const std::vector<Function>& pFunctions) : detail::CxxReflection(pFunctions)
    {
        rtl::detail::ReflectedConversions::init();
    }
}