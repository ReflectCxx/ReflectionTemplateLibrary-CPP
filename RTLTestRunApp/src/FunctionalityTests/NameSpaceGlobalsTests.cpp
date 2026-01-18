
#include <rtl_access.h>
#include <gtest/gtest.h>

#include <complex>

#include "TestMirrorProvider.h"
#include "GlobalTestUtils.h"

using namespace std;
using namespace rtl;

using namespace test_utils;
using namespace test_mirror;

namespace rtl_tests
{

    TEST(Reflecting_pod, construct_char_on_heap_and_stack)
    {
        optional<Record> charType = cxx::mirror().getRecord(cxx::reflected_id("char"));
        ASSERT_TRUE(charType);
        {
    /*      Attempting to construct a POD type('char') with a value directly via Record::create<>().
            Although the constructor for 'char' is registered, this call is resolved as if invoking
            a copy constructor(signature: (const char&)), which is implicitly registered.

            Design Restriction :
                - Direct invocation of copy constructors through Record::create<>() is intentionally disallowed.
                - Copy construction is only permitted when cloning an existing reflected object
                using RObject::clone<>().

            Rationale :
                - If the caller already knows the type 'T', there is no need to reflect its copy constructor
                through create<>().A normal C++ copy(e.g., `T(other)`) is simpler and clearer.
                - The only valid scenario for reflecting a copy constructor is when you are handling 'T'
                as type-erased, for that, RTL provides rtl::reflect(..), which wraps an existing 'T'
                into an RObject in a type-erased manner. (demonstrated in next test case.)
            Therefore, this call yields 'SignatureMismatch' by design.
    */      
            auto [err, rchar] = charType->ctorT<char>()(rtl::alloc::Stack, 'Q');
            EXPECT_TRUE(err == rtl::error::SignatureMismatch);
            ASSERT_TRUE(rchar.isEmpty());
        } {
            auto [err, rchar] = charType->ctorT()(rtl::alloc::Stack);
            EXPECT_TRUE(err == rtl::error::None);
            ASSERT_FALSE(rchar.isEmpty());
        }
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
        {
            auto [err, rchar] = charType->ctorT()(rtl::alloc::Heap);
            EXPECT_TRUE(err == rtl::error::None);
            ASSERT_FALSE(rchar.isEmpty());
            ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 1);
        }
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(Reflecting_pod, construct_char_directly_and_clone)
    {
        //Now for cases, if you want to handle it type-erased and pass around.
        RObject reflChar = rtl::reflect('Q');
        {
            //Internally calls the copy constructor.
            auto [err, rchar] = reflChar.clone<rtl::alloc::Stack>();
            EXPECT_TRUE(err == rtl::error::None);
            ASSERT_FALSE(rchar.isEmpty());
            EXPECT_TRUE(rchar.canViewAs<char>());

            auto viewCh = rchar.view<char>();
            ASSERT_TRUE(viewCh);

            char ch = viewCh->get();
            EXPECT_EQ(ch, 'Q');
        }
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
        {
            //Internally calls the copy constructor.
            auto [err, rchar] = reflChar.clone<rtl::alloc::Heap>();
            EXPECT_TRUE(err == rtl::error::None);
            ASSERT_FALSE(rchar.isEmpty());

            ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 1);
            EXPECT_TRUE(rchar.canViewAs<char>());

            // Internally, RTL manages all Heap allocated objects with std::unique_ptr.
            EXPECT_TRUE(rchar.canViewAs<std::unique_ptr<char>>());

            auto viewCh = rchar.view<char>();
            ASSERT_TRUE(viewCh);

            char ch = viewCh->get();
            EXPECT_EQ(ch, 'Q');
        }
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(RTLInterfaceCxxMirror, get_global_functions_with_wrong_names)
    {
        {
            optional<Function> badFunc = cxx::mirror().getFunction("wrong_namespace", "wrong_function");
            EXPECT_FALSE(badFunc);
        } {
            optional<Function> badFunc = cxx::mirror().getFunction(str_complex, "wrong_function");
            EXPECT_FALSE(badFunc);
        } {
            optional<Function> badFunc = cxx::mirror().getFunction("wrong_getComplexNumAsString");
            EXPECT_FALSE(badFunc);
        }
    }


    TEST(FunctionInNameSpace, get_namespace_function_types)
    {
        optional<Function> setReal = cxx::mirror().getFunction(str_complex, str_setReal);
        ASSERT_TRUE(setReal);

        optional<Function> setImaginary = cxx::mirror().getFunction(str_complex, str_setImaginary);
        ASSERT_TRUE(setImaginary);

        EXPECT_TRUE(setReal->getNamespace() == str_complex);
        EXPECT_TRUE(setReal->getFunctionName() == str_setReal);
        EXPECT_TRUE(setImaginary->getNamespace() == str_complex);
        EXPECT_TRUE(setImaginary->getFunctionName() == str_setImaginary);
    }


