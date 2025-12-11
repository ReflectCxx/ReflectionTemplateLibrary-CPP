
#include <rtl/access.h>
#include <rtl/rtl_constructor.h>

#include <gtest/gtest.h>

namespace rtl_tests
{
	TEST(TargetTypeErased_rtl_constructor, invalid_erased_return_rtl_constructor)
	{
		{
			rtl::constructor<int> ctor;
			EXPECT_FALSE(ctor);

			auto [err, robj] = ctor(rtl::alloc::Stack, 0);
			EXPECT_EQ(err, rtl::error::InvalidCaller);
			EXPECT_TRUE(robj.isEmpty());
		}
	}
}