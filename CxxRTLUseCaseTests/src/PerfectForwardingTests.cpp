/**
 * @file PerfectForwardingTests.cpp
 * @brief This file contains unit tests to validate the behavior of perfect forwarding in the reflection system.
 *
 * Perfect forwarding ensures that arguments are forwarded to the correct method overload while preserving their
 * value category (L-value, R-value, or const L-value). The tests use the reflection system to dynamically retrieve
 * and invoke methods, ensuring that the correct overload is called based on the argument type and value category.
 *
 * Note: The explicitly provided template types (e.g., `std::string&`, `std::string&&`, `const std::string&`) are
 * required by the design of the Reflection Template Library (RTL) to match the method signatures during invocation.
 *
 * Key Components:
 * - `CxxMirror`: The main reflection interface that provides access to class metadata (`Record`) and methods (`Method`).
 * - `Record`: Represents a reflected class/struct and provides access to its methods and constructors.
 * - `Method`: Represents a reflected method and provides interfaces to invoke it dynamically.
 * - `Instance`: A type-erased wrapper for objects created via reflection, ensuring proper memory management.
 * - `RStatus`: Represents the result of a reflection call, including the return value and error status.
 */

#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsAnimal.h"

using namespace std;
using namespace rtl;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests
{
    /**
     * @brief Test that a non-const L-value reference binds only to the corresponding overload.
     *
     * This test verifies that the reflection system correctly identifies and invokes the method
     * overload that accepts a non-const L-value reference (`std::string&`).
     */
    TEST(PerfectForwardingTest, non_const_lvalue_ref_only_binds_to_non_const_lvaue_ref_overload_on_heap)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            // Retrieve the metadata for the "Animal" class.
            optional<Record> classAnimal = cxxMirror.getRecord(animal::class_);
            ASSERT_TRUE(classAnimal);

            // Retrieve the "setAnimalName" method.
            optional<Method> setAnimalName = classAnimal->getMethod(animal::str_setAnimalName);
            ASSERT_TRUE(setAnimalName);

            // Create an instance of the "Animal" class.
            auto [status, animalObj] = classAnimal->create<alloc::Heap>();
            ASSERT_TRUE(status);
            ASSERT_FALSE(animalObj.isEmpty());

            // Verify that the method has the correct signature for a non-const L-value reference.
            const auto& isValid = setAnimalName->hasSignature<std::string&>();
            ASSERT_TRUE(isValid);

            // Invoke the method with a non-const L-value reference.
            auto nameStr = std::string(animal::NAME);
            status = setAnimalName->bind<std::string&>(animalObj).call(nameStr);

            ASSERT_TRUE(status);
            ASSERT_FALSE(status.getReturn().has_value());

            // Validate the behavior of the method.
            EXPECT_TRUE(animal::test_method_setAnimalName_non_const_lvalue_ref_args(animalObj.get(), animalObj.isOnHeap()));
        }

        // Ensure that all instances are cleaned up.
        EXPECT_TRUE(animal::assert_zero_instance_count());
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
    }


    TEST(PerfectForwardingTest, non_const_lvalue_ref_only_binds_to_non_const_lvaue_ref_overload_on_stack)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> classAnimal = cxxMirror.getRecord(animal::class_);
            ASSERT_TRUE(classAnimal);

            optional<Method> setAnimalName = classAnimal->getMethod(animal::str_setAnimalName);
            ASSERT_TRUE(setAnimalName);

            auto [status, animalObj] = classAnimal->create<alloc::Stack>();
            ASSERT_TRUE(status);
            ASSERT_FALSE(animalObj.isEmpty());

            const auto& isValid = setAnimalName->hasSignature<std::string&>();
            ASSERT_TRUE(isValid);

            auto nameStr = std::string(animal::NAME);
            status = setAnimalName->bind<std::string&>(animalObj).call(nameStr);

            ASSERT_TRUE(status);
            ASSERT_FALSE(status.getReturn().has_value());

            EXPECT_TRUE(animal::test_method_setAnimalName_non_const_lvalue_ref_args(animalObj.get(), animalObj.isOnHeap()));
        }
        EXPECT_TRUE(animal::assert_zero_instance_count());
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
    }


    /**
     * @brief Test that an R-value reference binds only to the corresponding overload.
     *
     * This test verifies that the reflection system correctly identifies and invokes the method
     * overload that accepts an R-value reference (`std::string&&`).
     */
    TEST(PerfectForwardingTest, rvalue_ref_only_binds_to_rvalue_ref_overload_on_heap)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            // Retrieve the metadata for the "Animal" class.
            optional<Record> classAnimal = cxxMirror.getRecord(animal::class_);
            ASSERT_TRUE(classAnimal);

            // Retrieve the "setAnimalName" method.
            optional<Method> setAnimalName = classAnimal->getMethod(animal::str_setAnimalName);
            ASSERT_TRUE(setAnimalName);

            // Create an instance of the "Animal" class.
            auto [status, animalObj] = classAnimal->create<alloc::Heap>();
            ASSERT_TRUE(status);
            ASSERT_FALSE(animalObj.isEmpty());

            // Verify that the method has the correct signature for an R-value reference.
            const auto& isValid = setAnimalName->hasSignature<std::string&&>();
            ASSERT_TRUE(isValid);

            // Invoke the method with an R-value reference.
            status = setAnimalName->bind<std::string&&>(animalObj).call(animal::NAME);

            ASSERT_TRUE(status);
            ASSERT_FALSE(status.getReturn().has_value());

            // Validate the behavior of the method.
            EXPECT_TRUE(animal::test_method_setAnimalName_rvalue_args(animalObj.get(), animalObj.isOnHeap()));
        }

        // Ensure that all instances are cleaned up.
        EXPECT_TRUE(animal::assert_zero_instance_count());
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
    }


    TEST(PerfectForwardingTest, rvalue_ref_only_binds_to_rvalue_ref_overload_on_stack)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> classAnimal = cxxMirror.getRecord(animal::class_);
            ASSERT_TRUE(classAnimal);

            optional<Method> setAnimalName = classAnimal->getMethod(animal::str_setAnimalName);
            ASSERT_TRUE(setAnimalName);

            auto [status, animalObj] = classAnimal->create<alloc::Stack>();
            ASSERT_TRUE(status);
            ASSERT_FALSE(animalObj.isEmpty());

            const auto& isValid = setAnimalName->hasSignature<std::string&&>();
            ASSERT_TRUE(isValid);

            status = setAnimalName->bind<std::string&&>(animalObj).call(animal::NAME);

            ASSERT_TRUE(status);
            ASSERT_FALSE(status.getReturn().has_value());

            EXPECT_TRUE(animal::test_method_setAnimalName_rvalue_args(animalObj.get(), animalObj.isOnHeap()));
        }
        EXPECT_TRUE(animal::assert_zero_instance_count());
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
    }

    /**
     * @brief Test that a const L-value reference binds only to the corresponding overload.
     *
     * This test verifies that the reflection system correctly identifies and invokes the method
     * overload that accepts a const L-value reference (`const std::string&`).
     */
    TEST(PerfectForwardingTest, const_lvalue_ref_only_binds_to_const_lvaue_ref_overload_on_heap)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            // Retrieve the metadata for the "Animal" class.
            optional<Record> classAnimal = cxxMirror.getRecord(animal::class_);
            ASSERT_TRUE(classAnimal);

            // Retrieve the "setAnimalName" method.
            optional<Method> setAnimalName = classAnimal->getMethod(animal::str_setAnimalName);
            ASSERT_TRUE(setAnimalName);

            // Create an instance of the "Animal" class.
            auto [status, animalObj] = classAnimal->create<alloc::Heap>();
            ASSERT_TRUE(status);
            ASSERT_FALSE(animalObj.isEmpty());

            // Verify that the method has the correct signature for a const L-value reference.
            const auto& isValid = setAnimalName->hasSignature<const std::string&>();
            ASSERT_TRUE(isValid);

            // Invoke the method with a const L-value reference.
            const auto nameStr = std::string(animal::NAME);
            status = setAnimalName->bind<const std::string&>(animalObj).call(nameStr);

            ASSERT_TRUE(status);
            ASSERT_FALSE(status.getReturn().has_value());

            // Validate the behavior of the method.
            EXPECT_TRUE(animal::test_method_setAnimalName_const_lvalue_ref_args(animalObj.get(), animalObj.isOnHeap()));
        }

        // Ensure that all instances are cleaned up.
        EXPECT_TRUE(animal::assert_zero_instance_count());
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
    }


    TEST(PerfectForwardingTest, const_lvalue_ref_only_binds_to_const_lvaue_ref_overload_on_stack)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> classAnimal = cxxMirror.getRecord(animal::class_);
            ASSERT_TRUE(classAnimal);

            optional<Method> setAnimalName = classAnimal->getMethod(animal::str_setAnimalName);
            ASSERT_TRUE(setAnimalName);

            auto [status, animalObj] = classAnimal->create<alloc::Stack>();
            ASSERT_TRUE(status);
            ASSERT_FALSE(animalObj.isEmpty());

            const auto& isValid = setAnimalName->hasSignature<const std::string&>();
            ASSERT_TRUE(isValid);

            const auto nameStr = std::string(animal::NAME);
            status = setAnimalName->bind<const std::string&>(animalObj).call(nameStr);

            ASSERT_TRUE(status);
            ASSERT_FALSE(status.getReturn().has_value());

            EXPECT_TRUE(animal::test_method_setAnimalName_const_lvalue_ref_args(animalObj.get(), animalObj.isOnHeap()));
        }
        EXPECT_TRUE(animal::assert_zero_instance_count());
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
    }


    TEST(PerfectForwardingTest, static_fn_const_lvalue_ref_only_binds_to_const_lvaue_ref_overload)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> classAnimal = cxxMirror.getRecord(animal::class_);
            ASSERT_TRUE(classAnimal);

            optional<Method> updateZooKeeper = classAnimal->getMethod(animal::str_updateZooKeeper);
            ASSERT_TRUE(updateZooKeeper);

            const auto& isValid = updateZooKeeper->hasSignature<const std::string&>();
            ASSERT_TRUE(isValid);

            const auto zookeeper = std::string(animal::ZOO_KEEPER);
            RStatus status = updateZooKeeper->bind<const std::string&>().call(zookeeper);

            ASSERT_TRUE(status);
            ASSERT_TRUE(status.getReturn().has_value());
            ASSERT_TRUE(status.isOfType<string>());

            const string& retStr = any_cast<string>(status.getReturn());
            EXPECT_TRUE(animal::test_method_updateZooKeeper<const std::string&>(retStr));
        }

        EXPECT_TRUE(animal::assert_zero_instance_count());
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
    }


    TEST(PerfectForwardingTest, static_fn_rvalue_ref_only_binds_to_rvalue_ref_overload)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> classAnimal = cxxMirror.getRecord(animal::class_);
            ASSERT_TRUE(classAnimal);

            optional<Method> updateZooKeeper = classAnimal->getMethod(animal::str_updateZooKeeper);
            ASSERT_TRUE(updateZooKeeper);

            const auto& isValid = updateZooKeeper->hasSignature<std::string&&>();
            ASSERT_TRUE(isValid);

            RStatus status = updateZooKeeper->bind<std::string&&>().call(animal::ZOO_KEEPER);

            ASSERT_TRUE(status);
            ASSERT_TRUE(status.getReturn().has_value());
            ASSERT_TRUE(status.isOfType<string>());

            const string& retStr = any_cast<string>(status.getReturn());
            EXPECT_TRUE(animal::test_method_updateZooKeeper<std::string&&>(retStr));
        }

        EXPECT_TRUE(animal::assert_zero_instance_count());
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
    }


    TEST(PerfectForwardingTest, static_fn_non_const_lvalue_ref_only_binds_to_non_const_lvaue_ref_overload)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> classAnimal = cxxMirror.getRecord(animal::class_);
            ASSERT_TRUE(classAnimal);

            optional<Method> updateZooKeeper = classAnimal->getMethod(animal::str_updateZooKeeper);
            ASSERT_TRUE(updateZooKeeper);

            const auto& isValid = updateZooKeeper->hasSignature<const std::string&>();
            ASSERT_TRUE(isValid);

            auto zookeeper = std::string(animal::ZOO_KEEPER);
            RStatus status = updateZooKeeper->bind<std::string&>().call(zookeeper);

            ASSERT_TRUE(status);
            ASSERT_TRUE(status.getReturn().has_value());
            ASSERT_TRUE(status.isOfType<string>());

            const string& retStr = any_cast<string>(status.getReturn());
            EXPECT_TRUE(animal::test_method_updateZooKeeper<std::string&>(retStr));
        }

        EXPECT_TRUE(animal::assert_zero_instance_count());
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
    }
}