    TEST(FunctionInNameSpace, namespace_function_execute_return)
    {
        {
            optional<Function> fnSetReal = cxx::mirror().getFunction(str_complex, str_setReal);
            ASSERT_TRUE(fnSetReal);
            EXPECT_TRUE(fnSetReal->hasSignature<double>());

            rtl::function<rtl::Return(double)> setReal = fnSetReal->argsT<double>().returnT<>();
            EXPECT_TRUE(setReal);
            EXPECT_EQ(setReal.get_init_error(), rtl::error::None);

            auto [err, ret] = setReal(g_real);
            EXPECT_TRUE(err == rtl::error::None);
            ASSERT_TRUE(ret.isEmpty());
        } {
            optional<Function> fnSetImaginary = cxx::mirror().getFunction(str_complex, str_setImaginary);
            ASSERT_TRUE(fnSetImaginary);
            EXPECT_TRUE(fnSetImaginary->hasSignature<double>());

            rtl::function<rtl::Return(double)> setImginary = fnSetImaginary->argsT<double>().returnT<>();
            EXPECT_TRUE(setImginary);
            EXPECT_EQ(setImginary.get_init_error(), rtl::error::None);

            auto [err, ret] = setImginary(g_imaginary);
            EXPECT_TRUE(err == rtl::error::None);
            ASSERT_TRUE(ret.isEmpty());
        } {
            optional<Function> fnGetMagnitude = cxx::mirror().getFunction(str_complex, str_getMagnitude);
            ASSERT_TRUE(fnGetMagnitude);
            EXPECT_TRUE(fnGetMagnitude->hasSignature<>()); //empty template params checks for zero arguments.

            rtl::function<rtl::Return()> getMagnitude = fnGetMagnitude->argsT<>().returnT<>();
            EXPECT_TRUE(getMagnitude);
            EXPECT_EQ(getMagnitude.get_init_error(), rtl::error::None);

            auto [err, ret] = getMagnitude();
            EXPECT_TRUE(err == rtl::error::None);
            ASSERT_FALSE(ret.isEmpty());
            EXPECT_TRUE(ret.canViewAs<double>());

            double retVal = ret.view<double>()->get();
            double magnitude = abs(complex(g_real, g_imaginary));
            EXPECT_DOUBLE_EQ(magnitude, retVal);
        }
    }


    TEST(FunctionInNameSpace, execute_with_wrong_signature)
    {
        optional<Function> fnSetReal = cxx::mirror().getFunction(str_complex, str_setReal);
        ASSERT_TRUE(fnSetReal);

        EXPECT_TRUE(fnSetReal->hasSignature<double>());
        EXPECT_FALSE(fnSetReal->hasSignature<float>());

        rtl::function<rtl::Return(float)> setReal = fnSetReal->argsT<float>().returnT<>();
        EXPECT_FALSE(setReal);
        EXPECT_EQ(setReal.get_init_error(), rtl::error::SignatureMismatch);

        auto [err, robj] = setReal(g_real);
        EXPECT_EQ(err, rtl::error::SignatureMismatch);
        EXPECT_TRUE(robj.isEmpty());
    }


    TEST(GlobalFunction, get_function_execute_return)
    {
        optional<Function> fnGetComplexAsStr = cxx::mirror().getFunction(str_getComplexNumAsString);
        ASSERT_TRUE(fnGetComplexAsStr);

        rtl::function<rtl::Return()> getComplexNumAsStr = fnGetComplexAsStr->argsT<>().returnT<>();
        EXPECT_TRUE(getComplexNumAsStr);
        EXPECT_EQ(getComplexNumAsStr.get_init_error(), rtl::error::None);

        auto [err, ret] = getComplexNumAsStr();
        EXPECT_TRUE(err == rtl::error::None);
        ASSERT_FALSE(ret.isEmpty());
        EXPECT_TRUE(ret.canViewAs<string>());

        string retVal = ret.view<std::string>()->get();
        string comlexNumStr = to_string(g_real) + "i" + to_string(g_imaginary);
        EXPECT_TRUE(comlexNumStr == retVal);
    }


