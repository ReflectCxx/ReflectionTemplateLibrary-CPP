
#include <gtest/gtest.h>
#include <rtl/rtl_access.h>

#include "MyReflectingType.h"

using namespace my_type;

namespace my_type { extern const rtl::CxxMirror& MyReflection(); }

namespace
{
    TEST(MyReflectionTests, invoking_semantics__C_style_function_with_no_overload)
    {
        {
            // Attempt to retrieve the C-style function without specifying a namespace.
            std::optional<rtl::Function> optSendString = MyReflection().getFunction("sendString");
            // Not found, since it was registered under the 'ext' namespace.
            EXPECT_FALSE(optSendString);
        } {
            // Retrieve the function with its correct namespace.
            std::optional<rtl::Function> optSendString = MyReflection().getFunction("ext", "sendString");
            // Found successfully.
            ASSERT_TRUE(optSendString);

            auto sendStringFn = optSendString->argsT<std::string>().returnT<>();
            ASSERT_TRUE(sendStringFn);
            EXPECT_EQ(sendStringFn.get_init_error(), rtl::error::None);

            auto theStr = std::string("Initiating reflection tests.");
            auto expectReturnStr = ("sent_string_" + theStr);

            // Nothing to bind here, since this is a non-member (C-style) function.  
            // However, if the function takes reference parameters that require perfect forwarding,  
            // the binding can be specified explicitly using `bind<T&>()`, `bind<T&&>()`, or `bind<const T&>()`.  
            // In essence, `bind()` enables correct forwarding semantics for function calls.  
            auto [err, ret] = sendStringFn(theStr);

            // Reflected call executes successfully.
            EXPECT_TRUE(err == rtl::error::None);
            EXPECT_FALSE(ret.isEmpty());

            // We know the return type is std::string.
            EXPECT_TRUE(ret.canViewAs<std::string>());

            // Extract the std::string view from `ret`.
            std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
            ASSERT_TRUE(strView);

            const std::string& retStr = strView->get();
            // Confirms that the expected function was invoked.
            EXPECT_EQ(retStr, expectReturnStr);
        }
    }


    TEST(MyReflectionTests, overload_resolution_semantics__arg_const_char_ptr)
    {
        // Retrieve the function with its correct namespace.
        std::optional<rtl::Function> optSendAsString = MyReflection().getFunction("ext", "sendAsString");
        // Found successfully.
        ASSERT_TRUE(optSendAsString);

        auto theStr = std::string("const_char_ptr.");
        auto expectReturnStr = ("sent_string_literal_" + theStr);

        auto sendAsStringFn = optSendAsString->argsT<const char*>().returnT<>();
        ASSERT_TRUE(sendAsStringFn);
        EXPECT_EQ(sendAsStringFn.get_init_error(), rtl::error::None);

        // Nothing to bind here, since this is a non-member (C-style) function and it does not  
        // require arguments to be perfectly forwarded.  
        // The argument passed is `const char*`, and the corresponding overload has been registered.  
        // The reflective call succeeds. If a mismatched argument is passed,  
        // `error::SignatureMismatch` will be returned.
        auto [err, ret] = sendAsStringFn(theStr.c_str());

        // Reflected call executes successfully.
        EXPECT_TRUE(err == rtl::error::None);
        EXPECT_FALSE(ret.isEmpty());

        // We know the return type is std::string.
        EXPECT_TRUE(ret.canViewAs<std::string>());

        // Extract the std::string view from `ret`.
        std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
        ASSERT_TRUE(strView);

        const std::string& retStr = strView->get();
        // Confirms that the expected function was invoked.
        EXPECT_EQ(retStr, expectReturnStr);
    }


