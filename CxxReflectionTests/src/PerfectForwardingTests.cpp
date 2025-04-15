#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsAnimal.h"

using namespace std;
using namespace rtl;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests
{
	TEST(PerfectForwardingTest, temporary_args_string_as_rvalue)
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
			ASSERT_TRUE(setAnimalName->hasSignature<std::string>());

			RStatus rStatus = setAnimalName->on(animalObj).call(std::string(animal::NAME));

			ASSERT_TRUE(rStatus);
			ASSERT_FALSE(rStatus.getReturn().has_value());

			EXPECT_TRUE(animal::test_method_setAnimalName_rvalue_args(animalObj.get()));
		}

		EXPECT_TRUE(animal::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}
}