    TEST(GlobalFunction, overloaded_function_execute_return)
    {
        optional<Function> fnReverseString = cxx::mirror().getFunction(str_reverseString);
        ASSERT_TRUE(fnReverseString);

        rtl::function<rtl::Return(std::string)> reverseString = fnReverseString->argsT<std::string>().returnT<>();
        ASSERT_TRUE(reverseString);
        {
            //STRA's type is 'const char*', function accepts 'string',
            //so type-casting in place as 'string'
            auto [err, ret] = reverseString(STRA);
            EXPECT_TRUE(err == rtl::error::None);
            ASSERT_FALSE(ret.isEmpty());
            EXPECT_TRUE(ret.canViewAs<string>());

            string retStr = ret.view<std::string>()->get();
            auto expStr = std::string(STRA_REVERSE) + SUFFIX_std_string;
            EXPECT_EQ(retStr, expStr);
        } {
            //STRB's type is 'const char*', function accepts 'string',
            //so explicitly binding type in template (using bind<...>()) to enforce the type as 'string'.
            auto [err, ret] = reverseString(STRB);

            EXPECT_TRUE(err == rtl::error::None);
            ASSERT_FALSE(ret.isEmpty());
            EXPECT_TRUE(ret.canViewAs<string>());

            string retStr = ret.view<std::string>()->get();
            auto expStr = std::string(STRB_REVERSE) + SUFFIX_std_string;
            EXPECT_EQ(retStr, expStr);
        } {
            rtl::function<rtl::Return()> reverseString = fnReverseString->argsT<>().returnT<>();

            auto [err, ret] = reverseString();
            EXPECT_TRUE(err == rtl::error::None);
            ASSERT_FALSE(ret.isEmpty());
            EXPECT_TRUE(ret.canViewAs<string>());
            
            string retStr = ret.view<std::string>()->get();
            auto expStr = std::string(REV_STR_VOID_RET) + SUFFIX_void;
            EXPECT_EQ(retStr, expStr);
        }
    }


    TEST(Reflecting_STL_class, std_string__call_reflected_method)
    {
        optional<Record> stdStringClass = cxx::mirror().getRecord("std", "string");
        ASSERT_TRUE(stdStringClass);

        optional<Method> fnIsStringEmpty = stdStringClass->getMethod("empty");
        ASSERT_TRUE(fnIsStringEmpty);

        RObject reflected_str0 = rtl::reflect(std::string(""));	//empty string.
        {
            auto isStringEmpty = fnIsStringEmpty->targetT().argsT().returnT();
            EXPECT_TRUE(isStringEmpty);

            auto [err, ret] = isStringEmpty(std::cref(reflected_str0))();
            EXPECT_TRUE(err == rtl::error::None);
            ASSERT_FALSE(ret.isEmpty());
            EXPECT_TRUE(ret.canViewAs<bool>());
            EXPECT_TRUE(ret.view<bool>()->get());
        }
        RObject reflected_str1 = rtl::reflect(std::string("not_empty"));
        {
            auto isStringEmpty = fnIsStringEmpty->targetT().argsT().returnT();
            EXPECT_TRUE(isStringEmpty);

            auto [err, ret] = isStringEmpty(std::cref(reflected_str1))();
            EXPECT_TRUE(err == rtl::error::None);
            ASSERT_FALSE(ret.isEmpty());
            EXPECT_TRUE(ret.canViewAs<bool>());
            EXPECT_FALSE(ret.view<bool>()->get());
        }
    }


    TEST(Reflecting_STL_class, std_string_view__call_reflected_method)
    {
        optional<Record> stdStringClass = cxx::mirror().getRecord("std", "string_view");
        ASSERT_TRUE(stdStringClass);

        optional<Method> fnIsStringEmpty = stdStringClass->getMethod("empty");
        ASSERT_TRUE(fnIsStringEmpty);

        RObject reflected_str0 = rtl::reflect("");	//empty string.
        {
            auto isStringEmpty = fnIsStringEmpty->targetT().argsT().returnT();
            EXPECT_TRUE(isStringEmpty);

            auto [err, ret] = isStringEmpty(std::cref(reflected_str0))();
            EXPECT_TRUE(err == rtl::error::None);
            ASSERT_FALSE(ret.isEmpty());
            EXPECT_TRUE(ret.canViewAs<bool>());
            EXPECT_TRUE(ret.view<bool>()->get());
        }
        RObject reflected_str1 = rtl::reflect("not_empty");
        {
            auto isStringEmpty = fnIsStringEmpty->targetT().argsT().returnT();
            EXPECT_TRUE(isStringEmpty);

            auto [err, ret] = isStringEmpty(std::cref(reflected_str1))();
            EXPECT_TRUE(err == rtl::error::None);
            ASSERT_FALSE(ret.isEmpty());
            EXPECT_TRUE(ret.canViewAs<bool>());
            EXPECT_FALSE(ret.view<bool>()->get());
        }
    }
}