    TEST(MyReflectionTests, overload_resolution_semantics__arg_lvalue)
    {
        // Retrieve the function from its namespace.
        std::optional<rtl::Function> optSendAsString = MyReflection().getFunction("ext", "sendAsString");
        ASSERT_TRUE(optSendAsString); // Function found successfully.

        auto nameStr = std::string("person_Eric");
        auto person = Person(nameStr);
        auto expectReturnStr = ("sent_string_lvalue_" + nameStr);

        auto sendAsStringFn = optSendAsString->argsT<Person>().returnT<>();
        ASSERT_TRUE(sendAsStringFn);
        EXPECT_EQ(sendAsStringFn.get_init_error(), rtl::error::None);

        // Nothing to bind here: the call is with a regular lvalue.
        // This resolves to the overload `sendAsString(Person)`.
        // The overload was registered, so the reflective call will succeed.
        // If the argument type mismatches, `error::SignatureMismatch` will be returned.
        auto [err, ret] = sendAsStringFn(person);

        // Validate reflective call succeeded.
        EXPECT_TRUE(err == rtl::error::None);
        EXPECT_FALSE(ret.isEmpty());

        // Verify return type and extract result.
        EXPECT_TRUE(ret.canViewAs<std::string>());
        std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
        ASSERT_TRUE(strView);

        const std::string& retStr = strView->get();
        // Confirms the correct overload was invoked.
        EXPECT_EQ(retStr, expectReturnStr);
    }


    TEST(MyReflectionTests, overload_resolution_with_perfect_forwarding_semantics__arg_rvalue)
    {
        // Retrieve the function from its namespace.
        std::optional<rtl::Function> optSendAsString = MyReflection().getFunction("ext", "sendAsString");
        ASSERT_TRUE(optSendAsString); // Function found successfully.

        auto nameStr = std::string("person_Logan");
        
        auto sendAsStringFn = optSendAsString->argsT<Person>().returnT<>();
        ASSERT_TRUE(sendAsStringFn);
        EXPECT_EQ(sendAsStringFn.get_init_error(), rtl::error::None);
        {
            // Although the argument is an rvalue (Person&&),
            // overload resolution prefers the by-value overload (Person)
            // over the rvalue-reference overload when both are viable.
            // As a result, the call resolves to the by-value function.
            auto [err, ret] = sendAsStringFn(Person(nameStr));
            EXPECT_TRUE(err == rtl::error::None);
            EXPECT_FALSE(ret.isEmpty());

            // Verify return type and extract result.
            EXPECT_TRUE(ret.canViewAs<std::string>());
            std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
            ASSERT_TRUE(strView);

            const std::string& retStr = strView->get();
            auto expectReturnStr = ("sent_string_lvalue_" + nameStr);
            // Confirms the correct overload was invoked.
            EXPECT_EQ(retStr, expectReturnStr);
        } {
            // Now invoke the rvalue-ref overload: `sendAsString(Person&&)`.
            // To ensure this overload is selected, we must explicitly bind
            // with `Person&&`. This is achieved through perfect forwarding,
            // since overload resolution cannot deduce rvalue-ref automatically.
            //
            // The overload was registered, so the reflective call will succeed.
            // If the argument type mismatches, `error::SignatureMismatch` will be returned.
            auto [err, ret] = sendAsStringFn.bind<Person&&>()(Person(nameStr));

            // Validate reflective call succeeded.
            EXPECT_TRUE(err == rtl::error::None);
            EXPECT_FALSE(ret.isEmpty());

            // Verify return type and extract result.
            EXPECT_TRUE(ret.canViewAs<std::string>());
            std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
            ASSERT_TRUE(strView);

            const std::string& retStr = strView->get();
            auto expectReturnStr = ("sent_string_rvalue_" + nameStr);
            // Confirms the correct overload was invoked.
            EXPECT_EQ(retStr, expectReturnStr);
        }
    }


    TEST(MyReflectionTests, invoking_static_member_function_semantics)
    {
        // Retrieve the reflected class metadata.
        std::optional<rtl::Record> classPerson = MyReflection().getRecord("Person");
        ASSERT_TRUE(classPerson);

        // Retrieve the static method from the class.
        std::optional<rtl::Method> optGetDefaults = classPerson->getMethod("getDefaults");
        ASSERT_TRUE(optGetDefaults);
        {
            auto getDefaultsFn = optGetDefaults->argsT<>().returnT<>();
            ASSERT_TRUE(getDefaultsFn);
            EXPECT_EQ(getDefaultsFn.get_init_error(), rtl::error::None);

            // Call the static member function directly.
            // Semantics are the same as a free function:
            // nothing to bind unless perfect-forwarding arguments are involved.
            // Since it's static, no instance of the class is required.
            auto [err, ret] = getDefaultsFn();

            // Validate reflective call succeeded.
            EXPECT_TRUE(err == rtl::error::None);
            EXPECT_FALSE(ret.isEmpty());

            // Verify return type and extract result.
            EXPECT_TRUE(ret.canViewAs<std::string>());
            std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
            ASSERT_TRUE(strView);

            const std::string& retStr = strView->get();
            auto expectReturnStr = std::string("Person_defaults_returned");
            // Confirms the expected static function was invoked.
            EXPECT_EQ(retStr, expectReturnStr);
        }
    }


