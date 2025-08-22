
#include "Singleton.h"
#include "SingletonReflection.h"

using namespace rtl::builder;
using namespace rtl::access;

namespace singleton_test
{
    const std::optional<rtl::access::Record>& Reflection::getSingletonClass()
    {
        static std::optional<rtl::access::Record> reflectedClass = CxxMirror(
            {
                Reflect().nameSpace().record<Singleton>("Singleton").build(),

                Reflect().member<Singleton>().methodStatic("getInstance").build(&Singleton::getInstance),

                Reflect().member<Singleton>().methodConst("getHelloString").build(&Singleton::getHelloString)

            }).getRecord("Singleton");

        return reflectedClass;
    }
}