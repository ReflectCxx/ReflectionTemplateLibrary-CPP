
#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsDate.h"
#include "TestUtilsAnimal.h"

using namespace std;
using namespace rtl;
using namespace test_utils;
using namespace rtl::access;

namespace rtl_tests
{
    TEST(rtl_InstanceClassTest, instance_copy_construct_on_stack)
    {
        EXPECT_TRUE(date::assert_zero_instance_count());
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> structDate = cxxMirror.getRecord(date::ns, date::struct_);
            ASSERT_TRUE(structDate);
            
            auto [status, dateObj] = structDate->instance<alloc::Stack>();
			ASSERT_TRUE(status);

            EXPECT_TRUE(Instance::getInstanceCount() == 1);
            {
                Instance instance = dateObj;

                ASSERT_FALSE(instance.isEmpty() && dateObj.isEmpty());
                ASSERT_FALSE(instance.isConst() && dateObj.isConst());
                ASSERT_FALSE(instance.isOnHeap() && dateObj.isOnHeap());
                ASSERT_TRUE(instance.getTypeId() == dateObj.getTypeId());
                ASSERT_TRUE(date::test_if_obejcts_are_equal(instance.get(), dateObj.get(), false));
                
                optional<Method> updateDate = structDate->getMethod(date::str_updateDate);
                ASSERT_TRUE(updateDate);
                
                string dateStr = date::DATE_STR1;
                auto status = updateDate->bind(dateObj).call(dateStr);
                ASSERT_TRUE(status);
                ASSERT_FALSE(date::test_if_obejcts_are_equal(instance.get(), dateObj.get(), false));
                
                EXPECT_TRUE(Instance::getInstanceCount() == 2);
            }
            EXPECT_TRUE(Instance::getInstanceCount() == 1);
        }
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
		EXPECT_TRUE(date::assert_zero_instance_count());
    }


    TEST(rtl_InstanceClassTest, instance_copy_sharing_heap_object)
    {
        EXPECT_TRUE(date::assert_zero_instance_count());
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> structDate = cxxMirror.getRecord(date::ns, date::struct_);
            ASSERT_TRUE(structDate);

            auto [status, dateObj] = structDate->instance<alloc::Heap>();
            ASSERT_TRUE(status);

            EXPECT_TRUE(Instance::getInstanceCount() == 1);
            {
                Instance instance = dateObj;

                ASSERT_FALSE(instance.isEmpty() && dateObj.isEmpty());
                ASSERT_FALSE(instance.isConst() && dateObj.isConst());
                ASSERT_TRUE(instance.isOnHeap() && dateObj.isOnHeap());
                ASSERT_TRUE(instance.getTypeId() == dateObj.getTypeId());
                ASSERT_TRUE(date::test_if_obejcts_are_equal(instance.get(), dateObj.get(), true));

                optional<Method> updateDate = structDate->getMethod(date::str_updateDate);
                ASSERT_TRUE(updateDate);

                string dateStr = date::DATE_STR1;
                auto status = updateDate->bind(dateObj).call(dateStr);
                ASSERT_TRUE(status);
                ASSERT_TRUE(date::test_if_obejcts_are_equal(instance.get(), dateObj.get(), true));

                EXPECT_TRUE(Instance::getInstanceCount() == 2);
            }
            EXPECT_TRUE(Instance::getInstanceCount() == 1);
        }
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        EXPECT_TRUE(date::assert_zero_instance_count());
    }


    TEST(rtl_InstanceClassTest, assignment_of_instances_on_stack)
    {
        EXPECT_TRUE(date::assert_zero_instance_count());
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> structDate = cxxMirror.getRecord(date::ns, date::struct_);
            ASSERT_TRUE(structDate);

            auto [status, dateObj] = structDate->instance<alloc::Stack>();
            ASSERT_TRUE(status);

            EXPECT_TRUE(Instance::getInstanceCount() == 1);
            {
                Instance instance;
                instance = dateObj;

                ASSERT_FALSE(instance.isEmpty() && dateObj.isEmpty());
                ASSERT_FALSE(instance.isConst() && dateObj.isConst());
                ASSERT_FALSE(instance.isOnHeap() && dateObj.isOnHeap());
                ASSERT_TRUE(instance.getTypeId() == dateObj.getTypeId());
                ASSERT_TRUE(date::test_if_obejcts_are_equal(instance.get(), dateObj.get(), false));

                optional<Method> updateDate = structDate->getMethod(date::str_updateDate);
                ASSERT_TRUE(updateDate);

                string dateStr = date::DATE_STR1;
                ASSERT_TRUE((updateDate->bind(dateObj).call(dateStr)));
                ASSERT_FALSE(date::test_if_obejcts_are_equal(instance.get(), dateObj.get(), false));

                EXPECT_TRUE(Instance::getInstanceCount() == 2);
            }
            EXPECT_TRUE(Instance::getInstanceCount() == 1);
        }
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        EXPECT_TRUE(date::assert_zero_instance_count());
    }


    TEST(rtl_InstanceClassTest, assignment_of_instances_sharing_heap)
    {
        EXPECT_TRUE(date::assert_zero_instance_count());
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> structDate = cxxMirror.getRecord(date::ns, date::struct_);
            ASSERT_TRUE(structDate);

            auto [status, dateObj] = structDate->instance<alloc::Heap>();
            ASSERT_TRUE(status);

            EXPECT_TRUE(Instance::getInstanceCount() == 1);
            {
                Instance instance;
                instance = dateObj;

                ASSERT_FALSE(instance.isEmpty() && dateObj.isEmpty());
                ASSERT_FALSE(instance.isConst() && dateObj.isConst());
                ASSERT_TRUE(instance.isOnHeap() && dateObj.isOnHeap());
                ASSERT_TRUE(instance.getTypeId() == dateObj.getTypeId());
                ASSERT_TRUE(date::test_if_obejcts_are_equal(instance.get(), dateObj.get(), true));

                optional<Method> updateDate = structDate->getMethod(date::str_updateDate);
                ASSERT_TRUE(updateDate);

                string dateStr = date::DATE_STR1;
                ASSERT_TRUE((updateDate->bind(dateObj).call(dateStr)));
                ASSERT_TRUE(date::test_if_obejcts_are_equal(instance.get(), dateObj.get(), true));

                EXPECT_TRUE(Instance::getInstanceCount() == 2);
            }
            EXPECT_TRUE(Instance::getInstanceCount() == 1);
        }
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        EXPECT_TRUE(date::assert_zero_instance_count());
    }


    TEST(rtl_InstanceClassTest, assignment_of_instances_with_unique_heaps)
    {
        EXPECT_TRUE(date::assert_zero_instance_count());
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> structDate = cxxMirror.getRecord(date::ns, date::struct_);
            ASSERT_TRUE(structDate);

            auto [status, dateObj] = structDate->instance<alloc::Heap>();
            ASSERT_TRUE(status);

            EXPECT_TRUE(Instance::getInstanceCount() == 1);
            {
                auto [status0, instance] = structDate->instance<alloc::Heap>();
                ASSERT_TRUE(status0);

                optional<Method> updateDate = structDate->getMethod(date::str_updateDate);
                ASSERT_TRUE(updateDate);

                string dateStr = date::DATE_STR1;
                ASSERT_TRUE((updateDate->bind(dateObj).call(dateStr)));
                ASSERT_FALSE(date::test_if_obejcts_are_equal(instance.get(), dateObj.get(), true));

                instance = dateObj;

                ASSERT_FALSE(instance.isEmpty() && dateObj.isEmpty());
                ASSERT_FALSE(instance.isConst() && dateObj.isConst());
                ASSERT_TRUE(instance.isOnHeap() && dateObj.isOnHeap());
                ASSERT_TRUE(instance.getTypeId() == dateObj.getTypeId());
                ASSERT_TRUE(date::test_if_obejcts_are_equal(instance.get(), dateObj.get(), true));

                EXPECT_TRUE(Instance::getInstanceCount() == 2);
            }
            EXPECT_TRUE(Instance::getInstanceCount() == 1);
        }
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        EXPECT_TRUE(date::assert_zero_instance_count());
    }


    TEST(rtl_InstanceClassTest, instance_move_construct_on_stack)
    {
        EXPECT_TRUE(date::assert_zero_instance_count());
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> structDate = cxxMirror.getRecord(date::ns, date::struct_);
            ASSERT_TRUE(structDate);

            auto [status, dateObj] = structDate->instance<alloc::Stack>();
            ASSERT_TRUE(status);

            ASSERT_FALSE(dateObj.isEmpty());
            ASSERT_FALSE(dateObj.isConst());
            ASSERT_FALSE(dateObj.isOnHeap());

            EXPECT_TRUE(Instance::getInstanceCount() == 1);
            {
                Instance instance = std::move(dateObj);

                ASSERT_TRUE(dateObj.isEmpty());
                ASSERT_FALSE(instance.isEmpty());
                ASSERT_FALSE(instance.getTypeId() == dateObj.getTypeId());

                optional<Method> updateDate = structDate->getMethod(date::str_updateDate);
                ASSERT_TRUE(updateDate);

                string dateStr = date::DATE_STR1;
                ASSERT_TRUE(updateDate->bind(instance).call(dateStr));
                ASSERT_TRUE(updateDate->bind(dateObj).call(dateStr) == rtl::Error::EmptyInstance);
                EXPECT_TRUE(Instance::getInstanceCount() == 2);
            }
            EXPECT_TRUE(Instance::getInstanceCount() == 1);
        }
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        EXPECT_TRUE(date::assert_zero_instance_count());
    }


    TEST(rtl_InstanceClassTest, instance_move_construct_shared_heap)
    {
        EXPECT_TRUE(date::assert_zero_instance_count());
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> structDate = cxxMirror.getRecord(date::ns, date::struct_);
            ASSERT_TRUE(structDate);

            auto [status, dateObj] = structDate->instance<alloc::Heap>();
            ASSERT_TRUE(status);

            ASSERT_FALSE(dateObj.isEmpty());
            ASSERT_FALSE(dateObj.isConst());
            ASSERT_TRUE(dateObj.isOnHeap());

            EXPECT_TRUE(Instance::getInstanceCount() == 1);
            {
                Instance instance = std::move(dateObj);

                ASSERT_TRUE(dateObj.isEmpty());
                ASSERT_FALSE(dateObj.isOnHeap());

                ASSERT_TRUE(instance.isOnHeap());
                ASSERT_FALSE(instance.isEmpty());
                ASSERT_FALSE(instance.getTypeId() == dateObj.getTypeId());

                optional<Method> updateDate = structDate->getMethod(date::str_updateDate);
                ASSERT_TRUE(updateDate);

                string dateStr = date::DATE_STR1;
                ASSERT_TRUE(updateDate->bind(instance).call(dateStr));
                ASSERT_TRUE(updateDate->bind(dateObj).call(dateStr) == rtl::Error::EmptyInstance);
                EXPECT_TRUE(Instance::getInstanceCount() == 2);
            }
            EXPECT_TRUE(Instance::getInstanceCount() == 1);
        }
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        EXPECT_TRUE(date::assert_zero_instance_count());
    }


    TEST(rtl_InstanceClassTest, instance_move_assignment_on_stack)
    {
        EXPECT_TRUE(date::assert_zero_instance_count());
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> structDate = cxxMirror.getRecord(date::ns, date::struct_);
            ASSERT_TRUE(structDate);

            auto [status, dateObj] = structDate->instance<alloc::Stack>();
            ASSERT_TRUE(status);

            ASSERT_FALSE(dateObj.isEmpty());
            ASSERT_FALSE(dateObj.isConst());
            ASSERT_FALSE(dateObj.isOnHeap());

            EXPECT_TRUE(Instance::getInstanceCount() == 1);
            {
                Instance instance;
                instance = std::move(dateObj);

                ASSERT_TRUE(dateObj.isEmpty());
                ASSERT_FALSE(instance.isEmpty());
                ASSERT_FALSE(instance.getTypeId() == dateObj.getTypeId());

                optional<Method> updateDate = structDate->getMethod(date::str_updateDate);
                ASSERT_TRUE(updateDate);

                string dateStr = date::DATE_STR1;
                ASSERT_TRUE(updateDate->bind(instance).call(dateStr));
                ASSERT_TRUE(updateDate->bind(dateObj).call(dateStr) == rtl::Error::EmptyInstance);
                EXPECT_TRUE(Instance::getInstanceCount() == 2);
            }
            EXPECT_TRUE(Instance::getInstanceCount() == 1);
        }
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        EXPECT_TRUE(date::assert_zero_instance_count());
    }


    TEST(rtl_InstanceClassTest, instance_move_assignment_with_shared_heap)
    {
        EXPECT_TRUE(date::assert_zero_instance_count());
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> structDate = cxxMirror.getRecord(date::ns, date::struct_);
            ASSERT_TRUE(structDate);

            auto [status, dateObj] = structDate->instance<alloc::Heap>();
            ASSERT_TRUE(status);

            ASSERT_FALSE(dateObj.isEmpty());
            ASSERT_FALSE(dateObj.isConst());
            ASSERT_TRUE(dateObj.isOnHeap());

            EXPECT_TRUE(Instance::getInstanceCount() == 1);
            {
                Instance instance;
                instance = std::move(dateObj);

                ASSERT_TRUE(dateObj.isEmpty());
                ASSERT_FALSE(instance.isEmpty());
                ASSERT_FALSE(instance.getTypeId() == dateObj.getTypeId());

                optional<Method> updateDate = structDate->getMethod(date::str_updateDate);
                ASSERT_TRUE(updateDate);

                string dateStr = date::DATE_STR1;
                ASSERT_TRUE(updateDate->bind(instance).call(dateStr));
                ASSERT_TRUE(updateDate->bind(dateObj).call(dateStr) == rtl::Error::EmptyInstance);
                EXPECT_TRUE(Instance::getInstanceCount() == 2);
            }
            EXPECT_TRUE(Instance::getInstanceCount() == 1);
        }
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        EXPECT_TRUE(date::assert_zero_instance_count());
    }


    TEST(rtl_InstanceClassTest, std_any_large_heap_object_deep_move_or_copy___move_or_copy_ctor_must_not_be_called)
    {
        EXPECT_TRUE(date::assert_zero_instance_count());
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> animal = cxxMirror.getRecord(animal::class_);
            ASSERT_TRUE(animal);

            auto [status, animalObj] = animal->instance<alloc::Heap>();
            ASSERT_TRUE(status);

            ASSERT_FALSE(animalObj.isEmpty());
            ASSERT_FALSE(animalObj.isConst());
            ASSERT_TRUE(animalObj.isOnHeap());

            optional<Method> setFamilyName = animal->getMethod(animal::str_setFamilyName);
            ASSERT_TRUE(setFamilyName);

			const auto& familyName = std::string(animal::FAMILY_NAME);
            ASSERT_TRUE((*setFamilyName)(animalObj)(familyName));

            EXPECT_TRUE(Instance::getInstanceCount() == 1);
            {
                Instance movedToObj = std::move(animalObj);

                ASSERT_TRUE(animalObj.isEmpty());
                ASSERT_FALSE(movedToObj.isEmpty());
                ASSERT_FALSE(movedToObj.getTypeId() == animalObj.getTypeId());

                optional<Method> getFamilyName = animal->getMethod(animal::str_getFamilyName);
                ASSERT_TRUE(getFamilyName);

                const auto& status = (*getFamilyName)(movedToObj)();
                ASSERT_TRUE(status);

                ASSERT_TRUE(status.getReturn().has_value());
                ASSERT_TRUE(status.isOfType<string>());

                const std::string& retStr = any_cast<string>(status.getReturn());
                ASSERT_EQ(retStr, familyName);

                EXPECT_TRUE(Instance::getInstanceCount() == 2);
            }
            EXPECT_TRUE(Instance::getInstanceCount() == 1);
        }
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        EXPECT_TRUE(date::assert_zero_instance_count());
    }


    TEST(rtl_InstanceClassTest, std_any_large_stack_object_deep_move_or_copy___move_or_copy_ctor_must_not_be_called)
    {
        EXPECT_TRUE(date::assert_zero_instance_count());
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> animal = cxxMirror.getRecord(animal::class_);
            ASSERT_TRUE(animal);

            auto [status, animalObj] = animal->instance<alloc::Stack>();
            ASSERT_TRUE(status);

            ASSERT_FALSE(animalObj.isEmpty());
            ASSERT_FALSE(animalObj.isConst());
            ASSERT_FALSE(animalObj.isOnHeap());

            optional<Method> setFamilyName = animal->getMethod(animal::str_setFamilyName);
            ASSERT_TRUE(setFamilyName);

            const auto& familyName = std::string(animal::FAMILY_NAME);
            ASSERT_TRUE((*setFamilyName)(animalObj)(familyName));

            EXPECT_TRUE(Instance::getInstanceCount() == 1);
            {
                Instance movedToObj = std::move(animalObj);

                ASSERT_TRUE(animalObj.isEmpty());
                ASSERT_FALSE(movedToObj.isEmpty());
                ASSERT_FALSE(movedToObj.getTypeId() == animalObj.getTypeId());

                optional<Method> getFamilyName = animal->getMethod(animal::str_getFamilyName);
                ASSERT_TRUE(getFamilyName);

                const auto& status = (*getFamilyName)(movedToObj)();
                ASSERT_TRUE(status);

                ASSERT_TRUE(status.getReturn().has_value());
                ASSERT_TRUE(status.isOfType<string>());

                const std::string& retStr = any_cast<string>(status.getReturn());
                ASSERT_EQ(retStr, familyName);

                EXPECT_TRUE(Instance::getInstanceCount() == 2);
            }
            EXPECT_TRUE(Instance::getInstanceCount() == 1);
        }
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        EXPECT_TRUE(date::assert_zero_instance_count());
    }


    TEST(rtl_InstanceClassTest, std_any_large_heap_object_deep_move___move_assignemt_must_not_be_called)
    {
        EXPECT_TRUE(date::assert_zero_instance_count());
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> animal = cxxMirror.getRecord(animal::class_);
            ASSERT_TRUE(animal);

            auto [status, animalObj] = animal->instance<alloc::Heap>();
            ASSERT_TRUE(status);

            ASSERT_FALSE(animalObj.isEmpty());
            ASSERT_FALSE(animalObj.isConst());
            ASSERT_TRUE(animalObj.isOnHeap());

            optional<Method> setFamilyName = animal->getMethod(animal::str_setFamilyName);
            ASSERT_TRUE(setFamilyName);

            const auto& familyName = std::string(animal::FAMILY_NAME);
            ASSERT_TRUE((*setFamilyName)(animalObj)(familyName));

            EXPECT_TRUE(Instance::getInstanceCount() == 1);
            {
                Instance movedToObj;
                movedToObj = std::move(animalObj);

                ASSERT_TRUE(animalObj.isEmpty());
                ASSERT_FALSE(movedToObj.isEmpty());
                ASSERT_FALSE(movedToObj.getTypeId() == animalObj.getTypeId());

                optional<Method> getFamilyName = animal->getMethod(animal::str_getFamilyName);
                ASSERT_TRUE(getFamilyName);

                const auto& status = (*getFamilyName)(movedToObj)();
                ASSERT_TRUE(status);

                ASSERT_TRUE(status.getReturn().has_value());
                ASSERT_TRUE(status.isOfType<string>());

                const std::string& retStr = any_cast<string>(status.getReturn());
                ASSERT_EQ(retStr, familyName);

                EXPECT_TRUE(Instance::getInstanceCount() == 2);
            }
            EXPECT_TRUE(Instance::getInstanceCount() == 1);
        }
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        EXPECT_TRUE(date::assert_zero_instance_count());
    }


    TEST(rtl_InstanceClassTest, std_any_large_stack_object_deep_move___move_or_copy_assignemt_must_not_be_called)
    {
        EXPECT_TRUE(date::assert_zero_instance_count());
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> animal = cxxMirror.getRecord(animal::class_);
            ASSERT_TRUE(animal);

            auto [status, animalObj] = animal->instance<alloc::Stack>();
            ASSERT_TRUE(status);

            ASSERT_FALSE(animalObj.isEmpty());
            ASSERT_FALSE(animalObj.isConst());
            ASSERT_FALSE(animalObj.isOnHeap());

            optional<Method> setFamilyName = animal->getMethod(animal::str_setFamilyName);
            ASSERT_TRUE(setFamilyName);

            const auto& familyName = std::string(animal::FAMILY_NAME);
            ASSERT_TRUE((*setFamilyName)(animalObj)(familyName));

            EXPECT_TRUE(Instance::getInstanceCount() == 1);
            {
                Instance movedToObj;
                movedToObj = std::move(animalObj);

                ASSERT_TRUE(animalObj.isEmpty());
                ASSERT_FALSE(movedToObj.isEmpty());
                ASSERT_FALSE(movedToObj.getTypeId() == animalObj.getTypeId());

                optional<Method> getFamilyName = animal->getMethod(animal::str_getFamilyName);
                ASSERT_TRUE(getFamilyName);

                const auto& status = (*getFamilyName)(movedToObj)();
                ASSERT_TRUE(status);

                ASSERT_TRUE(status.getReturn().has_value());
                ASSERT_TRUE(status.isOfType<string>());

                const std::string& retStr = any_cast<string>(status.getReturn());
                ASSERT_EQ(retStr, familyName);

                EXPECT_TRUE(Instance::getInstanceCount() == 2);
            }
            EXPECT_TRUE(Instance::getInstanceCount() == 1);
        }
        EXPECT_TRUE(Instance::getInstanceCount() == 0);
        EXPECT_TRUE(date::assert_zero_instance_count());
    }
}