    TEST(MyReflectionTests, overload_resolution_semantics__constructor)
    {
        std::optional<rtl::Record> classPerson = MyReflection().getRecord("Person");
        ASSERT_TRUE(classPerson);

        const char* name = "Charlie";
        //  Invokes the overloaded constructor that takes 'const std::string&'.
        //  It will not match the overload with 'std::string&', because arguments
        //  are forwarded as universal references (&&), which bind only to 
        //  'const std::string&'. This resolution is handled by the compiler,
        //  not by RTL.
        auto [err, robj] = classPerson->ctor<std::string>()(rtl::alloc::Stack, name);

        EXPECT_TRUE(err == rtl::error::None);
        ASSERT_TRUE(!robj.isEmpty());
        ASSERT_TRUE(robj.canViewAs<Person>());

        auto view = robj.view<Person>();
        EXPECT_TRUE(view);

        const Person& person = view->get();
        EXPECT_EQ(name, person.name);
    }


    TEST(MyReflectionTests, overload_resolution_semantics__method)
    {
        // Tests runtime overload resolution between `std::string` (by value)
        // and `std::string&` overloads of Person::setProfile.
        std::optional<rtl::Record> classPerson = MyReflection().getRecord("Person");
        ASSERT_TRUE(classPerson);

        //  Create a Person instance the regular way.
        Person orgTim("Tim");

        //  Reflect into RObject. Internally this creates a copy of 'orgTim' on the stack.
        rtl::RObject robjTim = rtl::reflect(orgTim);

        std::optional<rtl::Method> oSetProfile = classPerson->getMethod("setProfile");
        ASSERT_TRUE(oSetProfile);

        rtl::method<rtl::RObject, rtl::Return(std::string)> setProfile = oSetProfile->targetT()
                                                                                    .argsT<std::string>()
                                                                                    .returnT();
        EXPECT_TRUE(setProfile);
        //  NOTE for documentation:
        //  Calling with a constant-size array (like `"profStr"`) will not compile, 
        //  because array-to-pointer decay is not supported here.
        //  Instead, use a `const char*` or `std::string`.
        //  auto [err, ret] = setProfile(robjTim)("profStr");

        {
            auto [err, ret] = setProfile(robjTim)("Tim's prof");
            EXPECT_TRUE(err == rtl::error::None);
            EXPECT_FALSE(ret.isEmpty());

            // We know the return type is std::string.
            EXPECT_TRUE(ret.canViewAs<std::string>());

            // Extract the std::string view from `ret`.
            std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
            ASSERT_TRUE(strView);

            const std::string& retStr = strView->get();
            // Confirms that the overload taking `std::string` by value was invoked.
            EXPECT_EQ(retStr, "called_by_val");
        } {
            std::string profStr = "Tim's profile.";

            // TODO: by value and by-ref overload should not be allowed.
            auto [err, ret] = setProfile.bind<std::string&>(robjTim)("Tim's profile.");

            EXPECT_TRUE(err == rtl::error::None);
            EXPECT_FALSE(ret.isEmpty());

            // Again, return type is std::string.
            EXPECT_TRUE(ret.canViewAs<std::string>());

            // Extract the std::string view from `ret`.
            std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
            ASSERT_TRUE(strView);

            const std::string& retStr = strView->get();
            // Even though compiler doesn't allows this but RTL can call both the methods successfully,
            // TODO: by value and by-ref overload should not be allowed.
            EXPECT_EQ(retStr, "called_by_ref");
        }
    }


