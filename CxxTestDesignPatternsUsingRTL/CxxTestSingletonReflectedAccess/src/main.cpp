
#include <iostream>
#include "SingletonReflection.h"


int main()
{
    std::cout << "Singleton Instance reflected access test." << std::endl;
    {
        const auto& getInstance = singleton_test::Reflection::getSingletonClass()->getMethod("getInstance");

        if (!getInstance.has_value()) {
            std::cout << "Singleton::getInstance() not found! Test Failed." << std::endl;
            return -1;
        }

        auto status = getInstance->bind().call();

        if (!status || !status.getReturn().has_value()) {
            std::cout << "Singleton::getInstance() reflected call failed! Error: " << rtl::to_string(status) << std::endl;
            return -1;
        }

        rtl::access::Instance instance(status);

        if (status.getReturn().has_value() || instance.isEmpty()) {
            std::cout << "Singleton::getInstance(), cannot create reflected instance! " << std::endl;
            return -1;
        }

        const auto& getHelloString = singleton_test::Reflection::getSingletonClass()->getMethod("getHelloString");

        if (!getHelloString.has_value()) {
            std::cout << "Singleton::getHelloString() not found! Test Failed." << std::endl;
            return -1;
        }

        status = getHelloString->bind(instance).call();

        if (!status || !status.getReturn().has_value() || !status.isOfType<std::string>()) {
            std::cout << "Singleton::getHelloString() reflected call failed! Error: " << rtl::to_string(status) << std::endl;
            return -1;
        }

        const auto& helloStr = std::any_cast<std::string>(status.getReturn());

        std::cout << "Singleton::getHelloString(), reflected call returned: " << helloStr << std::endl;
    }

    if (rtl::access::Instance::getInstanceCount() != 0) {
        std::cout << "'Instance' not destroyed! test failed." << std::endl;
    }

    std::cout << "Singleton Instance reflected access test. PASSED." << std::endl;

    return 0;
}