#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsAnimal.h"

using namespace std;
using namespace rtl;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests
{
	TEST(PerfectForwardingTest, non_const_lvalue_ref_only_binds_to_non_const_lvaue_ref_overload)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classAnimal = cxxMirror.getRecord(animal::class_);
			ASSERT_TRUE(classAnimal);

			optional<Method> setAnimalName = classAnimal->getMethod(animal::str_setAnimalName);
			ASSERT_TRUE(setAnimalName);

			auto [status, animalObj] = classAnimal->instance();

			ASSERT_TRUE(status);
			ASSERT_FALSE(animalObj.isEmpty());

			const auto& isValid = setAnimalName->hasSignature<std::string&>();
			ASSERT_TRUE(isValid);

			auto nameStr = std::string(animal::NAME);
			RStatus rStatus = setAnimalName->on(animalObj).call<std::string&>(nameStr);

			ASSERT_TRUE(rStatus);
			ASSERT_FALSE(rStatus.getReturn().has_value());

			EXPECT_TRUE(animal::test_method_setAnimalName_non_const_lvalue_ref_args(animalObj.get()));
		}

		EXPECT_TRUE(animal::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}
	

	TEST(PerfectForwardingTest, rvalue_ref_only_binds_to_rvalue_ref_overload)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classAnimal = cxxMirror.getRecord(animal::class_);
			ASSERT_TRUE(classAnimal);

			optional<Method> setAnimalName = classAnimal->getMethod(animal::str_setAnimalName);
			ASSERT_TRUE(setAnimalName);

			auto [status, animalObj] = classAnimal->instance();

			ASSERT_TRUE(status);
			ASSERT_FALSE(animalObj.isEmpty());

			const auto& isValid = setAnimalName->hasSignature<std::string&&>();
			ASSERT_TRUE(isValid);

			RStatus rStatus = setAnimalName->on(animalObj).call<std::string&&>(animal::NAME);

			ASSERT_TRUE(rStatus);
			ASSERT_FALSE(rStatus.getReturn().has_value());

			EXPECT_TRUE(animal::test_method_setAnimalName_rvalue_args(animalObj.get()));
		}

		EXPECT_TRUE(animal::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(PerfectForwardingTest, const_lvalue_ref_only_binds_to_const_lvaue_ref_overload)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classAnimal = cxxMirror.getRecord(animal::class_);
			ASSERT_TRUE(classAnimal);

			optional<Method> setAnimalName = classAnimal->getMethod(animal::str_setAnimalName);
			ASSERT_TRUE(setAnimalName);

			auto [status, animalObj] = classAnimal->instance();

			ASSERT_TRUE(status);
			ASSERT_FALSE(animalObj.isEmpty());

			const auto& isValid = setAnimalName->hasSignature<const std::string&>();
			ASSERT_TRUE(isValid);
			
			auto nameStr = std::string(animal::NAME);
			RStatus rStatus = setAnimalName->on(animalObj).call<const std::string&>(nameStr);

			ASSERT_TRUE(rStatus);
			ASSERT_FALSE(rStatus.getReturn().has_value());

			EXPECT_TRUE(animal::test_method_setAnimalName_const_lvalue_ref_args(animalObj.get()));
		}

		EXPECT_TRUE(animal::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}
}