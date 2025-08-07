#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsPerson.h"
#include "TestUtilsBook.h"

using namespace std;
using namespace rtl;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests
{
    TEST(ConstMethodOverload, explicitly_making_const_call__on_static_method)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> classPerson = cxxMirror.getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> getDefaults = classPerson->getMethod(person::str_getDefaults);
            ASSERT_TRUE(getDefaults);
            ASSERT_TRUE(getDefaults->hasSignature<>());
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
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> classBook = cxxMirror.getRecord(book::class_);
            ASSERT_TRUE(classBook);

            auto [err0, book] = classBook->create<alloc::Stack>();
            ASSERT_TRUE(err0 == error::None);
            // Objects created through reflection are considered mutable (non-const) by default.
            ASSERT_FALSE(book.isConst());
            ASSERT_FALSE(book.isEmpty());

            optional<Record> classPerson = cxxMirror.getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> updateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(updateLastName);
            ASSERT_TRUE(updateLastName->hasSignature<string>());

            string lastName = person::LAST_NAME;
            {
                auto [err, ret] = updateLastName->bind<methodQ::Const>(book).call(lastName);

                ASSERT_TRUE(err == error::MethodTargetMismatch);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = updateLastName->bind<methodQ::NonConst>(book).call(lastName);

                ASSERT_TRUE(err == error::MethodTargetMismatch);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
    }


    TEST(ConstMethodOverload, explicitly_making_const_call__on_empty_target)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> classPerson = cxxMirror.getRecord(person::class_);
            ASSERT_TRUE(classPerson);
			
            optional<Method> updateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(updateLastName);
            ASSERT_TRUE(updateLastName->hasSignature<string>());

            string lastName = person::LAST_NAME;
            {
                auto [err, ret] = updateLastName->bind<methodQ::Const>(RObject()).call(lastName);

                ASSERT_TRUE(err == error::EmptyRObject);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = updateLastName->bind<methodQ::NonConst>(RObject()).call(lastName);

                ASSERT_TRUE(err == error::EmptyRObject);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
    }


    TEST(ConstMethodOverload, implicit_method_resolution__only_const_method_exists__on_heap_target)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> classPerson = cxxMirror.getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> updateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(updateLastName);

            string firstName = person::FIRST_NAME;
            auto [err0, person] = classPerson->create<alloc::Heap>(firstName);

            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            ASSERT_FALSE(person.isConst());
            ASSERT_TRUE(updateLastName->hasSignature<string>());
            {
                string_view lastName = "invalid_arg";
                auto [err, ret] = (*updateLastName)(person)(lastName);

                ASSERT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            } {
                string lastName = person::LAST_NAME;
                auto [err, ret] = (*updateLastName)(person)(lastName);

                ASSERT_TRUE(err == error::None);
                ASSERT_TRUE(ret.isEmpty());
            }
            EXPECT_TRUE(person::test_method_updateLastName_const(person.get(), person.isOnHeap()));
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, implicit_method_resolution__only_const_method_exists__on_stack_target)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> classPerson = cxxMirror.getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> updateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(updateLastName);

            string firstName = person::FIRST_NAME;
            auto [err0, person] = classPerson->create<alloc::Stack>(firstName);

            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            ASSERT_FALSE(person.isConst());
            ASSERT_TRUE(updateLastName->hasSignature<string>());
            {
                string_view lastName = "invalid_arg";
                auto [err, ret] = (*updateLastName)(person)(lastName);

                ASSERT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            } {
                string lastName = person::LAST_NAME;
                auto [err, ret] = (*updateLastName)(person)(lastName);

                ASSERT_TRUE(err == error::None);
                ASSERT_TRUE(ret.isEmpty());
            }
            EXPECT_TRUE(person::test_method_updateLastName_const(person.get(), person.isOnHeap()));
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, implicit_method_resolution__overloads_exists__on_heap_target)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> classPerson = cxxMirror.getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
            ASSERT_TRUE(updateAddress);

            string firstName = person::FIRST_NAME;
            auto [err0, person] = classPerson->create<alloc::Heap>(firstName);

            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            ASSERT_FALSE(person.isConst());
            ASSERT_TRUE(updateAddress->hasSignature<string>());
            {
                auto address = string(person::ADDRESS);
                auto [err, ret] = updateAddress->bind(person).call(address);

                ASSERT_TRUE(err == error::AmbiguousConstOverload);
                ASSERT_TRUE(ret.isEmpty());
            } {
                string_view address = "invalid_arg";
                auto [err, ret] = updateAddress->bind(person).call(address);

                ASSERT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, implicit_method_resolution__overloads_exists__on_stack_target)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> classPerson = cxxMirror.getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> updateAddress = classPerson->getMethod(person::str_updateAddress);
            ASSERT_TRUE(updateAddress);

            string firstName = person::FIRST_NAME;
            auto [err0, person] = classPerson->create<alloc::Stack>(firstName);

            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            ASSERT_FALSE(person.isConst());
            ASSERT_TRUE(updateAddress->hasSignature<string>());
            {
                auto address = string(person::ADDRESS);
                auto [err, ret] = updateAddress->bind(person).call(address);

                ASSERT_TRUE(err == error::AmbiguousConstOverload);
                ASSERT_TRUE(ret.isEmpty());
            } {
                string_view address = "invalid_arg";
                auto [err, ret] = updateAddress->bind(person).call(address);

                ASSERT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, explicit_const_method_resolution__only_const_method_exists__on_heap_target)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> classPerson = cxxMirror.getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> updateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(updateLastName);

            string lastName = person::LAST_NAME;
            string firstName = person::FIRST_NAME;
            auto [err0, person] = classPerson->create<alloc::Heap>(firstName);

            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            ASSERT_FALSE(person.isConst());
            ASSERT_TRUE(updateLastName->hasSignature<string>());
            {
                auto [err, ret] = updateLastName->bind<methodQ::NonConst>(person).call(0); //invalid argument

                ASSERT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = updateLastName->bind<methodQ::Const>(person).call(lastName);

                ASSERT_TRUE(err == error::None);
                ASSERT_TRUE(ret.isEmpty());
            }
            EXPECT_TRUE(person::test_method_updateLastName_const(person.get(), person.isOnHeap()));
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, explicit_const_method_resolution__only_const_method_exists__on_stack_target)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> classPerson = cxxMirror.getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> updateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(updateLastName);

            string lastName = person::LAST_NAME;
            string firstName = person::FIRST_NAME;

            auto [err0, person] = classPerson->create<alloc::Stack>(firstName);

            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            ASSERT_FALSE(person.isConst());
            ASSERT_TRUE(updateLastName->hasSignature<string>());
            {
                auto [err, ret] = updateLastName->bind<methodQ::NonConst>(person).call(0); //invlid argument
                
                ASSERT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = updateLastName->bind<methodQ::Const>(person).call(lastName);
                
                ASSERT_TRUE(err == error::None);
                ASSERT_TRUE(ret.isEmpty());
            }
            EXPECT_TRUE(person::test_method_updateLastName_const(person.get(), person.isOnHeap()));
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, explicit_non_const_method_resolution__only_const_method_exists__on_heap_target)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();
            
            optional<Record> classPerson = cxxMirror.getRecord(person::class_);
            ASSERT_TRUE(classPerson);
            
            optional<Method> updateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(updateLastName);
            
            string lastName = person::LAST_NAME;
            string firstName = person::FIRST_NAME;
            
            auto [err0, person] = classPerson->create<alloc::Heap>(firstName);
            
            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            ASSERT_FALSE(person.isConst());
            ASSERT_TRUE(updateLastName->hasSignature<string>());
            {
                auto [err, ret] = updateLastName->bind<methodQ::NonConst>(person).call(lastName);
                
                ASSERT_TRUE(err == error::NonConstMethodOverloadNotFound);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = updateLastName->bind<methodQ::NonConst>(person).call(0); //invalid argument

				ASSERT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


	TEST(ConstMethodOverload, explicit_non_const_method_resolution__only_const_method_exists__on_stack_target)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();
            
            optional<Record> classPerson = cxxMirror.getRecord(person::class_);
            ASSERT_TRUE(classPerson);
            
            optional<Method> updateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(updateLastName);
            
            string lastName = person::LAST_NAME;
            string firstName = person::FIRST_NAME;
            auto [err0, person] = classPerson->create<alloc::Stack>(firstName);
            
            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            ASSERT_FALSE(person.isConst());
            ASSERT_TRUE(updateLastName->hasSignature<string>());
            {
                auto [err, ret] = updateLastName->bind<methodQ::NonConst>(person).call(lastName);
                
                ASSERT_TRUE(err == error::NonConstMethodOverloadNotFound);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = updateLastName->bind<methodQ::NonConst>(person).call(0); //invalid argument
                
                ASSERT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, explicit_const_method_resolution__only_non_const_method_exists__on_heap_target)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classPerson = cxxMirror.getRecord(person::class_);
            ASSERT_TRUE(classPerson);
            
            optional<Method> getFirstName = classPerson->getMethod(person::str_getFirstName);
            ASSERT_TRUE(getFirstName);
            
            string firstName = person::FIRST_NAME;
            auto [err0, person] = classPerson->create<alloc::Heap>(firstName);
            
            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            ASSERT_FALSE(person.isConst());
            ASSERT_TRUE(getFirstName->hasSignature<>());
            {
                auto [err, ret] = getFirstName->bind<methodQ::Const>(person).call();
                
                ASSERT_TRUE(err == error::ConstMethodOverloadNotFound);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = getFirstName->bind<methodQ::Const>(person).call(0); //invalid argument
                
                ASSERT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, explicit_const_method_resolution__only_non_const_method_exists__on_stack_target)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();
            
            optional<Record> classPerson = cxxMirror.getRecord(person::class_);
            ASSERT_TRUE(classPerson);
            
            optional<Method> getFirstName = classPerson->getMethod(person::str_getFirstName);
            ASSERT_TRUE(getFirstName);
            
            string firstName = person::FIRST_NAME;
            auto [err0, person] = classPerson->create<alloc::Stack>(firstName);
            
            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            ASSERT_FALSE(person.isConst());
            ASSERT_TRUE(getFirstName->hasSignature<>());
            {
                auto [err, ret] = getFirstName->bind<methodQ::Const>(person).call();
                
                ASSERT_TRUE(err == error::ConstMethodOverloadNotFound);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = getFirstName->bind<methodQ::Const>(person).call(0); //invalid argument
                ASSERT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, explicit_non_const_method_resolution__only_non_const_method_exists__on_heap_target)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();
            
            optional<Record> classPerson = cxxMirror.getRecord(person::class_);
            ASSERT_TRUE(classPerson);
            
            optional<Method> getFirstName = classPerson->getMethod(person::str_getFirstName);
            ASSERT_TRUE(getFirstName);
            
            string firstName = person::FIRST_NAME;
            auto [err0, person] = classPerson->create<alloc::Heap>(firstName);
            
            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            ASSERT_FALSE(person.isConst());
            ASSERT_TRUE(getFirstName->hasSignature<>());
            {
                auto [err, ret] = getFirstName->bind<methodQ::Const>(person).call(0); //invalid argument
                
                ASSERT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = getFirstName->bind<methodQ::NonConst>(person).call();
                
                ASSERT_TRUE(err == error::None);
                ASSERT_FALSE(ret.isEmpty());
                ASSERT_TRUE(ret.canViewAs<std::string>());
                
                auto& fname = ret.view<std::string>()->get();
                EXPECT_EQ(fname, firstName);
            }
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, explicit_non_const_method_resolution__only_non_const_method_exists__on_stack_target)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> classPerson = cxxMirror.getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> getFirstName = classPerson->getMethod(person::str_getFirstName);
            ASSERT_TRUE(getFirstName);

            string firstName = person::FIRST_NAME;
            auto [err0, person] = classPerson->create<alloc::Stack>(firstName);

            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            ASSERT_FALSE(person.isConst());
            ASSERT_FALSE(person.isConst());
            ASSERT_TRUE(getFirstName->hasSignature<>());
            {
                auto [err, ret] = getFirstName->bind<methodQ::Const>(person).call(0); //invalid argument

                ASSERT_TRUE(err == error::SignatureMismatch);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = getFirstName->bind<methodQ::NonConst>(person).call();

                ASSERT_TRUE(err == error::None);
                ASSERT_FALSE(ret.isEmpty());
                ASSERT_TRUE(ret.canViewAs<std::string>());

                auto& fname = ret.view<std::string>()->get();
                EXPECT_EQ(fname, firstName);
            }
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, explicit_non_const_method_resolution__only_non_const_method_exists__on_const_target)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> classPerson = cxxMirror.getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> createConstPerson = classPerson->getMethod(person::str_createConst);
            ASSERT_TRUE(createConstPerson);

            // Objects created through reflection are considered mutable (non-const) by default.
            // But return-values can be 'const' objects.
            auto [err0, constPerson] = createConstPerson->bind().call();
            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(constPerson.isEmpty());
            ASSERT_TRUE(constPerson.isConst());

            optional<Method> getFirstName = classPerson->getMethod(person::str_getFirstName);
            ASSERT_TRUE(getFirstName);

            string firstName = person::FIRST_NAME;
            ASSERT_TRUE(getFirstName->hasSignature<>());
            {
                auto [err, ret] = getFirstName->bind(constPerson).call();

                ASSERT_TRUE(err == error::ImplicitCallToNonConstOnConstTarget);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = getFirstName->bind<methodQ::NonConst>(constPerson).call();

                ASSERT_TRUE(err == error::None);
                ASSERT_FALSE(ret.isEmpty());
                ASSERT_TRUE(ret.canViewAs<std::string>());
            }
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, explicit_non_const_method_resolution__only_non_const_method_exists__on_const_ptr_target)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> classPerson = cxxMirror.getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> createConstPtrPerson = classPerson->getMethod(person::str_createPtr);
            ASSERT_TRUE(createConstPtrPerson);

            // Returns 'const Person*', unmanaged, need explicit call to 'delete'.
            auto [err0, constPersonPtr] = createConstPtrPerson->bind().call();
            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(constPersonPtr.isEmpty());
            // Objects created through reflection are considered mutable (non-const) by default.
            // But return-values can be 'const' objects.
            ASSERT_TRUE(constPersonPtr.isConst());

            optional<Method> getFirstName = classPerson->getMethod(person::str_getFirstName);
            ASSERT_TRUE(getFirstName);

            string firstName = person::FIRST_NAME;
            ASSERT_TRUE(getFirstName->hasSignature<>());
            {
                auto [err, ret] = getFirstName->bind(constPersonPtr).call();

                ASSERT_TRUE(err == error::ImplicitCallToNonConstOnConstTarget);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = getFirstName->bind<methodQ::NonConst>(constPersonPtr).call();

                ASSERT_TRUE(err == error::None);
                ASSERT_FALSE(ret.isEmpty());
                ASSERT_TRUE(ret.canViewAs<std::string>());
            }
            EXPECT_TRUE(person::delete_unmanaged_person_instance_created_via_createPtr(constPersonPtr.get()));
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }
}