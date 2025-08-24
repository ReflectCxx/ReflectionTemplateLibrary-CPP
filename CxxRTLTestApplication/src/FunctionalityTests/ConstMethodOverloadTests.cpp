#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsPerson.h"
#include "TestUtilsBook.h"

using namespace std;
using namespace rtl;
using namespace rtl::access;
using namespace test_utils;
using namespace the_reflection;

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
                // auto [err, ret] = getDefaults->bind<methodQ::Const>().call();
                // auto [err, ret] = getDefaults->bind<methodQ::NonConst>().call();
                // auto [err, ret] = getDefaults->bind<methodQ::None>().call();
            }
        }
    }


    TEST(ConstMethodOverload, explicitly_making_const_call__on_wrong_target)
    {
        {
            optional<Record> classBook = cxx::mirror().getRecord(book::class_);
            ASSERT_TRUE(classBook);

            auto [err0, book] = classBook->create<alloc::Stack>();
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
                auto [err, ret] = updateLastName->bind<methodQ::Const>(book).call(lastName);

                EXPECT_TRUE(err == error::TargetMismatch);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = updateLastName->bind<methodQ::NonConst>(book).call(lastName);

                EXPECT_TRUE(err == error::TargetMismatch);
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
                auto [err, ret] = updateLastName->bind<methodQ::Const>(RObject()).call(lastName);

                EXPECT_TRUE(err == error::EmptyRObject);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = updateLastName->bind<methodQ::NonConst>(RObject()).call(lastName);

                EXPECT_TRUE(err == error::EmptyRObject);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
    }


    TEST(ConstMethodOverload, implicit_method_resolution__only_const_method_exists__on_heap_target)
    {
        {
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> updateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(updateLastName);

            string firstName = person::FIRST_NAME;
            auto [err0, person] = classPerson->create<alloc::Heap>(firstName);

            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(updateLastName->hasSignature<string>());
            {
                string_view lastName = "invalid_arg";
                auto [err, ret] = (*updateLastName)(person)(lastName);

                EXPECT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            } {
                string lastName = person::LAST_NAME;
                auto [err, ret] = (*updateLastName)(person)(lastName);

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

            string firstName = person::FIRST_NAME;
            auto [err0, person] = classPerson->create<alloc::Stack>(firstName);

            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(updateLastName->hasSignature<string>());
            {
                string_view lastName = "invalid_arg";
                auto [err, ret] = (*updateLastName)(person)(lastName);

                EXPECT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            } {
                string lastName = person::LAST_NAME;
                auto [err, ret] = (*updateLastName)(person)(lastName);

                EXPECT_TRUE(err == error::None);
                ASSERT_TRUE(ret.isEmpty());
            }
            EXPECT_TRUE(person::test_method_updateLastName_const(person));
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, implicit_method_resolution__overloads_exists__on_heap_target)
    {
        {
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
            ASSERT_TRUE(updateAddress);

            string firstName = person::FIRST_NAME;
            auto [err0, person] = classPerson->create<alloc::Heap>(firstName);

            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // RTL treats objects created via reflection as logically immutable (i.e., 'const' by default).
            // For such objects, applying a logical 'const_cast' is always safe, hence the check below is true.
            // However, RTL respects the const-ness of objects originating outside RTL (e.g., return values).
            // If an object is provided to RTL as 'const', a 'const_cast' would not be safe, and the check
            // would return false. RTL never performs such unsafe casts internally.
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(updateAddress->hasSignature<string>());
            {
                auto address = string(person::ADDRESS);
                auto [err, ret] = updateAddress->bind(person).call(address);

                EXPECT_TRUE(err == error::AmbiguousConstOverload);
                ASSERT_TRUE(ret.isEmpty());
            } {
                string_view address = "invalid_arg";
                auto [err, ret] = updateAddress->bind(person).call(address);

                EXPECT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, implicit_method_resolution__overloads_exists__on_stack_target)
    {
        {
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
            ASSERT_TRUE(updateAddress);

            string firstName = person::FIRST_NAME;
            auto [err0, person] = classPerson->create<alloc::Stack>(firstName);

            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(updateAddress->hasSignature<string>());
            {
                auto address = string(person::ADDRESS);
                auto [err, ret] = updateAddress->bind(person).call(address);

                EXPECT_TRUE(err == error::AmbiguousConstOverload);
                ASSERT_TRUE(ret.isEmpty());
            } {
                string_view address = "invalid_arg";
                auto [err, ret] = updateAddress->bind(person).call(address);

                EXPECT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, explicit_const_method_resolution__only_const_method_exists__on_heap_target)
    {
        {
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> updateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(updateLastName);

            string lastName = person::LAST_NAME;
            string firstName = person::FIRST_NAME;
            auto [err0, person] = classPerson->create<alloc::Heap>(firstName);

            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(updateLastName->hasSignature<string>());
            {
                auto [err, ret] = updateLastName->bind<methodQ::NonConst>(person).call(0); //invalid argument

                EXPECT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = updateLastName->bind<methodQ::Const>(person).call(lastName);

                EXPECT_TRUE(err == error::None);
                ASSERT_TRUE(ret.isEmpty());
            }
            EXPECT_TRUE(person::test_method_updateLastName_const(person));
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, explicit_const_method_resolution__only_const_method_exists__on_stack_target)
    {
        {
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> updateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(updateLastName);

            string lastName = person::LAST_NAME;
            string firstName = person::FIRST_NAME;

            auto [err0, person] = classPerson->create<alloc::Stack>(firstName);

            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(updateLastName->hasSignature<string>());
            {
                auto [err, ret] = updateLastName->bind<methodQ::NonConst>(person).call(0); //invlid argument
                
                EXPECT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = updateLastName->bind<methodQ::Const>(person).call(lastName);
                
                EXPECT_TRUE(err == error::None);
                ASSERT_TRUE(ret.isEmpty());
            }
            EXPECT_TRUE(person::test_method_updateLastName_const(person));
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, explicit_non_const_method_resolution__only_const_method_exists__on_heap_target)
    {
        {   
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);
            
            optional<Method> updateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(updateLastName);
            
            string lastName = person::LAST_NAME;
            string firstName = person::FIRST_NAME;
            
            auto [err0, person] = classPerson->create<alloc::Heap>(firstName);
            
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(updateLastName->hasSignature<string>());
            {
                auto [err, ret] = updateLastName->bind<methodQ::NonConst>(person).call(lastName);
                
                EXPECT_TRUE(err == error::NonConstOverloadMissing);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = updateLastName->bind<methodQ::NonConst>(person).call(0); //invalid argument

				EXPECT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


	TEST(ConstMethodOverload, explicit_non_const_method_resolution__only_const_method_exists__on_stack_target)
    {
        {   
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);
            
            optional<Method> updateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(updateLastName);
            
            string lastName = person::LAST_NAME;
            string firstName = person::FIRST_NAME;
            auto [err0, person] = classPerson->create<alloc::Stack>(firstName);
            
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(updateLastName->hasSignature<string>());
            {
                auto [err, ret] = updateLastName->bind<methodQ::NonConst>(person).call(lastName);
                
                EXPECT_TRUE(err == error::NonConstOverloadMissing);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = updateLastName->bind<methodQ::NonConst>(person).call(0); //invalid argument
                
                EXPECT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, explicit_const_method_resolution__only_non_const_method_exists__on_heap_target)
    {
        {
			optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);
            
            optional<Method> getFirstName = classPerson->getMethod(person::str_getFirstName);
            ASSERT_TRUE(getFirstName);
            
            string firstName = person::FIRST_NAME;
            auto [err0, person] = classPerson->create<alloc::Heap>(firstName);
            
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(getFirstName->hasSignature<>());
            {
                auto [err, ret] = getFirstName->bind<methodQ::Const>(person).call();
                
                EXPECT_TRUE(err == error::ConstOverloadMissing);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = getFirstName->bind<methodQ::Const>(person).call(0); //invalid argument
                
                EXPECT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, explicit_const_method_resolution__only_non_const_method_exists__on_stack_target)
    {
        {   
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);
            
            optional<Method> getFirstName = classPerson->getMethod(person::str_getFirstName);
            ASSERT_TRUE(getFirstName);
            
            string firstName = person::FIRST_NAME;
            auto [err0, person] = classPerson->create<alloc::Stack>(firstName);
            
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(getFirstName->hasSignature<>());
            {
                auto [err, ret] = getFirstName->bind<methodQ::Const>(person).call();
                
                EXPECT_TRUE(err == error::ConstOverloadMissing);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = getFirstName->bind<methodQ::Const>(person).call(0); //invalid argument
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
            
            string firstName = person::FIRST_NAME;
            auto [err0, person] = classPerson->create<alloc::Heap>(firstName);
            
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(getFirstName->hasSignature<>());
            {
                auto [err, ret] = getFirstName->bind<methodQ::Const>(person).call(0); //invalid argument
                
                EXPECT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = getFirstName->bind<methodQ::NonConst>(person).call();
                
                EXPECT_TRUE(err == error::None);
                ASSERT_FALSE(ret.isEmpty());
                EXPECT_TRUE(ret.canViewAs<std::string>());
                
                auto& fname = ret.view<std::string>()->get();
                EXPECT_EQ(fname, firstName);
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

            string firstName = person::FIRST_NAME;
            auto [err0, person] = classPerson->create<alloc::Stack>(firstName);

            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(person.isConstCastSafe());
            EXPECT_TRUE(getFirstName->hasSignature<>());
            {
                auto [err, ret] = getFirstName->bind<methodQ::Const>(person).call(0); //invalid argument

                EXPECT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = getFirstName->bind<methodQ::NonConst>(person).call();

                EXPECT_TRUE(err == error::None);
                ASSERT_FALSE(ret.isEmpty());
                EXPECT_TRUE(ret.canViewAs<std::string>());

                auto& fname = ret.view<std::string>()->get();
                EXPECT_EQ(fname, firstName);
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

            auto [err0, constPerson] = createConstPerson->bind().call();
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(constPerson.isEmpty());
            // RTL treats own objects as mutable (logical const enforced), preserves external const; type system ensures const-safety.
            EXPECT_FALSE(constPerson.isConstCastSafe());

            optional<Method> getFirstName = classPerson->getMethod(person::str_getFirstName);
            ASSERT_TRUE(getFirstName);

            string firstName = person::FIRST_NAME;
            EXPECT_TRUE(getFirstName->hasSignature<>());
            {
                auto [err, ret] = getFirstName->bind(constPerson).call();

                EXPECT_TRUE(err == error::ConstCallViolation);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = getFirstName->bind<methodQ::NonConst>(constPerson).call();
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

            // Returns 'const Person*', unmanaged, need explicit call to 'delete'.
            auto [err0, constPersonPtr] = createConstPtrPerson->bind().call();
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(constPersonPtr.isEmpty());
            // RTL treats own objects as mutable (logical const enforced), preserves external const; type system ensures const-safety.
            EXPECT_FALSE(constPersonPtr.isConstCastSafe());

            optional<Method> getFirstName = classPerson->getMethod(person::str_getFirstName);
            ASSERT_TRUE(getFirstName);

            string firstName = person::FIRST_NAME;
            EXPECT_TRUE(getFirstName->hasSignature<>());
            {
                auto [err, ret] = getFirstName->bind(constPersonPtr).call();

                EXPECT_TRUE(err == error::ConstCallViolation);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = getFirstName->bind<methodQ::NonConst>(constPersonPtr).call();

                EXPECT_TRUE(err == error::IllegalConstCast);
                ASSERT_TRUE(ret.isEmpty());
            }
            EXPECT_TRUE(person::delete_unmanaged_person_instance_created_via_createPtr(constPersonPtr));
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }
}