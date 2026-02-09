/**
 * @file PerfectForwardingTests.cpp
 * @brief This file contains unit tests to validate the behavior of perfect forwarding in the reflection system.
 *
 * Perfect forwarding ensures that arguments are forwarded to the correct method overload while preserving their
 * value category (L-value, R-value, or const L-value). The tests use the reflection system to dynamically retrieve
 * and invoke methods, ensuring that the correct overload is called based on the argument type and value category.
 *
 * Note: The explicitly provided template types (e.g., `std::string&`, `std::string&&`, `const std::string&`) are
 * required by the design of the RTL to match the method signatures during invocation.
 *
 * Key Components:
 * - `CxxMirror`: The main reflection interface that provides access to class metadata (`Record`) and methods (`Method`).
 * - `Record`: Represents a reflected class/struct and provides access to its methods and constructors.
 * - `Method`: Represents a reflected method and provides interfaces to invoke it dynamically.
 * - `RObject`: A type-erased wrapper for return values and objects created via reflection, ensuring proper memory management.
 */


#include <rtl_access.h>
#include <gtest/gtest.h>

#include "TestMirrorProvider.h"
#include "TestUtilsAnimal.h"

using namespace std;
using namespace rtl;

using namespace test_utils;


namespace rtl_tests
{
    /**
     * @brief Test that an R-value reference binds only to the corresponding overload.
     *
     * This test verifies that the reflection system correctly identifies and invokes the method
     * overload that accepts an R-value reference (`std::string&&`).
     */
    TEST(PerfectForwardingTest, overload_resolution_with_rvalue_ref_on_heap_object)
    {
        {
            // Retrieve the metadata for the "Animal" class.
            optional<Record> classAnimal = cxx::mirror().getRecord(animal::class_);
            ASSERT_TRUE(classAnimal);

            // Create an instance of the "Animal" class.
            auto [err0, animal] = classAnimal->ctorT()(alloc::Heap);
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(animal.isEmpty());

            // Retrieve the "setAnimalName" method.
            optional<Method> oSetAnimalName = classAnimal->getMethod(animal::str_setAnimalName);
            ASSERT_TRUE(oSetAnimalName);
            // Verify that the method has the correct signature for an R-value reference.
            EXPECT_TRUE((oSetAnimalName->hasSignature<std::string&&>()));

            auto setAnimalName = oSetAnimalName->targetT().argsT<std::string>().returnT();
            EXPECT_TRUE(setAnimalName);

            // Invoke the method with an R-value reference.
            auto [err1, ret1] = setAnimalName.bind<std::string&&>(animal)(animal::NAME);

            EXPECT_TRUE(err1 == error::None);
            ASSERT_TRUE(ret1.isEmpty());

            // Validate the behavior of the method.
            EXPECT_TRUE(animal::test_method_setAnimalName_rvalue_args(animal));
        }

        // Ensure that all instances are cleaned up.
        EXPECT_TRUE(animal::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    /**
    * @brief Test that a non-const L-value reference binds only to the corresponding overload.
    *
    * This test verifies that the reflection system correctly identifies and invokes the method
    * overload that accepts a non-const L-value reference (`std::string&`). */
    TEST(PerfectForwardingTest, overload_resolution_with_non_const_lvaue_ref_on_heap_object)
    {
        {
            // Retrieve the metadata for the "Animal" class.
            optional<Record> classAnimal = cxx::mirror().getRecord(animal::class_);
            ASSERT_TRUE(classAnimal);

            // Create an instance of the "Animal" class.
            auto [err0, animal] = classAnimal->ctorT()(alloc::Heap);
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(animal.isEmpty());

            // Retrieve the "setAnimalName" method.
            optional<Method> oSetAnimalName = classAnimal->getMethod(animal::str_setAnimalName);
            ASSERT_TRUE(oSetAnimalName);
            // Verify that the method has the correct signature for a non-const L-value reference.
            EXPECT_TRUE((oSetAnimalName->hasSignature<std::string&>()));

            auto setAnimalName = oSetAnimalName->targetT().argsT<std::string>().returnT();
            EXPECT_TRUE(setAnimalName);

            // Invoke the method with a non-const L-value reference.
            auto [err1, ret1] = setAnimalName.bind<std::string&>(animal)(animal::NAME);

            EXPECT_TRUE(err1 == error::None);
            ASSERT_TRUE(ret1.isEmpty());

            // Validate the behavior of the method.
            EXPECT_TRUE(animal::test_method_setAnimalName_non_const_lvalue_ref_args(animal));
        }

        // Ensure that all instances are cleaned up.
        EXPECT_TRUE(animal::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    /*
    * @brief Test that a const L-value reference binds only to the corresponding overload.
    *
    * This test verifies that the reflection system correctly identifies and invokes the method
    * overload that accepts a const L-value reference (`const std::string&`). */
    TEST(PerfectForwardingTest, overload_resolution_with_const_lvaue_ref_on_heap_object)
    {
        {
            // Retrieve the metadata for the "Animal" class.
            optional<Record> classAnimal = cxx::mirror().getRecord(animal::class_);
            ASSERT_TRUE(classAnimal);

            // Create an instance of the "Animal" class.
            auto [err0, animal] = classAnimal->ctorT()(alloc::Heap);
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(animal.isEmpty());

            // Retrieve the "setAnimalName" method.
            optional<Method> oSetAnimalName = classAnimal->getMethod(animal::str_setAnimalName);
            ASSERT_TRUE(oSetAnimalName);
            // Verify that the method has the correct signature for a const L-value reference.
            EXPECT_TRUE((oSetAnimalName->hasSignature<const std::string&>()));

            auto setAnimalName = oSetAnimalName->targetT().argsT<std::string>().returnT();
            EXPECT_TRUE(setAnimalName);

            // Invoke the method with a const L-value reference.
            auto [err1, ret1] = setAnimalName.bind<const std::string&>(animal)(animal::NAME);

            EXPECT_TRUE(err1 == error::None);
            EXPECT_TRUE(ret1.isEmpty());

            // Validate the behavior of the method.
            EXPECT_TRUE(animal::test_method_setAnimalName_const_lvalue_ref_args(animal));
        }

        // Ensure that all instances are cleaned up.
        EXPECT_TRUE(animal::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }



    /**
 * @brief Test that an R-value reference binds only to the corresponding overload.
 *
 * This test verifies that the reflection system correctly identifies and invokes the method
 * overload that accepts an R-value reference (`std::string&&`).
 */
    TEST(PerfectForwardingTest, overload_resolution_with_rvalue_ref_on_stack_object)
    {
        {
            // Retrieve the metadata for the "Animal" class.
            optional<Record> classAnimal = cxx::mirror().getRecord(animal::class_);
            ASSERT_TRUE(classAnimal);

            // Create an instance of the "Animal" class.
            auto [err0, animal] = classAnimal->ctorT()(alloc::Stack);
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(animal.isEmpty());

            // Retrieve the "setAnimalName" method.
            optional<Method> oSetAnimalName = classAnimal->getMethod(animal::str_setAnimalName);
            ASSERT_TRUE(oSetAnimalName);
            // Verify that the method has the correct signature for an R-value reference.
            EXPECT_TRUE((oSetAnimalName->hasSignature<std::string&&>()));

            auto setAnimalName = oSetAnimalName->targetT().argsT<std::string>().returnT();
            EXPECT_TRUE(setAnimalName);

            // Invoke the method with an R-value reference.
            auto [err1, ret1] = setAnimalName.bind<std::string&&>(animal)(animal::NAME);

            EXPECT_TRUE(err1 == error::None);
            ASSERT_TRUE(ret1.isEmpty());

            // Validate the behavior of the method.
            EXPECT_TRUE(animal::test_method_setAnimalName_rvalue_args(animal));
        }

        // Ensure that all instances are cleaned up.
        EXPECT_TRUE(animal::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    /**
    * @brief Test that a non-const L-value reference binds only to the corresponding overload.
    *
    * This test verifies that the reflection system correctly identifies and invokes the method
    * overload that accepts a non-const L-value reference (`std::string&`). */
    TEST(PerfectForwardingTest, overload_resolution_with_non_const_lvaue_ref_on_stack_object)
    {
        {
            // Retrieve the metadata for the "Animal" class.
            optional<Record> classAnimal = cxx::mirror().getRecord(animal::class_);
            ASSERT_TRUE(classAnimal);

            // Create an instance of the "Animal" class.
            auto [err0, animal] = classAnimal->ctorT()(alloc::Stack);
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(animal.isEmpty());

            // Retrieve the "setAnimalName" method.
            optional<Method> oSetAnimalName = classAnimal->getMethod(animal::str_setAnimalName);
            ASSERT_TRUE(oSetAnimalName);
            // Verify that the method has the correct signature for a non-const L-value reference.
            EXPECT_TRUE((oSetAnimalName->hasSignature<std::string&>()));

            auto setAnimalName = oSetAnimalName->targetT().argsT<std::string>().returnT();
            EXPECT_TRUE(setAnimalName);

            // Invoke the method with a non-const L-value reference.
            auto [err1, ret1] = setAnimalName.bind<std::string&>(animal)(animal::NAME);

            EXPECT_TRUE(err1 == error::None);
            ASSERT_TRUE(ret1.isEmpty());

            // Validate the behavior of the method.
            EXPECT_TRUE(animal::test_method_setAnimalName_non_const_lvalue_ref_args(animal));
        }

        // Ensure that all instances are cleaned up.
        EXPECT_TRUE(animal::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    /*
    * @brief Test that a const L-value reference binds only to the corresponding overload.
    *
    * This test verifies that the reflection system correctly identifies and invokes the method
    * overload that accepts a const L-value reference (`const std::string&`). */
    TEST(PerfectForwardingTest, overload_resolution_with_const_lvaue_ref_on_stack_object)
    {
        {
            // Retrieve the metadata for the "Animal" class.
            optional<Record> classAnimal = cxx::mirror().getRecord(animal::class_);
            ASSERT_TRUE(classAnimal);

            // Create an instance of the "Animal" class.
            auto [err0, animal] = classAnimal->ctorT()(alloc::Stack);
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(animal.isEmpty());

            // Retrieve the "setAnimalName" method.
            optional<Method> oSetAnimalName = classAnimal->getMethod(animal::str_setAnimalName);
            ASSERT_TRUE(oSetAnimalName);
            // Verify that the method has the correct signature for a const L-value reference.
            EXPECT_TRUE((oSetAnimalName->hasSignature<const std::string&>()));

            auto setAnimalName = oSetAnimalName->targetT().argsT<std::string>().returnT();
            EXPECT_TRUE(setAnimalName);

            // Invoke the method with a const L-value reference.
            auto [err1, ret1] = setAnimalName.bind<const std::string&>(animal)(animal::NAME);

            EXPECT_TRUE(err1 == error::None);
            EXPECT_TRUE(ret1.isEmpty());

            // Validate the behavior of the method.
            EXPECT_TRUE(animal::test_method_setAnimalName_const_lvalue_ref_args(animal));
        }

        // Ensure that all instances are cleaned up.
        EXPECT_TRUE(animal::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(PerfectForwardingTest, static_fn_overload_resolution_with_rvalue_ref)
    {
        {
            optional<Record> classAnimal = cxx::mirror().getRecord(animal::class_);
            ASSERT_TRUE(classAnimal);

            optional<Method> oUpdateZooKeeper = classAnimal->getMethod(animal::str_updateZooKeeper);
            ASSERT_TRUE(oUpdateZooKeeper);

            const auto& isValid = oUpdateZooKeeper->hasSignature<std::string&&>();
            EXPECT_TRUE(isValid);

            auto updateZooKeeper = oUpdateZooKeeper->argsT<std::string>().returnT<>();
            {
                auto [err, ret] = updateZooKeeper(animal::ZOO_KEEPER);
                EXPECT_TRUE(err == error::ExplicitRefBindingRequired);
                EXPECT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = updateZooKeeper.bind<std::string&&>()(animal::ZOO_KEEPER);

                EXPECT_TRUE(err == error::None);
                ASSERT_FALSE(ret.isEmpty());
                EXPECT_TRUE(ret.canViewAs<string>());

                const string& retStr = ret.view<string>()->get();
                EXPECT_TRUE(animal::test_method_updateZooKeeper<std::string&&>(retStr));
            }
        }

        EXPECT_TRUE(animal::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(PerfectForwardingTest, static_fn_overload_resolution_with_const_lvalue_ref)
    {
        {
            optional<Record> classAnimal = cxx::mirror().getRecord(animal::class_);
            ASSERT_TRUE(classAnimal);

            optional<Method> oUpdateZooKeeper = classAnimal->getMethod(animal::str_updateZooKeeper);
            ASSERT_TRUE(oUpdateZooKeeper);

            const auto& isValid = oUpdateZooKeeper->hasSignature<const std::string&>();
            EXPECT_TRUE(isValid);

            rtl::static_method<rtl::Return(std::string)> updateZooKeeper = oUpdateZooKeeper->argsT<std::string>()
                                                                                            .returnT<>();

            auto [err, ret] = updateZooKeeper.bind<const std::string&>()(animal::ZOO_KEEPER);

            EXPECT_TRUE(err == error::None);
            ASSERT_FALSE(ret.isEmpty());
            EXPECT_TRUE(ret.canViewAs<string>());

            const string& retStr = ret.view<string>()->get();
            EXPECT_TRUE(animal::test_method_updateZooKeeper<const std::string&>(retStr));
        }

        EXPECT_TRUE(animal::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(PerfectForwardingTest, static_fn_overload_resolution_with_non_const_lvalue_ref)
    {
        {
            optional<Record> classAnimal = cxx::mirror().getRecord(animal::class_);
            ASSERT_TRUE(classAnimal);

            optional<Method> oUpdateZooKeeper = classAnimal->getMethod(animal::str_updateZooKeeper);
            ASSERT_TRUE(oUpdateZooKeeper);

            const auto& isValid = oUpdateZooKeeper->hasSignature<const std::string&>();
            EXPECT_TRUE(isValid);

            rtl::static_method<rtl::Return(std::string)> updateZooKeeper = oUpdateZooKeeper->argsT<std::string>()
                                                                                            .returnT<>();
            auto [err, ret] = updateZooKeeper.bind<std::string&>()(animal::ZOO_KEEPER);

            EXPECT_TRUE(err == error::None);
            ASSERT_FALSE(ret.isEmpty());
            EXPECT_TRUE(ret.canViewAs<string>());

            const string& retStr = ret.view<string>()->get();
            EXPECT_TRUE(animal::test_method_updateZooKeeper<std::string&>(retStr));
        }

        EXPECT_TRUE(animal::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }
}