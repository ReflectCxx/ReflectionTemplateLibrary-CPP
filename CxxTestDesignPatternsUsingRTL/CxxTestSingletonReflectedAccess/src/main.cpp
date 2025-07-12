
#include <iostream>
#include "SingletonReflection.h"

using namespace singleton_test;

int main()
{
    std::cout << "Singleton Instance reflected access test." << std::endl;
    {
        const auto& getInstance = Reflection::getSingletonClass()->getMethod("getInstance");

        if (!getInstance.has_value()) {
            std::cout << "Singleton::getInstance() not found! Test Failed." << std::endl;
            return -1;
        }

        auto [err, robj] = getInstance->bind().call();

        if (err != rtl::error::None) {
            std::cout << "Singleton::getInstance() reflected call failed! Error: " << rtl::to_string(err) << std::endl;
            return -1;
        }

        const auto& getHelloString = Reflection::getSingletonClass()->getMethod("getHelloString");

        if (!getHelloString.has_value()) {
            std::cout << "Singleton::getHelloString() not found! Test Failed." << std::endl;
            return -1;
        }

        auto [err0, retVal] = getHelloString->bind(robj).call();

        if (err0 != rtl::error::None || !retVal.canReflectAs<std::string>()) {
            std::cout << "Singleton::getHelloString() reflected call failed! Error: " << rtl::to_string(err) << std::endl;
            return -1;
        }

        const auto& helloStr = retVal.view<std::string>()->get();

        std::cout << "Singleton::getHelloString(), reflected call returned: " << helloStr << std::endl;
    }

    std::cout << "Singleton Instance reflected access test. PASSED." << std::endl;

    return 0;
}