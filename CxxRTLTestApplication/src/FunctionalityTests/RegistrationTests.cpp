
#include <gtest/gtest.h>

#include "RTLibInterface.h"
#include "RegistrationTestProp.h"

using namespace rtl::access;

namespace registration_test
{
    extern const rtl::access::CxxMirror& cxx_mirror();

    TEST(RegistrationTest, C_style_function)
    {
        {
            // Attempt to retrieve the C-style function without specifying a namespace.
            auto sendAsStr = cxx_mirror().getFunction("sendAsString");
            // Not found, since it was registered under the 'ext' namespace.
            EXPECT_FALSE(sendAsStr);
        } {
            // Retrieve the function with its correct namespace.
            auto sendAsStr = cxx_mirror().getFunction("ext", "sendAsString");
            // Found successfully.
            ASSERT_TRUE(sendAsStr);

            auto [err, ret] = sendAsStr->bind().call(Person("Alex"));
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
            EXPECT_EQ(retStr, "sendAsString_called.");
        }
    }


    TEST(RegistrationTest, constructor_overload_resolution)
    {
        std::optional<rtl::access::Record> classPerson = cxx_mirror().getRecord("Person");
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


    TEST(RegistrationTest, overload_resolution__setProfile)
    {
        // Tests runtime overload resolution between `std::string` (by value)
        // and `std::string&` overloads of Person::setProfile.
        std::optional<rtl::access::Record> classPerson = cxx_mirror().getRecord("Person");
        ASSERT_TRUE(classPerson);

        //  Create a Person instance the regular way.
        Person orgTim("Tim");

        //  Reflect into RObject. Internally this creates a copy of 'orgTim' on the stack.
        rtl::access::RObject robjTim = rtl::reflect(orgTim);

        std::optional<rtl::access::Method> setProfile = classPerson->getMethod("setProfile");
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


    TEST(RegistrationTest, perfect_forwarding_rvalue_ref)
    {
        std::optional<rtl::access::Record> classPerson = cxx_mirror().getRecord("Person");
        ASSERT_TRUE(classPerson);

        // Create a Person instance the regular way.
        Person orgTim("Tim");

        // Reflect into RObject. Internally this creates a copy of 'orgTim' on the stack.
        rtl::access::RObject robjTim = rtl::reflect(orgTim);

        std::optional<rtl::access::Method> setTitle = classPerson->getMethod("setTitle");
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

    
    TEST(RegistrationTest, perfect_forwarding_overload_resolution)
    {
        std::optional<rtl::access::Record> classPerson = cxx_mirror().getRecord("Person");
        ASSERT_TRUE(classPerson);

        // Create a Person instance the regular way.
        Person orgTim("Tim");

        // Reflect into RObject. Internally this creates a copy of 'orgTim' on the stack.
        rtl::access::RObject robjTim = rtl::reflect(orgTim);

        std::optional<rtl::access::Method> setOccupation = classPerson->getMethod("setOccupation");
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


    TEST(RegistrationTest, non_const_method_call_resolution__on_true_const_target)
    {
        std::optional<rtl::access::Record> classPerson = cxx_mirror().getRecord("Person");
        ASSERT_TRUE(classPerson);

        std::optional<rtl::access::Method> getName = classPerson->getMethod("getName");
        ASSERT_TRUE(getName);
        {
            // Case 1: Reflecting a true-const Person.
            const Person constPerson = Person("Const Sam");

            // Reflect 'const Person' into RObject.
            rtl::access::RObject robj = rtl::reflect(constPerson);

            // RTL never performs an implicit const_cast on externally provided true-const objects.
            // Since 'constPerson' is genuinely const, RTL preserves that constness.
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


    TEST(RegistrationTest, non_const_method_call_resolution__on_logical_const_target)
    {
        std::optional<rtl::access::Record> classPerson = cxx_mirror().getRecord("Person");
        ASSERT_TRUE(classPerson);

        std::optional<rtl::access::Method> getName = classPerson->getMethod("getName");
        ASSERT_TRUE(getName);
        // Case 2: Reflecting a mutable Person.
        Person mutablePerson = Person("Mutable Sam");

        // Reflect 'Person' into RObject (copy created on stack).
        rtl::access::RObject robj = rtl::reflect(mutablePerson);

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
            EXPECT_EQ(retStr, "Mutable Sam");
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
            EXPECT_EQ(retStr, "Mutable Sam");
        }
    }
}