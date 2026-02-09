
#include <rtl_access.h>
#include <gtest/gtest.h>

#include "TestMirrorProvider.h"
#include "TestUtilsBook.h"
#include "TestUtilsDate.h"

using namespace std;
using namespace rtl;

using namespace test_utils;


namespace rtl_tests
{
    TEST(CopyConstructor, clone_default_instance_on_heap_source_on_heap)
    {
        {
            optional<Record> classBook = cxx::mirror().getRecord(cxx::type::Book::id);
            ASSERT_TRUE(classBook);

            auto [err0, book0] = classBook->ctorT()(alloc::Heap);
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(book0.isEmpty());

            auto [err1, book1] = book0.clone<alloc::Heap>();

            EXPECT_TRUE(err1 == error::None);
            EXPECT_FALSE(book1.isEmpty());

            EXPECT_EQ(book0.getTypeId(), book1.getTypeId());

            EXPECT_TRUE(book::get_book_instance_count() == 2);
            EXPECT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 2);
        }
        EXPECT_TRUE(book::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(CopyConstructor, clone_default_instance_on_stack_source_on_stack)
    {
        {
            optional<Record> classBook = cxx::mirror().getRecord(cxx::type::Book::id);
            ASSERT_TRUE(classBook);

            auto [err0, book0] = classBook->ctorT()(alloc::Stack);
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(book0.isEmpty());

            auto [err1, book1] = book0.clone<alloc::Stack>();

            EXPECT_TRUE(err1 == error::None);
            ASSERT_FALSE(book1.isEmpty());

            EXPECT_TRUE(book::get_book_instance_count() == 2);
            EXPECT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
        }
        EXPECT_TRUE(book::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(CopyConstructor, clone_default_instance_on_heap_source_on_stack)
    {
        {
            optional<Record> classBook = cxx::mirror().getRecord(cxx::type::Book::id);
            ASSERT_TRUE(classBook);

            auto [err0, book0] = classBook->ctorT()(alloc::Stack);
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(book0.isEmpty());

            auto [err1, book1] = book0.clone<alloc::Heap>();

            EXPECT_TRUE(err1 == error::None);
            ASSERT_FALSE(book1.isEmpty());

            EXPECT_TRUE(book::get_book_instance_count() == 2);
            EXPECT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 1);
        }
        EXPECT_TRUE(book::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(CopyConstructor, clone_default_instance_on_stack_source_on_heap)
    {
        {
            optional<Record> classBook = cxx::mirror().getRecord(cxx::type::Book::id);
            ASSERT_TRUE(classBook);

            auto [err0, book0] = classBook->ctorT()(alloc::Heap);
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(book0.isEmpty());

            auto [err1, book1] = book0.clone<alloc::Stack>();

            EXPECT_TRUE(err1 == error::None);
            ASSERT_FALSE(book1.isEmpty());

            EXPECT_TRUE(book::get_book_instance_count() == 2);
            EXPECT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 1);
        }
        EXPECT_TRUE(book::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(CopyConstructor, clone_mutated_instance_on_heap_source_on_heap)
    {
        {
            optional<Record> classBook = cxx::mirror().getRecord(cxx::type::Book::id);
            ASSERT_TRUE(classBook);

            rtl::constructor<double, std::string> ctorT = classBook->ctorT<double, std::string>();

            auto [err0, book] = ctorT(alloc::Heap, book::PRICE, book::TITLE);
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(book.isEmpty());
            {
                optional<Method> oSetAuthor = classBook->getMethod(cxx::type::Book::fn::setAuthor::id);
                ASSERT_TRUE(oSetAuthor);

                auto setAuthor = oSetAuthor->targetT().argsT<std::string>().returnT();

                auto [err, ret] = setAuthor(book)(book::AUTHOR);
                EXPECT_TRUE(err == error::None);
                EXPECT_TRUE(ret.isEmpty());
            } {
                optional<Method> oSetDescription = classBook->getMethod(cxx::type::Book::fn::setDescription::id);
                ASSERT_TRUE(oSetDescription);

                auto setDescription = oSetDescription->targetT().argsT<std::string>().returnT();

                auto [err, ret] = setDescription(book)(book::DESCRIPTION);
                EXPECT_TRUE(err == error::None);
                EXPECT_TRUE(ret.isEmpty());
            }
            auto [err1, bookCopy] = book.clone<alloc::Heap>();
            EXPECT_TRUE(err1 == error::None);
            ASSERT_FALSE(bookCopy.isEmpty());

            const bool isPassed = book::test_copy_ctor_with_mutated_object(bookCopy);
            EXPECT_TRUE(isPassed);

            EXPECT_TRUE(book::get_book_instance_count() == 2);
            EXPECT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 2);
        }
        EXPECT_TRUE(book::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(CopyConstructor, clone_mutated_instance_on_stack_source_on_stack)
    {
        {
            optional<Record> classBook = cxx::mirror().getRecord(cxx::type::Book::id);
            ASSERT_TRUE(classBook);

            rtl::constructor<double, std::string> ctorT = classBook->ctorT<double, std::string>();
            
            auto [err0, book] = ctorT(alloc::Stack, book::PRICE, book::TITLE);
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(book.isEmpty());
            {
                optional<Method> oSetAuthor = classBook->getMethod(cxx::type::Book::fn::setAuthor::id);
                ASSERT_TRUE(oSetAuthor);

                auto setAuthor = oSetAuthor->targetT().argsT<std::string>().returnT();

                auto [err, ret] = setAuthor(book)(book::AUTHOR);
                EXPECT_TRUE(err == error::None);
                EXPECT_TRUE(ret.isEmpty());
            } {
                optional<Method> oSetDescription = classBook->getMethod(cxx::type::Book::fn::setDescription::id);
                ASSERT_TRUE(oSetDescription);

                auto setDescription = oSetDescription->targetT().argsT<std::string>().returnT();

                auto [err, ret] = setDescription(book)(book::DESCRIPTION);
                EXPECT_TRUE(err == error::None);
                EXPECT_TRUE(ret.isEmpty());
            }
            auto [err1, bookCopy] = book.clone<alloc::Stack>();
            EXPECT_TRUE(err1 == error::None);
            ASSERT_FALSE(bookCopy.isEmpty());

            const bool isPassed = book::test_copy_ctor_with_mutated_object(bookCopy);
            EXPECT_TRUE(isPassed);

            EXPECT_TRUE(book::get_book_instance_count() == 2);
            EXPECT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
        }
        EXPECT_TRUE(book::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(CopyConstructor, clone_mutated_instance_on_heap_source_on_stack)
    {
        {
            optional<Record> classBook = cxx::mirror().getRecord(cxx::type::Book::id);
            ASSERT_TRUE(classBook);
            
            rtl::constructor<double, std::string> ctorT = classBook->ctorT<double, std::string>();

            auto [err0, book] = ctorT(alloc::Stack, book::PRICE, book::TITLE);
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(book.isEmpty());
            {
                optional<Method> oSetAuthor = classBook->getMethod(cxx::type::Book::fn::setAuthor::id);
                ASSERT_TRUE(oSetAuthor);

                auto setAuthor = oSetAuthor->targetT().argsT<std::string>().returnT();

                auto [err, ret] = setAuthor(book)(book::AUTHOR);
                EXPECT_TRUE(err == error::None);
                EXPECT_TRUE(ret.isEmpty());
            } {
                optional<Method> oSetDescription = classBook->getMethod(cxx::type::Book::fn::setDescription::id);
                ASSERT_TRUE(oSetDescription);

                auto setDescription = oSetDescription->targetT().argsT<std::string>().returnT();

                auto [err, ret] = setDescription(book)(book::DESCRIPTION);
                EXPECT_TRUE(err == error::None);
                EXPECT_TRUE(ret.isEmpty());
            }
            auto [err1, bookCopy] = book.clone<alloc::Heap>();
            EXPECT_TRUE(err1 == error::None);
            ASSERT_FALSE(bookCopy.isEmpty());
            
            const bool isPassed = book::test_copy_ctor_with_mutated_object(bookCopy);
            EXPECT_TRUE(isPassed);
            
            EXPECT_TRUE(book::get_book_instance_count() == 2);
            EXPECT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 1);
        }
        EXPECT_TRUE(book::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }
    
    
    TEST(CopyConstructor, clone_mutated_instance_on_stack_source_on_heap)
    {
        {   
            optional<Record> classBook = cxx::mirror().getRecord(cxx::type::Book::id);
            ASSERT_TRUE(classBook);
            
            rtl::constructor<double, std::string> ctorT = classBook->ctorT<double, std::string>();

            auto [err0, book] = ctorT(alloc::Heap, book::PRICE, book::TITLE);
            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(book.isEmpty());
            {
                optional<Method> oSetAuthor = classBook->getMethod(cxx::type::Book::fn::setAuthor::id);
                ASSERT_TRUE(oSetAuthor);

                auto setAuthor = oSetAuthor->targetT().argsT<std::string>().returnT();

                auto [err, ret] = setAuthor(book)(book::AUTHOR);
                EXPECT_TRUE(err == error::None);
                EXPECT_TRUE(ret.isEmpty());
            } {
                optional<Method> oSetDescription = classBook->getMethod(cxx::type::Book::fn::setDescription::id);
                ASSERT_TRUE(oSetDescription);

                auto setDescription = oSetDescription->targetT().argsT<std::string>().returnT();

                auto [err, ret] = setDescription(book)(book::DESCRIPTION);
                EXPECT_TRUE(err == error::None);
                EXPECT_TRUE(ret.isEmpty());
            }
            auto [err1, bookCopy] = book.clone<alloc::Stack>();
            EXPECT_TRUE(err1 == error::None);
            ASSERT_FALSE(bookCopy.isEmpty());
            
            const bool isPassed = book::test_copy_ctor_with_mutated_object(bookCopy);
            EXPECT_TRUE(isPassed);
            
            EXPECT_TRUE(book::get_book_instance_count() == 2);
            EXPECT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 1);
        }
        EXPECT_TRUE(book::assert_zero_instance_count());
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(CopyConstructor, sharing_semantics__clone_on_stack_src_on_stack_mutate_after)
    {
        {
            // Retrieve the reflected Record for the 'Calender' struct
            optional<Record> typeCalender = cxx::mirror().getRecord(calender::struct_);
            ASSERT_TRUE(typeCalender);

            // Create a stack-allocated object via reflection
            auto [err0, calender0] = typeCalender->ctorT()(alloc::Stack);

            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(calender0.isEmpty());
            EXPECT_FALSE(calender0.isOnHeap());

            EXPECT_TRUE(calender::get_instance_count() == 1);
            // 'Calender' has 2 'Event' instances, shared_ptr<Event> and a std::unique_ptr<Event>.
            EXPECT_TRUE(event::get_instance_count() == 2);
            // 'Event' has a unique_ptr<Date> and two 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 2);

            // The underlying object is expected to be copied via copy constructor.
            auto [err1, calender1] = calender0.clone<rtl::alloc::Stack>();
            
            EXPECT_TRUE(err1 == error::None);
            // Verify the object created is valid and on stack.
            ASSERT_FALSE(calender1.isEmpty());
            EXPECT_FALSE(calender1.isOnHeap());
            EXPECT_TRUE(calender0.getTypeId() == calender1.getTypeId());

            // Calender got cloned now.
            EXPECT_TRUE(calender::get_instance_count() == 2);
            // 'Calender' has shared_ptr<Event> and a std::unique_ptr<Event>, so one got shared and one newly created.
            EXPECT_TRUE(event::get_instance_count() == 3);
            // 'Event' has a unique_ptr<Date> and 3 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 3);

            optional<Method> oGetTheDate = typeCalender->getMethod(calender::str_getTheDate);
            ASSERT_TRUE(oGetTheDate);

            rtl::method<rtl::RObject, rtl::Return()> getTheDate = oGetTheDate->targetT().argsT().returnT();
            EXPECT_TRUE(getTheDate);
            {                
                auto [err_0, date0] = getTheDate(calender0)();

                EXPECT_TRUE(err_0 == error::None);
                EXPECT_FALSE(date0.isOnHeap());
                ASSERT_FALSE(date0.isEmpty());

                auto [err_1, date1] = getTheDate(calender1)();
                
                EXPECT_TRUE(err_1 == error::None);
                EXPECT_FALSE(date1.isOnHeap());
                ASSERT_FALSE(date1.isEmpty());

                // both objects must be equal (shared via shared_ptr inside 'Calender')
                EXPECT_TRUE(date::test_if_obejcts_are_equal(date0, date1));

                optional<Record> structDate = cxx::mirror().getRecord(date::struct_);
                ASSERT_TRUE(structDate);

                optional<Method> oUpdateDate = structDate->getMethod(date::str_updateDate);
                ASSERT_TRUE(oUpdateDate);
                
                method<RObject, Return(string)> updateDate = oUpdateDate->targetT().argsT<string>().returnT();
                EXPECT_TRUE(updateDate);
                {
                    auto [err, ret] = updateDate(date0)(date::DATE_STR1);
                    ASSERT_TRUE(err == error::None && ret.isEmpty());
                    // After mutation, they should be still equal.
                    EXPECT_TRUE(date::test_if_obejcts_are_equal(date0, date1));
                }
            }
        }
        // After scope exit, stack instances are cleaned up automatically
        EXPECT_TRUE(calender::get_instance_count() == 0);
        EXPECT_TRUE(event::get_instance_count() == 0);
        EXPECT_TRUE(date::get_instance_count() == 0);
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(CopyConstructor, sharing_semantics__clone_on_heap_src_on_stack_mutate_after)
    {
        {
            // Retrieve the reflected Record for the 'Calender' struct
            optional<Record> typeCalender = cxx::mirror().getRecord(calender::struct_);
            ASSERT_TRUE(typeCalender);

            // Create a stack-allocated object via reflection
            auto [err0, calender0] = typeCalender->ctorT()(alloc::Stack);

            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(calender0.isEmpty());
            EXPECT_FALSE(calender0.isOnHeap());

            EXPECT_TRUE(calender::get_instance_count() == 1);
            // 'Calender' has 2 'Event' instances, shared_ptr<Event> and a std::unique_ptr<Event>.
            EXPECT_TRUE(event::get_instance_count() == 2);
            // 'Event' has a unique_ptr<Date> and two 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 2);

            // The underlying object is expected to be copied via copy constructor.
            auto [err1, calender1] = calender0.clone<rtl::alloc::Heap>();

            EXPECT_TRUE(err1 == error::None);
            // Verify the object created is valid and on stack.
            ASSERT_FALSE(calender1.isEmpty());
            EXPECT_TRUE(calender1.isOnHeap());
            EXPECT_TRUE(calender0.getTypeId() == calender1.getTypeId());

            // Calender got cloned now.
            EXPECT_TRUE(calender::get_instance_count() == 2);
            // 'Calender' has shared_ptr<Event> and a std::unique_ptr<Event>, so one got shared and one newly created.
            EXPECT_TRUE(event::get_instance_count() == 3);
            // 'Event' has a unique_ptr<Date> and 3 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 3);

            optional<Method> oGetTheDate = typeCalender->getMethod(calender::str_getTheDate);
            ASSERT_TRUE(oGetTheDate);

            rtl::method<rtl::RObject, rtl::Return()> getTheDate = oGetTheDate->targetT().argsT().returnT();
            EXPECT_TRUE(getTheDate);
            {
                auto [err_0, date0] = getTheDate(calender0)();

                EXPECT_TRUE(err_0 == error::None);
                EXPECT_FALSE(date0.isOnHeap());
                ASSERT_FALSE(date0.isEmpty());

                auto [err_1, date1] = getTheDate(calender1)();

                EXPECT_TRUE(err_1 == error::None);
                EXPECT_FALSE(date1.isOnHeap());
                ASSERT_FALSE(date1.isEmpty());

                // both objects must be equal (shared via shared_ptr inside 'Calender')
                EXPECT_TRUE(date::test_if_obejcts_are_equal(date0, date1));

                optional<Record> structDate = cxx::mirror().getRecord(date::struct_);
                ASSERT_TRUE(structDate);

                optional<Method> oUpdateDate = structDate->getMethod(date::str_updateDate);
                ASSERT_TRUE(oUpdateDate);

                method<RObject, Return(string)> updateDate = oUpdateDate->targetT().argsT<string>().returnT();
                EXPECT_TRUE(updateDate);
                {
                    auto [err, ret] = updateDate(date0)(date::DATE_STR1);
                    ASSERT_TRUE(err == error::None && ret.isEmpty());
                    // After mutation, they should be still equal.
                    EXPECT_TRUE(date::test_if_obejcts_are_equal(date0, date1));
                }
            }
        }
        // After scope exit, stack instances are cleaned up automatically
        EXPECT_TRUE(calender::get_instance_count() == 0);
        EXPECT_TRUE(event::get_instance_count() == 0);
        EXPECT_TRUE(date::get_instance_count() == 0);
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(CopyConstructor, sharing_semantics__clone_on_stack_src_on_heap_mutate_after)
    {
        {
            // Retrieve the reflected Record for the 'Calender' struct
            optional<Record> typeCalender = cxx::mirror().getRecord(calender::struct_);
            ASSERT_TRUE(typeCalender);

            // Create a stack-allocated object via reflection
            auto [err0, calender0] = typeCalender->ctorT()(alloc::Heap);

            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(calender0.isEmpty());
            EXPECT_TRUE(calender0.isOnHeap());

            EXPECT_TRUE(calender::get_instance_count() == 1);
            // 'Calender' has 2 'Event' instances, shared_ptr<Event> and a std::unique_ptr<Event>.
            EXPECT_TRUE(event::get_instance_count() == 2);
            // 'Event' has a unique_ptr<Date> and two 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 2);

            // The underlying object is expected to be copied via copy constructor.
            auto [err1, calender1] = calender0.clone<rtl::alloc::Stack>();

            EXPECT_TRUE(err1 == error::None);
            // Verify the object created is valid and on stack.
            ASSERT_FALSE(calender1.isEmpty());
            EXPECT_FALSE(calender1.isOnHeap());
            EXPECT_TRUE(calender0.getTypeId() == calender1.getTypeId());

            // Calender got cloned now.
            EXPECT_TRUE(calender::get_instance_count() == 2);
            // 'Calender' has shared_ptr<Event> and a std::unique_ptr<Event>, so one got shared and one newly created.
            EXPECT_TRUE(event::get_instance_count() == 3);
            // 'Event' has a unique_ptr<Date> and 3 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 3);

            optional<Method> oGetTheDate = typeCalender->getMethod(calender::str_getTheDate);
            ASSERT_TRUE(oGetTheDate);

            rtl::method<rtl::RObject, rtl::Return()> getTheDate = oGetTheDate->targetT().argsT().returnT();
            EXPECT_TRUE(getTheDate);
            {
                auto [err_0, date0] = getTheDate(calender0)();

                EXPECT_TRUE(err_0 == error::None);
                EXPECT_FALSE(date0.isOnHeap());
                ASSERT_FALSE(date0.isEmpty());

                auto [err_1, date1] = getTheDate(calender1)();

                EXPECT_TRUE(err_1 == error::None);
                EXPECT_FALSE(date1.isOnHeap());
                ASSERT_FALSE(date1.isEmpty());

                // both objects must be equal (shared via shared_ptr inside 'Calender')
                EXPECT_TRUE(date::test_if_obejcts_are_equal(date0, date1));

                optional<Record> structDate = cxx::mirror().getRecord(date::struct_);
                ASSERT_TRUE(structDate);

                optional<Method> oUpdateDate = structDate->getMethod(date::str_updateDate);
                ASSERT_TRUE(oUpdateDate);

                method<RObject, Return(string)> updateDate = oUpdateDate->targetT().argsT<string>().returnT();
                EXPECT_TRUE(updateDate);
                {
                    auto [err, ret] = updateDate(date0)(date::DATE_STR1);
                    ASSERT_TRUE(err == error::None && ret.isEmpty());
                    // After mutation, they should be still equal.
                    EXPECT_TRUE(date::test_if_obejcts_are_equal(date0, date1));
                }
            }
        }
        // After scope exit, stack instances are cleaned up automatically
        EXPECT_TRUE(calender::get_instance_count() == 0);
        EXPECT_TRUE(event::get_instance_count() == 0);
        EXPECT_TRUE(date::get_instance_count() == 0);
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }


    TEST(CopyConstructor, sharing_semantics__clone_on_heap_src_on_heap_mutate_after)
    {
        {
            // Retrieve the reflected Record for the 'Calender' struct
            optional<Record> typeCalender = cxx::mirror().getRecord(calender::struct_);
            ASSERT_TRUE(typeCalender);

            // Create a stack-allocated object via reflection
            auto [err0, calender0] = typeCalender->ctorT()(alloc::Heap);

            EXPECT_TRUE(err0 == error::None);
            ASSERT_FALSE(calender0.isEmpty());
            EXPECT_TRUE(calender0.isOnHeap());

            EXPECT_TRUE(calender::get_instance_count() == 1);
            // 'Calender' has 2 'Event' instances, shared_ptr<Event> and a std::unique_ptr<Event>.
            EXPECT_TRUE(event::get_instance_count() == 2);
            // 'Event' has a unique_ptr<Date> and two 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 2);

            // The underlying object is expected to be copied via copy constructor.
            auto [err1, calender1] = calender0.clone<rtl::alloc::Heap>();

            EXPECT_TRUE(err1 == error::None);
            // Verify the object created is valid and on stack.
            ASSERT_FALSE(calender1.isEmpty());
            EXPECT_TRUE(calender1.isOnHeap());
            EXPECT_TRUE(calender0.getTypeId() == calender1.getTypeId());

            // Calender got cloned now.
            EXPECT_TRUE(calender::get_instance_count() == 2);
            // 'Calender' has shared_ptr<Event> and a std::unique_ptr<Event>, so one got shared and one newly created.
            EXPECT_TRUE(event::get_instance_count() == 3);
            // 'Event' has a unique_ptr<Date> and 3 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 3);

            optional<Method> oGetSavedDate = typeCalender->getMethod(calender::str_getSavedDate);
            ASSERT_TRUE(oGetSavedDate);

            rtl::method<rtl::RObject, rtl::Return()> getSavedDate = oGetSavedDate->targetT().argsT().returnT();
            EXPECT_TRUE(getSavedDate);
            {
                auto [err_0, date0] = getSavedDate(calender0)();

                EXPECT_TRUE(err_0 == error::None);
                EXPECT_FALSE(date0.isOnHeap());
                ASSERT_FALSE(date0.isEmpty());

                auto [err_1, date1] = getSavedDate(calender1)();

                EXPECT_TRUE(err_1 == error::None);
                EXPECT_FALSE(date1.isOnHeap());
                ASSERT_FALSE(date1.isEmpty());

                // both objects must be equal, created via default-constructor, different instances, not shared.
                EXPECT_TRUE(date::test_if_obejcts_are_equal(date0, date1));

                optional<Record> structDate = cxx::mirror().getRecord(date::struct_);
                ASSERT_TRUE(structDate);
                
                optional<Method> oUpdateDate = structDate->getMethod(date::str_updateDate);
                ASSERT_TRUE(oUpdateDate);

                method<RObject, Return(string)> updateDate = oUpdateDate->targetT().argsT<string>().returnT();
                EXPECT_TRUE(updateDate);
                {
                    auto [err, ret] = updateDate(date0)(date::DATE_STR1);
                    ASSERT_TRUE(err == error::None && ret.isEmpty());
                    // After mutation, they should be not be equal, since both are unique instances.
                    EXPECT_FALSE(date::test_if_obejcts_are_equal(date0, date1));
                }
            }
        }
        // After scope exit, stack instances are cleaned up automatically
        EXPECT_TRUE(calender::get_instance_count() == 0);
        EXPECT_TRUE(event::get_instance_count() == 0);
        EXPECT_TRUE(date::get_instance_count() == 0);
        ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
    }
}