    TEST(MyReflectionTests, perfect_forwarding_seamantics__rvalue_ref)
    {
        std::optional<rtl::Record> classPerson = MyReflection().getRecord("Person");
        ASSERT_TRUE(classPerson);

        // Create a Person instance the regular way.
        Person orgTim("Tim");

        // Reflect into RObject. Internally this creates a copy of 'orgTim' on the stack.
        rtl::RObject robjTim = rtl::reflect(orgTim);

        std::optional<rtl::Method> oSetTitle = classPerson->getMethod("setTitle");
        ASSERT_TRUE(oSetTitle);

        rtl::method<rtl::RObject, rtl::Return(std::string)> setTitle = oSetTitle->targetT()
                                                                                .argsT<std::string>()
                                                                                .returnT();
        EXPECT_TRUE(setTitle);
        {
            //  Attempt to call 'setTitle' with an rvalue string.
            //  This fails because reflection will first attempt to resolve the call
            //  against a by-value parameter (`std::string`) instead of the actual
            //  registered signature (`std::string&&`).
            auto [err, ret] = setTitle(robjTim)(std::string("Mr."));
            EXPECT_TRUE(err == rtl::error::ExplicitRefBindingRequired);
            EXPECT_TRUE(ret.isEmpty());
        } {
            //  To invoke the method successfully, we must perfectly forward `std::string` as an rvalue-ref.  
            //  This requires explicitly specifying `std::string&&` in the template parameter pack of `bind`.  
            //  Note: passing a string literal works fine here, since it is implicitly convertible to `std::string`;  
            //  wrapping with `std::string("Mr.")` is unnecessary.  
            auto [err, ret] = setTitle.bind<std::string&&>(robjTim)("Mr.");
            EXPECT_TRUE(err == rtl::error::None);
            ASSERT_FALSE(ret.isEmpty());

            // We know the return type is std::string.
            EXPECT_TRUE(ret.canViewAs<std::string>());

            // Extract the std::string view from `ret`.
            std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
            ASSERT_TRUE(strView);

            const std::string& retStr = strView->get();
            // Confirms that the `setTitle(std::string&&)` overload was correctly invoked.
            EXPECT_EQ(retStr, "called_by_ref_rvalue");
        }
    }

    
    TEST(MyReflectionTests, perfect_forwarding_semantics__overload_resolution)
    {
        std::optional<rtl::Record> classPerson = MyReflection().getRecord("Person");
        ASSERT_TRUE(classPerson);

        // Create a Person instance the regular way.
        Person orgTim("Tim");

        // Reflect into RObject. Internally this creates a copy of 'orgTim' on the stack.
        rtl::RObject robjTim = rtl::reflect(orgTim);

        std::optional<rtl::Method> oSetOccupation = classPerson->getMethod("setOccupation");
        ASSERT_TRUE(oSetOccupation);

        rtl::method<rtl::RObject, rtl::Return(std::string)> setOccupation = oSetOccupation->targetT()
                                                                                          .argsT<std::string>()
                                                                                          .returnT();
        EXPECT_TRUE(setOccupation);
        {
        //  Attempt to call 'setOccupation' with an rvalue string.
        //  Expectation: should match the rvalue-ref overload (`std::string&&`).
        //  Actual: fails because reflection first attempts to match a by-value
        //  parameter (`std::string`) instead of the registered signature.
            auto [err, ret] = setOccupation(robjTim)(std::string("Teacher"));
            EXPECT_TRUE(err == rtl::error::ExplicitRefBindingRequired);
            EXPECT_TRUE(ret.isEmpty());
        } {
        //  Attempt to call 'setOccupation' with a const-lvalue string.
        //  Expectation: should match the const-lvalue-ref overload (`const std::string&`).
        //  Actual: fails for the same reason reflection attempts by-value resolution first.
            const std::string occupationStr = "Teacher";
            auto [err, ret] = setOccupation(robjTim)(occupationStr);
            EXPECT_TRUE(err == rtl::error::ExplicitRefBindingRequired);
            EXPECT_TRUE(ret.isEmpty());
        } {
        //  Correctly invoke the rvalue-ref overload by explicitly binding
        //  `std::string&&` in the template parameter pack and perfectly forwarding.
            auto [err, ret] = setOccupation.bind<std::string&&>(robjTim)("Teacher");
            EXPECT_TRUE(err == rtl::error::None);
            ASSERT_FALSE(ret.isEmpty());

            // The return type is known to be std::string.
            EXPECT_TRUE(ret.canViewAs<std::string>());

            std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
            ASSERT_TRUE(strView);

            const std::string& retStr = strView->get();
            // Confirms that the `setOccupation(std::string&&)` overload was correctly invoked.
            EXPECT_EQ(retStr, "called_by_rvalue_ref");
        } {
        //  Correctly invoke the const-lvalue-ref overload by explicitly binding
        //  `const std::string&` in the template parameter pack and perfectly forwarding.
            auto [err, ret] = setOccupation.bind<const std::string&>(robjTim)("Teacher");
            EXPECT_TRUE(err == rtl::error::None);
            ASSERT_FALSE(ret.isEmpty());

            // The return type is known to be std::string.
            EXPECT_TRUE(ret.canViewAs<std::string>());

            std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
            ASSERT_TRUE(strView);

            const std::string& retStr = strView->get();
            // Confirms that the `setOccupation(const std::string&)` overload was correctly invoked.
            EXPECT_EQ(retStr, "called_by_ref_lvalue");
        }
    }


