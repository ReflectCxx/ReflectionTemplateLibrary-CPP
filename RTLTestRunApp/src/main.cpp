
#include <thread>
#include <gtest/gtest.h>
#include "CxxMirrorTests/CxxMirrorThreadingTest.h"


class GlobalTestEnvironment : public ::testing::Environment
{
public:
    void SetUp() override
    {
        std::cout << "\n----------------------------------------------------------------------";
        std::cout << "\n        CxxMirror ==> Initialization & Multithreading-Test            ";
        std::cout << "\n----------------------------------------------------------------------";
        {
            std::jthread t0(rtl_tests::InitMirror::reflectingBook);
            std::jthread t1(rtl_tests::InitMirror::reflectingDate);
            std::jthread t2(rtl_tests::InitMirror::reflectingEvent);
            std::jthread t3(rtl_tests::InitMirror::reflectingAnimal);
            std::jthread t4(rtl_tests::InitMirror::reflectingPerson);
            std::jthread t5(rtl_tests::InitMirror::reflectingLibrary);
            std::jthread t6(rtl_tests::InitMirror::reflectingPodsStl);
            std::jthread t7(rtl_tests::InitMirror::reflectingCalender);
            std::jthread t8(rtl_tests::InitMirror::reflectingMyTypePerson);
            std::jthread t9(rtl_tests::InitMirror::reflectingCStyleFunctions);
        }
        std::cout << "\n----------------------------------------------------------------------\n\n";
    }
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new GlobalTestEnvironment);

    return RUN_ALL_TESTS();
}
