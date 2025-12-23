
#include <rtl/access.h>
#include <gtest/gtest.h>

#include "TestMirrorProvider.h"
#include "TestUtilsPerson.h"
#include "TestUtilsBook.h"

using namespace std;
using namespace rtl;

using namespace test_utils;
using namespace test_mirror;

namespace rtl_tests
{
    TEST(ConstMethodOverload, explicitly_making_const_call__on_static_method)
    {
        {
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> getDefaults = classPerson->getMethod(person::str_getDefaults);
            ASSERT_TRUE(getDefaults);
            EXPECT_TRUE(getDefaults->hasSignature<>());
            {
                // enabling this results compiler error.
                // auto [err, ret] = getDefaults->bind().call();
                // auto [err, ret] = getDefaults->bind().call();
            }
        }
    }


    TEST(ConstMethodOverload, explicitly_making_const_call__on_wrong_target)
    {
        {
            optional<Record> classBook = cxx::mirror().getRecord(book::class_);
            ASSERT_TRUE(classBook);

            auto [err0, book] = classBook->ctor()(alloc::Stack);
            EXPECT_TRUE(err0 == error::None);
            EXPECT_TRUE(book.isConstCastSafe());
            ASSERT_FALSE(book.isEmpty());

            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> updateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(updateLastName);
            EXPECT_TRUE(updateLastName->hasSignature<string>());

            string lastName = person::LAST_NAME;
            {
                auto [err, ret] = updateLastName->bind(constCast(book)).call(lastName);

                EXPECT_TRUE(err == error::TargetTypeMismatch);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = updateLastName->bind(constCast(book)).call(lastName);

                EXPECT_TRUE(err == error::TargetTypeMismatch);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
    }


    TEST(ConstMethodOverload, explicitly_making_const_call__on_empty_target)
    {
        {
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);
			
            optional<Method> updateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(updateLastName);
            EXPECT_TRUE(updateLastName->hasSignature<string>());

            string lastName = person::LAST_NAME;
            {
                auto [err, ret] = updateLastName->bind(constCast(RObject{ })).call(lastName);

                EXPECT_TRUE(err == error::EmptyRObject);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = updateLastName->bind(constCast(RObject{ })).call(lastName);

                EXPECT_TRUE(err == error::EmptyRObject);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
    }


    TEST(ConstMethodOverload, semantics_with_heap_target__only_const_method_exists)
    {
        {
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> updateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(updateLastName);

            auto [err0, person] = classPerson->ctor<std::string>()(alloc::Heap, person::FIRST_NAME);

            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // 'person' is created via reflection, so its logically-const,
            // hence const_cast on the object bieng reflected is safe.
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(updateLastName->hasSignature<string>());

            // this will by default bind to the const-method.
            // Since the reflected object is bieng treated as 'const', so the 
            // 'const' method will be preffered with no-need of explicit resolution, since it exists.
            string lastName = person::LAST_NAME;
            auto [err, ret] = updateLastName->bind(person).call(lastName);
            EXPECT_TRUE(err == error::None);
            ASSERT_TRUE(ret.isEmpty());

            EXPECT_TRUE(person::test_method_updateLastName_const(person));
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, semantics_with_stack_target__only_const_method_exists)
    {
        {
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> updateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(updateLastName);

            auto [err0, person] = classPerson->ctor<std::string>()(alloc::Stack, person::FIRST_NAME);

            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // 'person' is created via reflection, so its logically-const,
            // hence const_cast on the object bieng reflected is safe.
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(updateLastName->hasSignature<string>());

            string lastName = person::LAST_NAME;
            // this will by default bind to the const-method.
            // Since the reflected object is bieng treated as 'const', so the 
            // 'const' method will be preffered with no-need of explicit resolution, since it exists.
            auto [err, ret] = updateLastName->bind(person).call(lastName);
            EXPECT_TRUE(err == error::None);
            ASSERT_TRUE(ret.isEmpty());

            EXPECT_TRUE(person::test_method_updateLastName_const(person));
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, implicit_method_resolution__only_const_method_exists__on_heap_target)
    {
        {
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> updateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(updateLastName);

            auto [err0, person] = classPerson->ctor<std::string>()(alloc::Heap, person::FIRST_NAME);

            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(updateLastName->hasSignature<string>());
            {
                string_view lastName = "invalid_arg";
                auto [err, ret] = updateLastName->bind(person).call(lastName);

                EXPECT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            } {
                string lastName = person::LAST_NAME;
                auto [err, ret] = updateLastName->bind(person).call(lastName);

                EXPECT_TRUE(err == error::None);
                ASSERT_TRUE(ret.isEmpty());
            }
            EXPECT_TRUE(person::test_method_updateLastName_const(person));
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, implicit_method_resolution__only_const_method_exists__on_stack_target)
    {
        {
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> updateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(updateLastName);

            auto [err0, person] = classPerson->ctor<std::string>()(alloc::Stack, person::FIRST_NAME);

            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(updateLastName->hasSignature<string>());
            {
                string_view lastName = "invalid_arg";
                auto [err, ret] = updateLastName->bind(person).call(lastName);

                EXPECT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            } {
                string lastName = person::LAST_NAME;
                auto [err, ret] = updateLastName->bind(person).call(lastName);

                EXPECT_TRUE(err == error::None);
                ASSERT_TRUE(ret.isEmpty());
            }
            EXPECT_TRUE(person::test_method_updateLastName_const(person));
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, semantics_with_target_on_heap__overloads_exists)
    {
        {
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
            ASSERT_TRUE(updateAddress);

            auto [err0, person] = classPerson->ctor<std::string>()(alloc::Heap, person::FIRST_NAME);

            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // RTL treats objects created via reflection as logically immutable (i.e., 'const' by default).
            // For such objects, applying a logical 'const_cast' is always safe, hence the check below is true.
            // However, RTL respects the const-ness of objects originating outside RTL (e.g., return values).
            // If an object is provided to RTL as 'const', a 'const_cast' would not be safe, and the check
            // would return false. RTL never performs such unsafe casts internally.
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(updateAddress->hasSignature<string>());
            
            auto address = string(person::ADDRESS);
            {
                // by default it calls the const-method overload. since 
                // it exists and the target is logically-const reflected-object. 
                auto [err, ret] = updateAddress->bind(person).call(address);
                EXPECT_TRUE(err == error::None);
                ASSERT_TRUE(ret.isEmpty());
            } {
                // Since both the oveload exists then implicit call will bind to const-method by default,
                // To explicitly choose the non-const method, we can explicitly bind by wrapping the target
                // in 'rtl::constCast<RObject>'.
                auto [err, ret] = updateAddress->bind(constCast(person)).call(address);
                EXPECT_TRUE(err == error::None);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, semantics_with_target_on_stack__overloads_exists)
    {
        {
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
            ASSERT_TRUE(updateAddress);

            auto [err0, person] = classPerson->ctor<std::string>()(alloc::Stack, person::FIRST_NAME);

            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // RTL treats objects created via reflection as logically immutable (i.e., 'const' by default).
            // For such objects, applying a logical 'const_cast' is always safe, hence the check below is true.
            // However, RTL respects the const-ness of objects originating outside RTL (e.g., return values).
            // If an object is provided to RTL as 'const', a 'const_cast' would not be safe, and the check
            // would return false. RTL never performs such unsafe casts internally.
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(updateAddress->hasSignature<string>());
            
            auto address = string(person::ADDRESS);
            {
                // by default it calls the const-method overload. since 
                // it exists and the target is logically-const reflected-object. 
                auto [err, ret] = updateAddress->bind(person).call(address);
                EXPECT_TRUE(err == error::None);
                ASSERT_TRUE(ret.isEmpty());
            } {
                // Since both the oveload exists then implicit call will bind to const-method by default,
                // To explicitly choose the non-const method, we can explicitly bind by wrapping the target
                // in 'rtl::constCast<RObject>'.
                auto [err, ret] = updateAddress->bind(constCast(person)).call(address);
                EXPECT_TRUE(err == error::None);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, explicitly_bind_non_const_method_with_target_on_heap__only_const_method_exists)
    {
        {
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);
            
            optional<Method> updateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(updateLastName);

            auto [err0, person] = classPerson->ctor<std::string>()(alloc::Heap, person::FIRST_NAME);
            
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered logically-immutable by default. So const_cast on them is safe
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(updateLastName->hasSignature<string>());
            {
                string lastName = person::LAST_NAME;
                auto [err, ret] = updateLastName->bind(constCast(person)).call(lastName);
                
                EXPECT_TRUE(err == error::NonConstOverloadMissing);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = updateLastName->bind(constCast(person)).call(0); //invalid argument

				EXPECT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


	TEST(ConstMethodOverload, explicitly_bind_non_const_method_with_target_on_stack__only_const_method_exists)
    {
        {   
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);
            
            optional<Method> updateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(updateLastName);

            auto [err0, person] = classPerson->ctor<std::string>()(alloc::Stack, person::FIRST_NAME);
            
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(updateLastName->hasSignature<string>());
            {
                string lastName = person::LAST_NAME;
                auto [err, ret] = updateLastName->bind(constCast(person)).call(lastName);
                
                EXPECT_TRUE(err == error::NonConstOverloadMissing);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = updateLastName->bind(constCast(person)).call(0); //invalid argument
                
                EXPECT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, explicit_non_const_method_resolution__only_non_const_method_exists__on_heap_target)
    {
        {   
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);
            
            optional<Method> getFirstName = classPerson->getMethod(person::str_getFirstName);
            ASSERT_TRUE(getFirstName);
            
            auto [err0, person] = classPerson->ctor<std::string>()(alloc::Heap, person::FIRST_NAME);
            
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(getFirstName->hasSignature<>());
            {
                auto [err, ret] = getFirstName->bind(constCast(person)).call(0); //invalid argument
                
                EXPECT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = getFirstName->bind(constCast(person)).call();
                
                EXPECT_TRUE(err == error::None);
                ASSERT_FALSE(ret.isEmpty());
                EXPECT_TRUE(ret.canViewAs<std::string>());
                
                auto& fname = ret.view<std::string>()->get();
                EXPECT_EQ(fname, std::string(person::FIRST_NAME));
            }
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, explicit_non_const_method_resolution__only_non_const_method_exists__on_stack_target)
    {
        {
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> getFirstName = classPerson->getMethod(person::str_getFirstName);
            ASSERT_TRUE(getFirstName);

            auto [err0, person] = classPerson->ctor<std::string>()(alloc::Stack, person::FIRST_NAME);

            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(getFirstName->hasSignature<>());
            {
                auto [err, ret] = getFirstName->bind(constCast(person)).call(0); //invalid argument

                EXPECT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = getFirstName->bind(constCast(person)).call();

                EXPECT_TRUE(err == error::None);
                ASSERT_FALSE(ret.isEmpty());
                EXPECT_TRUE(ret.canViewAs<std::string>());

                auto& fname = ret.view<std::string>()->get();
                EXPECT_EQ(fname, std::string(person::FIRST_NAME));
            }
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, explicit_method_resolution__only_non_const_method_exists__call_on_returned_const_target)
    {
        {
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> createConstPerson = classPerson->getMethod(person::str_createConst);
            ASSERT_TRUE(createConstPerson);

            auto createPerson = createConstPerson->argsT<>().returnT<>();
            ASSERT_TRUE(createPerson);
            EXPECT_EQ(createPerson.get_init_error(), rtl::error::None);

            auto [err0, constPerson] = createPerson();
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(constPerson.isEmpty());
            // RTL treats own objects as mutable (logical const enforced), preserves external const; type system ensures const-safety.
            EXPECT_FALSE(constPerson.isConstCastSafe());

            optional<Method> getFirstName = classPerson->getMethod(person::str_getFirstName);
            ASSERT_TRUE(getFirstName);

            EXPECT_TRUE(getFirstName->hasSignature<>());
            {
                auto [err, ret] = getFirstName->bind(constPerson).call();

                // A non-const version exists, but the object itself is truly const.
                // Therefore, only const-qualified methods can be called on it.
                // However, no const-overload is available.
                EXPECT_TRUE(err == error::ConstOverloadMissing);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = getFirstName->bind(constCast(constPerson)).call();
                EXPECT_TRUE(err == error::IllegalConstCast);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, explicit_method_resolution__only_non_const_method_exists__call_on_returned_const_pointer_target)
    {
        {
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> createConstPtrPerson = classPerson->getMethod(person::str_createPtr);
            ASSERT_TRUE(createConstPtrPerson);

            auto createPerson = createConstPtrPerson->argsT<>().returnT<>();
            ASSERT_TRUE(createPerson);
            EXPECT_EQ(createPerson.get_init_error(), rtl::error::None);

            // Returns 'const Person*', unmanaged, need explicit call to 'delete'.
            auto [err0, constPersonPtr] = createPerson();
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(constPersonPtr.isEmpty());
            // RTL treats own objects as mutable (logical const enforced), preserves external const; type system ensures const-safety.
            EXPECT_FALSE(constPersonPtr.isConstCastSafe());

            optional<Method> getFirstName = classPerson->getMethod(person::str_getFirstName);
            ASSERT_TRUE(getFirstName);

            EXPECT_TRUE(getFirstName->hasSignature<>());
            {
                auto [err, ret] = getFirstName->bind(constPersonPtr).call();
                // A non-const version exists, but the object itself is truly const.
                // Therefore, only const-qualified methods can be called on it.
                // However, no const-overload is available.
                EXPECT_TRUE(err == error::ConstOverloadMissing);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = getFirstName->bind(constCast(constPersonPtr)).call();

                EXPECT_TRUE(err == error::IllegalConstCast);
                ASSERT_TRUE(ret.isEmpty());
            }
            EXPECT_TRUE(person::delete_unmanaged_person_instance_created_via_createPtr(constPersonPtr));
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }
}