    TEST(MyReflectionTests, const_method_semantics__on_true_const_target)
    {
        // Case 1: Reflecting a true-const Person.
        const Person constSam = Person("Const-Sam");
        // Reflect 'const Person' into RObject.
        // RTL never performs an implicit const_cast on const objects.
        // Since 'constSam' is genuinely const, RTL preserves that constness.
        // This applies equally to any object returned by reflective calls.
        rtl::RObject robj = rtl::reflect(constSam);
        
        std::optional<rtl::Record> classPerson = MyReflection().getRecord("Person");
        ASSERT_TRUE(classPerson);

        std::optional<rtl::Method> oGetProfile = classPerson->getMethod("getProfile");
        ASSERT_TRUE(oGetProfile);

        rtl::method<rtl::RObject, rtl::Return()> getProfile = oGetProfile->targetT().argsT().returnT();
        EXPECT_TRUE(getProfile);
        {
            // For 'getProfile' only a const overload is registered.
            // Since 'robj' reflects a const object, only const methods can be called on it.
            // making 'robj' as const (using std::cref) ensures to call the const-method on it.
            auto [err, ret] = getProfile(std::cref(robj))();
            EXPECT_TRUE(err == rtl::error::None);
            EXPECT_FALSE(ret.isEmpty());

            // Validate return type and value.
            EXPECT_TRUE(ret.canViewAs<std::string>());
            std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
            ASSERT_TRUE(strView);

            const std::string& retStr = strView->get();
            std::string expectReturnStr = "only_const_method_version_exists";
            EXPECT_EQ(retStr, expectReturnStr);
        } {
            // Attempt to bind a truly-const object to a non-const method.
            // Since the object is genuinely const, the call fails because no 
            // non-const overload is registered for the same.
            auto [err, ret] = getProfile(robj)();
            // Expected: NonConstOverloadMissing.
            EXPECT_TRUE(err == rtl::error::NonConstOverloadMissing);
            EXPECT_TRUE(ret.isEmpty());
        }
    }


    TEST(MyReflectionTests, non_const_method_semantics__on_true_const_target)
    {
        // Case 1: Reflecting a true-const Person.
        const Person constSam = Person("Const-Sam");
        // Reflect 'const Person' into RObject.
        // RTL never performs an implicit const_cast on const objects.
        // Since 'constSam' is genuinely const, RTL preserves that constness.
        // This applies equally to any object returned by reflective calls.
        rtl::RObject robj = rtl::reflect(constSam);

        std::optional<rtl::Record> classPerson = MyReflection().getRecord("Person");
        ASSERT_TRUE(classPerson);

        // only a non-const overload exists(and registered) for 'getName'.
        std::optional<rtl::Method> oGetName = classPerson->getMethod("getName");
        ASSERT_TRUE(oGetName);

        rtl::method<rtl::RObject, rtl::Return()> getName = oGetName->targetT().argsT().returnT();
        EXPECT_TRUE(getName);
        {
            // using std::cref() here, we are enforcing to call the const-method
            // overload of 'getName' (which doesn't exists).
            auto [err, ret] = getName(std::cref(robj))();
            // 'robj' reflects a true-const Person, but 'getName' is non-const.
            // RTL searches for a const overload, which is not present.
            // Expected: ConstOverloadMissing.
            EXPECT_TRUE(err == rtl::error::ConstOverloadMissing);
            EXPECT_TRUE(ret.isEmpty());
        } {
            // Explicitly attempt to bind the true-const object to a non-const method.
            // Since the object is truly const, const_cast is unsafe.
            auto [err, ret] = getName(robj)();
            // Expected: InvalidCallOnConstTarget.
            EXPECT_TRUE(err == rtl::error::InvalidCallOnConstTarget);
            EXPECT_TRUE(ret.isEmpty());
        }
    }


