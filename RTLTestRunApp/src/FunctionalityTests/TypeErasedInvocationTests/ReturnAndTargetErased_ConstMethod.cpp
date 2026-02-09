
#include <rtl_access.h>
#include <gtest/gtest.h>

#include "TestMirrorProvider.h"
#include "GlobalTestUtils.h"
#include "../CxxTestProps/inc/StringConstOverload.h"

using namespace test_utils;


namespace rtl_tests
{
    TEST(ReturnAndTargetErased_ConstMethod, auto_resolution_to_const_method)
    {
        std::optional<rtl::Record> recStrConstOverload = cxx::mirror().getRecord(StrConstOverload::struct_);
        ASSERT_TRUE(recStrConstOverload);

        auto testWithAlloc = [&](rtl::alloc pAlloc) 
        {
            auto [err, robj] = recStrConstOverload->ctorT()(pAlloc);
            EXPECT_EQ(err, rtl::error::None);
            EXPECT_TRUE(!robj.isEmpty());

            std::optional<rtl::Method> oReverseString = recStrConstOverload->getMethod(str_reverseString);
            ASSERT_TRUE(oReverseString);

            // Both const & non-const overloads are present for this method.
            rtl::method<rtl::RObject, rtl::Return()> reverseString = oReverseString->targetT().argsT().returnT();
            EXPECT_TRUE(reverseString);
            {
                auto [err, ret] = reverseString(robj)();
                EXPECT_EQ(err, rtl::error::None);
                EXPECT_TRUE(!ret.isEmpty());
                ASSERT_TRUE(ret.canViewAs<std::string>());

                const std::string& retStr = ret.view<std::string>()->get();
                const std::string& expectedStr = std::string(StrConstOverload::struct_) + REV_STR_VOID_RET +
                                                 SUFFIX_void;
                EXPECT_EQ(retStr, expectedStr);
            } {
                auto [err, ret] = reverseString(std::cref(robj))();
                EXPECT_EQ(err, rtl::error::None);
                EXPECT_TRUE(!ret.isEmpty());
                ASSERT_TRUE(ret.canViewAs<std::string>());

                const std::string& retStr = ret.view<std::string>()->get();
                const std::string& expectedStr = std::string(StrConstOverload::struct_) + REV_STR_VOID_RET +
                                                 SUFFIX_void + SUFFIX_const;
                EXPECT_EQ(retStr, expectedStr);
            }
        };

        testWithAlloc(rtl::alloc::Heap);
        testWithAlloc(rtl::alloc::Stack);
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }
}