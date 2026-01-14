
#include <rtl_access.h>
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
    TEST(ConstMethodOverload, explicitly_making_const_call__on_wrong_target)
    {
        {
            optional<Record> classBook = cxx::mirror().getRecord(book::class_);
            ASSERT_TRUE(classBook);

            auto [err0, book] = classBook->ctor()(alloc::Stack);
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(book.isEmpty());

            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> oUpdateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(oUpdateLastName);
            EXPECT_TRUE(oUpdateLastName->hasSignature<string>());

            method<RObject, Return(string)> updateLastName = oUpdateLastName->targetT().argsT<string>().returnT();
            EXPECT_TRUE(updateLastName);
            {
                auto [err, ret] = updateLastName(book)(person::LAST_NAME);
                // Only const method exits for this function, no non-const overload.
                EXPECT_TRUE(err == error::NonConstOverloadMissing);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = updateLastName(std::cref(book))(person::LAST_NAME);

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
			
            optional<Method> oUpdateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(oUpdateLastName);
            EXPECT_TRUE(oUpdateLastName->hasSignature<string>());

            method<RObject, Return(string)> updateLastName = oUpdateLastName->targetT().argsT<string>().returnT();
            EXPECT_TRUE(updateLastName);
            {
                // only const-overload exists, this tries to call the non-const version since 
                // the 'robj' is non-const.
                RObject robj;
                auto [err, ret] = updateLastName(robj)(person::LAST_NAME);
                EXPECT_TRUE(err == error::NonConstOverloadMissing);
                ASSERT_TRUE(ret.isEmpty());
            } {
                // Here the const-method is invoked, since the 'robj' is decleared const,
                // it automatically binds to const-overload, however the 'robj' is empty
                // hence the expecetd return error is error::EmptyRObject.
                const RObject robj;
                auto [err, ret] = updateLastName(robj)(person::LAST_NAME);
                EXPECT_TRUE(err == error::EmptyRObject);
                ASSERT_TRUE(ret.isEmpty());
            }
        }
    }


    TEST(ConstMethodOverload, semantics_when_only_const_method_exists)
    {
        auto testWithAllocOn = [](alloc alloc)->void
        {
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            optional<Method> oUpdateLastName = classPerson->getMethod(person::str_updateLastName);
            ASSERT_TRUE(oUpdateLastName);

            auto [err0, person] = classPerson->ctor<std::string>()(alloc, person::FIRST_NAME);

            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());
            EXPECT_TRUE(oUpdateLastName->hasSignature<string>());

            method<RObject, Return(string)> updateLastName = oUpdateLastName->targetT().argsT<string>().returnT();
            EXPECT_TRUE(updateLastName);
            {
                auto [err, ret] = updateLastName(person)(person::LAST_NAME);
                // only const method exists, no non-const overload found.
                EXPECT_TRUE(err == error::NonConstOverloadMissing);
                ASSERT_TRUE(ret.isEmpty());
            } {
                // explicit call to const method.
                auto [err, ret] = updateLastName(std::cref(person))(person::LAST_NAME);

                EXPECT_TRUE(err == error::None);
                ASSERT_TRUE(ret.isEmpty());
            }
            EXPECT_TRUE(person::test_method_updateLastName_const(person));
        };

        testWithAllocOn(alloc::Heap);
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);

        testWithAllocOn(alloc::Stack);
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(ConstMethodOverload, semantics_when_const_and_nonconst_overload_exists)
    {
        auto testWithAllocOn = [](alloc alloc)->void
        {
            optional<Record> classPerson = cxx::mirror().getRecord(person::class_);
            ASSERT_TRUE(classPerson);

            auto [err0, person] = classPerson->ctor<std::string>()(alloc, person::FIRST_NAME);
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(person.isEmpty());

            optional<Method> oUpdateAddress = classPerson->getMethod(person::str_updateAddress);
            ASSERT_TRUE(oUpdateAddress);
            EXPECT_TRUE(oUpdateAddress->hasSignature<string>());

            method<RObject, Return(string)> updateAddress = oUpdateAddress->targetT().argsT<string>().returnT();
            EXPECT_TRUE(updateAddress);
            {
                // sending 'person' as const (using std::cref) calls the const-method overload.
                auto [err, ret] = updateAddress(cref(person))(person::ADDRESS);
                EXPECT_TRUE(err == error::None);
                ASSERT_TRUE(ret.isEmpty());
            } {
                // sending 'person' as non-const calls the non-const-method overload.
                auto [err, ret] = updateAddress(person)(person::ADDRESS);
                EXPECT_TRUE(err == error::None);
                ASSERT_TRUE(ret.isEmpty());
            }
        };

        testWithAllocOn(alloc::Heap);
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);

        testWithAllocOn(alloc::Stack);
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

            static_method<Return()> createPerson = createConstPerson->argsT().returnT();
            EXPECT_TRUE(createPerson);
            EXPECT_EQ(createPerson.get_init_error(), rtl::error::None);

            auto [err0, constPerson] = createPerson();
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(constPerson.isEmpty());

            optional<Method> oGetFirstName = classPerson->getMethod(person::str_getFirstName);
            ASSERT_TRUE(oGetFirstName);
            EXPECT_TRUE(oGetFirstName->hasSignature<>());

            method<RObject, Return()> getFirstName = oGetFirstName->targetT().argsT().returnT();
            EXPECT_TRUE(getFirstName);
            {
                auto [err, ret] = getFirstName(cref(constPerson))();

                // A non-const version exists, but the object itself is truly const.
                // Therefore, only const-qualified methods can be called on it.
                // However, no const-overload is available.
                EXPECT_TRUE(err == error::ConstOverloadMissing);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = getFirstName(constPerson)();
                EXPECT_TRUE(err == error::InvalidCallOnConstTarget);
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

            static_method<Return()> createPerson = createConstPtrPerson->argsT().returnT();
            EXPECT_TRUE(createPerson);
            EXPECT_EQ(createPerson.get_init_error(), rtl::error::None);

            // Returns 'const Person*', unmanaged, need explicit call to 'delete'.
            auto [err0, constPersonPtr] = createPerson();
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(constPersonPtr.isEmpty());

            optional<Method> oGetFirstName = classPerson->getMethod(person::str_getFirstName);
            ASSERT_TRUE(oGetFirstName);
            EXPECT_TRUE(oGetFirstName->hasSignature<>());

            method<RObject, Return()> getFirstName = oGetFirstName->targetT().argsT().returnT();
            EXPECT_TRUE(getFirstName);
            {
                auto [err, ret] = getFirstName(cref(constPersonPtr))();
                // A non-const version exists, but the object itself is truly const.
                // Therefore, only const-qualified methods can be called on it.
                // However, no const-overload is available.
                EXPECT_TRUE(err == error::ConstOverloadMissing);
                ASSERT_TRUE(ret.isEmpty());
            } {
                auto [err, ret] = getFirstName(constPersonPtr)();
                EXPECT_TRUE(err == error::InvalidCallOnConstTarget);
                ASSERT_TRUE(ret.isEmpty());
            }
            EXPECT_TRUE(person::delete_unmanaged_person_instance_created_via_createPtr(constPersonPtr));
        }
        EXPECT_TRUE(person::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }
}