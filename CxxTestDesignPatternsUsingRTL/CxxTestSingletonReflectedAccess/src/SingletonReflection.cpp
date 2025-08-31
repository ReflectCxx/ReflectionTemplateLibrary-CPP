
#include "Singleton.h"
#include "SingletonReflection.h"

namespace singleton_test
{
    const std::optional<rtl::Record>& Reflection::getSingletonClass()
    {
        static std::optional<rtl::Record> reflectedClass = rtl::CxxMirror(
        {
            rtl::type().ns().record<Singleton>("Singleton").build(),

            rtl::type().member<Singleton>().methodStatic("getInstance").build(&Singleton::getInstance),

            rtl::type().member<Singleton>().methodConst("getHelloString").build(&Singleton::getHelloString)

        }).getRecord("Singleton");

        return reflectedClass;
    }
}