    TEST(MyReflectionTests, const_based_overload_resolution_semantics__on_const_target)
    {
        // Case 1: Reflecting a true-const Person.
        const Person constSam = Person("Const-Sam");
        // Reflect 'const Person' into RObject.
        // RTL never performs an implicit const_cast on const objects.
        // Since 'constSam' is genuinely const, RTL preserves that constness.
        // This applies equally to any object returned by reflective calls.
        rtl::RObject robj = rtl::reflect(constSam);

        std::optional<rtl::Record> classPerson = MyReflection().getRecord("Person");
        ASSERT_TRUE(classPerson);

        std::optional<rtl::Method> oUpdateAddress = classPerson->getMethod("updateAddress");
        ASSERT_TRUE(oUpdateAddress);

        rtl::method<rtl::RObject, rtl::Return()> updateAddress = oUpdateAddress->targetT().argsT().returnT();
        EXPECT_TRUE(updateAddress);
        {
            std::string expectReturnStr = "called_const_overload";
            // Both const and non-const overloads are registered.
            // Since 'robj' reflecting a true-const, RTL invokes the const overload without fail.
            auto [err, ret] = updateAddress(std::cref(robj))();
            EXPECT_TRUE(err == rtl::error::None);
            EXPECT_FALSE(ret.isEmpty());

            EXPECT_TRUE(ret.canViewAs<std::string>());
            std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
            ASSERT_TRUE(strView);

            const std::string& retStr = strView->get();
            EXPECT_EQ(retStr, expectReturnStr);
        } {
            // Explicitly attempt to call the non-const overload.
            // Unsafe here, since the object is truly const.
            auto [err, ret] = updateAddress(robj)();
            // Expected: IllegalConstCast.
            EXPECT_TRUE(err == rtl::error::InvalidCallOnConstTarget);
            EXPECT_TRUE(ret.isEmpty());
        }
    }


    TEST(MyReflectionTests, const_based_overload_resolution_semantics__on_non_const_target)
    {
        // Case 2: Reflecting a mutable Person.
        rtl::RObject robj = rtl::reflect(Person("Mutable-Sam"));

        std::optional<rtl::Record> classPerson = MyReflection().getRecord("Person");
        ASSERT_TRUE(classPerson);

        std::optional<rtl::Method> oUpdateAddress = classPerson->getMethod("updateAddress");
        ASSERT_TRUE(oUpdateAddress);

        rtl::method<rtl::RObject, rtl::Return()> updateAddress = oUpdateAddress->targetT().argsT().returnT();
        EXPECT_TRUE(updateAddress);
        {
            std::string expectReturnStr = "called_const_overload";
            // Both const and non-const overloads are registered.
            // Since 'robj' is mutable, but we can explicitly call the const overload
            // by making sending the 'robj' as const (using std::cref()).
            auto [err, ret] = updateAddress(std::cref(robj))();
            EXPECT_TRUE(err == rtl::error::None);
            EXPECT_FALSE(ret.isEmpty());

            EXPECT_TRUE(ret.canViewAs<std::string>());
            std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
            ASSERT_TRUE(strView);

            const std::string& retStr = strView->get();
            EXPECT_EQ(retStr, expectReturnStr);
        } {
            std::string expectReturnStr = "called_non_const_overload";
            // Explicit request for the non-const overload by sending the 'robj' as non-const.
            auto [err, ret] = updateAddress(robj)();
            EXPECT_TRUE(err == rtl::error::None);
            EXPECT_FALSE(ret.isEmpty());

            EXPECT_TRUE(ret.canViewAs<std::string>());
            std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
            ASSERT_TRUE(strView);

            const std::string& retStr = strView->get();
            EXPECT_EQ(retStr, expectReturnStr);
        }
    }
}