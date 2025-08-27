
#include <gtest/gtest.h>

#include "RTLibInterface.h"
#include "MyReflectingType.h"

using namespace rtl;
using namespace my_type;

namespace my_type { extern const rtl::CxxMirror& MyReflection(); }

namespace
{
    TEST(MyReflectionTests, invoking_semantics__C_style_function_with_no_overload)
    {
        {
            // Attempt to retrieve the C-style function without specifying a namespace.
            auto sendString = MyReflection().getFunction("sendString");
            // Not found, since it was registered under the 'ext' namespace.
            EXPECT_FALSE(sendString);
        } {
            // Retrieve the function with its correct namespace.
            auto sendString = MyReflection().getFunction("ext", "sendString");
            // Found successfully.
            ASSERT_TRUE(sendString);

            auto theStr = std::string("Initiating reflection tests.");
            auto expectReturnStr = ("sent_string_" + theStr);

            // Nothing to bind here, since this is a non-member (C-style) function.  
            // However, if the function takes reference parameters that require perfect forwarding,  
            // the binding can be specified explicitly using `bind<T&>()`, `bind<T&&>()`, or `bind<const T&>()`.  
            // In essence, `bind()` enables correct forwarding semantics for function calls.  
            auto [err, ret] = sendString->bind().call(theStr);

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
        auto sendAsString = MyReflection().getFunction("ext", "sendAsString");
        // Found successfully.
        ASSERT_TRUE(sendAsString);

        auto theStr = std::string("const_char_ptr.");
        auto expectReturnStr = ("sent_string_literal_" + theStr);

        // Nothing to bind here, since this is a non-member (C-style) function and it does not  
        // require arguments to be perfectly forwarded.  
        // The argument passed is `const char*`, and the corresponding overload has been registered.  
        // The reflective call succeeds. If a mismatched argument is passed,  
        // `error::SignatureMismatch` will be returned.
        auto [err, ret] = sendAsString->bind().call(theStr.c_str());

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
        auto sendAsString = MyReflection().getFunction("ext", "sendAsString");
        ASSERT_TRUE(sendAsString); // Function found successfully.

        auto nameStr = std::string("person_Eric");
        auto person = Person(nameStr);
        auto expectReturnStr = ("sent_string_lvalue_" + nameStr);

        // Nothing to bind here: the call is with a regular lvalue.
        // This resolves to the overload `sendAsString(Person)`.
        // The overload was registered, so the reflective call will succeed.
        // If the argument type mismatches, `error::SignatureMismatch` will be returned.
        auto [err, ret] = sendAsString->bind().call(person);

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
        auto sendAsString = MyReflection().getFunction("ext", "sendAsString");
        ASSERT_TRUE(sendAsString); // Function found successfully.

        auto nameStr = std::string("person_Logan");
        auto expectReturnStr = ("sent_string_rvalue_" + nameStr);

        // Now invoke the rvalue-ref overload: `sendAsString(Person&&)`.
        // To ensure this overload is selected, we must explicitly bind
        // with `Person&&`. This is achieved through perfect forwarding,
        // since overload resolution cannot deduce rvalue-ref automatically.
        //
        // The overload was registered, so the reflective call will succeed.
        // If the argument type mismatches, `error::SignatureMismatch` will be returned.
        auto [err, ret] = sendAsString->bind<Person&&>().call(Person(nameStr));

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


    TEST(MyReflectionTests, invoking_static_member_function_semantics)
    {
        // Retrieve the reflected class metadata.
        std::optional<rtl::Record> classPerson = MyReflection().getRecord("Person");
        ASSERT_TRUE(classPerson);

        // Retrieve the static method from the class.
        std::optional<rtl::Method> getDefaults = classPerson->getMethod("getDefaults");
        ASSERT_TRUE(getDefaults);

        auto expectReturnStr = std::string("Person_defaults_returned");

        {
            // Call the static member function directly.
            // Semantics are the same as a free function:
            // nothing to bind unless perfect-forwarding arguments are involved.
            // Since it's static, no instance of the class is required.
            auto [err, ret] = getDefaults->bind().call();

            // Validate reflective call succeeded.
            EXPECT_TRUE(err == rtl::error::None);
            EXPECT_FALSE(ret.isEmpty());

            // Verify return type and extract result.
            EXPECT_TRUE(ret.canViewAs<std::string>());
            std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
            ASSERT_TRUE(strView);

            const std::string& retStr = strView->get();
            // Confirms the expected static function was invoked.
            EXPECT_EQ(retStr, expectReturnStr);
        } {
            // Now create a `Person` object and reflect it into RTL.
            rtl::RObject robj = rtl::reflect(Person(""));

            // Even if we bind a target object before calling the static function,
            // it has no effect — the call remains valid and succeeds.
            // This matches C++ native semantics: binding an instance is irrelevant
            // for static member functions.
            auto [err, ret] = getDefaults->bind(robj).call();

            // Validate reflective call succeeded.
            EXPECT_TRUE(err == rtl::error::None);
            EXPECT_FALSE(ret.isEmpty());

            // Verify return type and extract result.
            EXPECT_TRUE(ret.canViewAs<std::string>());
            std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
            ASSERT_TRUE(strView);

            const std::string& retStr = strView->get();
            // Confirms the expected static function was invoked.
            EXPECT_EQ(retStr, expectReturnStr);
        }
    }


    TEST(MyReflectionTests, overload_resolution_semantics__constructor)
    {
        std::optional<rtl::Record> classPerson = MyReflection().getRecord("Person");
        ASSERT_TRUE(classPerson);

        std::string name = "Charlie";
        {
            //  Invokes the overloaded constructor that takes 'const std::string&'.
            //  It will not match the overload with 'std::string&', because arguments
            //  are forwarded as universal references (&&), which bind only to 
            //  'const std::string&'. This resolution is handled by the compiler,
            //  not by RTL.
            auto [err, robj] = classPerson->create<rtl::alloc::Stack>(name);

            EXPECT_TRUE(err == rtl::error::None);
            ASSERT_TRUE(!robj.isEmpty());
            ASSERT_TRUE(robj.canViewAs<Person>());

            auto view = robj.view<Person>();
            EXPECT_TRUE(view);

            const Person& person = view->get();
            EXPECT_EQ(name, person.name);
        }
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

        std::optional<rtl::Method> setProfile = classPerson->getMethod("setProfile");
        ASSERT_TRUE(setProfile);

        //  NOTE for documentation:
        //  Calling with a constant-size array (like `"profStr"`) will not compile, 
        //  because array-to-pointer decay is not supported here.
        //  Instead, use a `const char*` or `std::string`.
        //  auto [err, ret] = setProfile->bind(robjTim).call("profStr");
        
        {
            auto [err, ret] = setProfile->bind(robjTim).call(std::string("Tim's prof"));
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
            auto [err, ret] = setProfile->bind(robjTim).call<const std::string&>(profStr);
            EXPECT_TRUE(err == rtl::error::None);
            EXPECT_FALSE(ret.isEmpty());

            // Again, return type is std::string.
            EXPECT_TRUE(ret.canViewAs<std::string>());

            // Extract the std::string view from `ret`.
            std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
            ASSERT_TRUE(strView);

            const std::string& retStr = strView->get();
            // Even though we explicitly bound `std::string&`, 
            // runtime overload resolution still picked the by-value version.
            EXPECT_EQ(retStr, "called_by_val");
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

        std::optional<rtl::Method> setTitle = classPerson->getMethod("setTitle");
        ASSERT_TRUE(setTitle);

        {
            //  Attempt to call 'setTitle' with an rvalue string.
            //  This fails because reflection will first attempt to resolve the call
            //  against a by-value parameter (`std::string`) instead of the actual
            //  registered signature (`std::string&&`).
            auto [err, ret] = setTitle->bind(robjTim).call(std::string("Mr."));
            EXPECT_TRUE(err == rtl::error::SignatureMismatch);
            EXPECT_TRUE(ret.isEmpty());
        } {
            //  To invoke the method successfully, we must perfectly forward `std::string` as an rvalue-ref.  
            //  This requires explicitly specifying `std::string&&` in the template parameter pack of `bind`.  
            //  Note: passing a string literal works fine here, since it is implicitly convertible to `std::string`;  
            //  wrapping with `std::string("Mr.")` is unnecessary.  
            auto [err, ret] = setTitle->bind<std::string&&>(robjTim).call("Mr.");
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

        std::optional<rtl::Method> setOccupation = classPerson->getMethod("setOccupation");
        ASSERT_TRUE(setOccupation);

        {
        //  Attempt to call 'setOccupation' with an rvalue string.
        //  Expectation: should match the rvalue-ref overload (`std::string&&`).
        //  Actual: fails because reflection first attempts to match a by-value
        //  parameter (`std::string`) instead of the registered signature.
            auto [err, ret] = setOccupation->bind(robjTim).call(std::string("Teacher"));
            EXPECT_TRUE(err == rtl::error::SignatureMismatch);
            EXPECT_TRUE(ret.isEmpty());
        } {
        //  Attempt to call 'setOccupation' with a const-lvalue string.
        //  Expectation: should match the const-lvalue-ref overload (`const std::string&`).
        //  Actual: fails for the same reason�reflection attempts by-value resolution first.
            const std::string occupationStr = "Teacher";
            auto [err, ret] = setOccupation->bind(robjTim).call(std::string(occupationStr));
            EXPECT_TRUE(err == rtl::error::SignatureMismatch);
            EXPECT_TRUE(ret.isEmpty());
        } {
        //  Correctly invoke the rvalue-ref overload by explicitly binding
        //  `std::string&&` in the template parameter pack and perfectly forwarding.
            auto [err, ret] = setOccupation->bind<std::string&&>(robjTim).call("Teacher");
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
            auto [err, ret] = setOccupation->bind<const std::string&>(robjTim).call("Teacher");
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


    TEST(MyReflectionTests, non_const_method_semantics__on_true_const_target)
    {
        std::optional<rtl::Record> classPerson = MyReflection().getRecord("Person");
        ASSERT_TRUE(classPerson);

        std::optional<rtl::Method> getName = classPerson->getMethod("getName");
        ASSERT_TRUE(getName);
        {
            // Case 1: Reflecting a true-const Person.
            const Person constSam = Person("Const-Sam");

            // Reflect 'const Person' into RObject.
            rtl::RObject robj = rtl::reflect(constSam);

            // RTL never performs an implicit const_cast on externally provided true-const objects.
            // Since 'constSam' is genuinely const, RTL preserves that constness.
            // This applies equally to any object returned by reflective calls.
            EXPECT_FALSE(robj.isConstCastSafe());
            {
                auto [err, ret] = getName->bind(robj).call();
                // 'robj' reflects a true-const Person, but 'getName' is non-const.
                // Non-const methods cannot be invoked on true-const objects.
                // Expected: ConstCallViolation.
                EXPECT_TRUE(err == rtl::error::ConstCallViolation);
                EXPECT_TRUE(ret.isEmpty());
            } {
                // Attempt to explicitly bind the true-const object to a non-const method.
                // This requests RTL to const_cast the reflected object.
                // Since the underlying object is true-const, the cast is unsafe.
                auto [err, ret] = getName->bind(rtl::constCast(robj)).call();
                // Expected: IllegalConstCast.
                EXPECT_TRUE(err == rtl::error::IllegalConstCast);
                EXPECT_TRUE(ret.isEmpty());
            }
        }
    }


    TEST(MyReflectionTests, non_const_method_semantics__on_logical_const_target)
    {
        std::optional<rtl::Record> classPerson = MyReflection().getRecord("Person");
        ASSERT_TRUE(classPerson);

        std::optional<rtl::Method> getName = classPerson->getMethod("getName");
        ASSERT_TRUE(getName);
        // Case 2: Reflecting a mutable Person.
        Person mutableSam = Person("Mutable-Sam");

        // Reflect 'Person' into RObject (copy created on stack).
        rtl::RObject robj = rtl::reflect(mutableSam);

        // RTL treats reflection-created objects as logically immutable by default.
        // For such objects, const_cast is always safe, since RTL controls their lifetime.
        EXPECT_TRUE(robj.isConstCastSafe());
        {
            auto [err, ret] = getName->bind(robj).call();
            // 'robj' is logically-const, but since only a non-const overload is present,
            // RTL safely applies const_cast internally and invokes it.
            EXPECT_TRUE(err == rtl::error::None);
            EXPECT_FALSE(ret.isEmpty());

            // Validate return type and value.
            EXPECT_TRUE(ret.canViewAs<std::string>());
            std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
            ASSERT_TRUE(strView);

            const std::string& retStr = strView->get();
            EXPECT_EQ(retStr, "Mutable-Sam");
        } {
            // Same as above, but this time we explicitly request the non-const overload.
            // `rtl::constCast()` signals intent to call the non-const variant.
            // Safe here, since the underlying object is not truly const.
            auto [err, ret] = getName->bind(rtl::constCast(robj)).call();
            EXPECT_TRUE(err == rtl::error::None);
            EXPECT_FALSE(ret.isEmpty());

            // Validate return type and value.
            EXPECT_TRUE(ret.canViewAs<std::string>());
            std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
            ASSERT_TRUE(strView);

            const std::string& retStr = strView->get();
            EXPECT_EQ(retStr, "Mutable-Sam");
        }
    }


    TEST(MyReflectionTests, const_based_overload_resolution_semantics__on_true_const_target)
    {
        std::optional<rtl::Record> classPerson = MyReflection().getRecord("Person");
        ASSERT_TRUE(classPerson);

        std::optional<rtl::Method> updateAddress = classPerson->getMethod("updateAddress");
        ASSERT_TRUE(updateAddress);
        {
            // Case 1: Reflecting a true-const Person.
            const Person constSam = Person("Const-Sam");

            // Reflect 'const Person' into RObject.
            rtl::RObject robj = rtl::reflect(constSam);

            // RTL never performs an implicit const_cast on externally provided true-const objects.
            // Since 'constSam' is genuinely const, RTL preserves that constness.
            // This applies equally to any object returned by reflective calls.
            EXPECT_FALSE(robj.isConstCastSafe());
            {
                std::string expectReturnStr = "called_const_overload";
                // 'robj' reflects a true-const and for 'updateAddress' both overloads (const/non-const) 
                // are registered. So it will automatically invoke the 'const' overload of 'updateAddress'.
                auto [err, ret] = updateAddress->bind(robj).call();
                EXPECT_TRUE(err == rtl::error::None);
                EXPECT_FALSE(ret.isEmpty());

                // Validate return type and value.
                EXPECT_TRUE(ret.canViewAs<std::string>());
                std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
                ASSERT_TRUE(strView);

                const std::string& retStr = strView->get();
                EXPECT_EQ(retStr, expectReturnStr);
            } {
                // Attempt to explicitly treat the true-const object as non-const,
                // and tries to call the non-const version of 'updateAddress'.
                // This requests RTL to const_cast the reflected object.
                // Since the underlying object is true-const, the cast is unsafe.
                auto [err, ret] = updateAddress->bind(rtl::constCast(robj)).call();
                // Expected: IllegalConstCast.
                EXPECT_TRUE(err == rtl::error::IllegalConstCast);
                EXPECT_TRUE(ret.isEmpty());
            }
        }
    }


    TEST(MyReflectionTests, const_based_overload_resolution_semantics__on_logical_const_target)
    {
        std::optional<rtl::Record> classPerson = MyReflection().getRecord("Person");
        ASSERT_TRUE(classPerson);

        std::optional<rtl::Method> updateAddress = classPerson->getMethod("updateAddress");
        ASSERT_TRUE(updateAddress);
        // Case 2: Reflecting a mutable Person.
        Person mutableSam = Person("Mutable-Sam");

        // Reflect 'Person' into RObject (copy created on stack).
        rtl::RObject robj = rtl::reflect(mutableSam);

        // RTL treats reflection-created objects as logically immutable by default.
        // For such objects, const_cast is always safe, since RTL controls their lifetime.
        EXPECT_TRUE(robj.isConstCastSafe());
        {
            std::string expectReturnStr = "called_const_overload";
            // For 'updateAddress' both overloads (const/non-const) are registered.
            // Since 'robj' is logically-const, it will automatically invoke the 'const' overload.
            auto [err, ret] = updateAddress->bind(robj).call();
            EXPECT_TRUE(err == rtl::error::None);
            EXPECT_FALSE(ret.isEmpty());

            // Validate return type and value.
            EXPECT_TRUE(ret.canViewAs<std::string>());
            std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
            ASSERT_TRUE(strView);

            const std::string& retStr = strView->get();
            EXPECT_EQ(retStr, expectReturnStr);
        } {
            std::string expectReturnStr = "called_non_const_overload";
            // Now this time we explicitly request for the non-const overload.
            // `rtl::constCast()` signals intent to call the non-const variant.
            // const_cast is safe here, since the underlying object is not truly const.
            // This will explicitly make the call to non-const version of 'updateAddress'
            auto [err, ret] = updateAddress->bind(rtl::constCast(robj)).call();
            EXPECT_TRUE(err == rtl::error::None);
            EXPECT_FALSE(ret.isEmpty());

            // Validate return type and value.
            EXPECT_TRUE(ret.canViewAs<std::string>());
            std::optional<rtl::view<std::string>> strView = ret.view<std::string>();
            ASSERT_TRUE(strView);

            const std::string& retStr = strView->get();
            EXPECT_EQ(retStr, expectReturnStr);
        }
    }
}