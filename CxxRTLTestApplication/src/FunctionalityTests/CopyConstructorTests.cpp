#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsBook.h"
#include "TestUtilsDate.h"

using namespace std;
using namespace rtl;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests
{
    TEST(CopyConstructor, clone_instance_on_heap_source_on_heap)
    {
        {
            optional<Record> classBook = MyReflection::instance().getRecord(book::class_);
            ASSERT_TRUE(classBook);

            auto [err0, book0] = classBook->create<alloc::Heap>();
            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(book0.isEmpty());

            auto [err1, book1] = book0.clone<alloc::Heap>();

            ASSERT_TRUE(err1 == error::None);
            ASSERT_TRUE(!book1.isEmpty());

            EXPECT_TRUE(book::get_book_instance_count() == 2);
            EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 2);
        }
        EXPECT_TRUE(book::assert_zero_instance_count());
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(CopyConstructor, clone_instance_on_stack_source_on_stack)
    {
        {
            optional<Record> classBook = MyReflection::instance().getRecord(book::class_);
            ASSERT_TRUE(classBook);

            auto [err0, book0] = classBook->create<alloc::Stack>();
            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(book0.isEmpty());

            auto [err1, book1] = book0.clone<alloc::Stack>();

            ASSERT_TRUE(err1 == error::None);
            ASSERT_TRUE(!book1.isEmpty());

            EXPECT_TRUE(book::get_book_instance_count() == 2);
            EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
        }
        EXPECT_TRUE(book::assert_zero_instance_count());
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }



    TEST(CopyConstructor, clone_instance_on_heap_source_on_stack)
    {
        {
            optional<Record> classBook = MyReflection::instance().getRecord(book::class_);
            ASSERT_TRUE(classBook);

            auto [err0, book0] = classBook->create<alloc::Stack>();
            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(book0.isEmpty());

            auto [err1, book1] = book0.clone<alloc::Heap>();

            ASSERT_TRUE(err1 == error::None);
            ASSERT_TRUE(!book1.isEmpty());

            EXPECT_TRUE(book::get_book_instance_count() == 2);
            EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 1);
        }
        EXPECT_TRUE(book::assert_zero_instance_count());
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }



    TEST(CopyConstructor, clone_instance_on_stack_source_on_heap)
    {
        {
            optional<Record> classBook = MyReflection::instance().getRecord(book::class_);
            ASSERT_TRUE(classBook);

            auto [err0, book0] = classBook->create<alloc::Heap>();
            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(book0.isEmpty());

            auto [err1, book1] = book0.clone<alloc::Stack>();

            ASSERT_TRUE(err1 == error::None);
            ASSERT_TRUE(!book1.isEmpty());

            EXPECT_TRUE(book::get_book_instance_count() == 2);
            EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 1);
        }
        EXPECT_TRUE(book::assert_zero_instance_count());
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(CopyConstructor, clone_instance_on_heap_source_on_heap_mutated)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> classBook = cxxMirror.getRecord(book::class_);
            ASSERT_TRUE(classBook);

            optional<Method> setAuthor = classBook->getMethod(book::str_setAuthor);
            ASSERT_TRUE(setAuthor);

            optional<Method> setDecription = classBook->getMethod(book::str_setDescription);
            ASSERT_TRUE(setDecription);

            double price = book::PRICE;
            string title = book::TITLE;
            string author = book::AUTHOR;
            string description = book::DESCRIPTION;

            auto [err0, book] = classBook->create<alloc::Heap>(price, title);
            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(book.isEmpty());

            auto [err1, ret1] = (*setAuthor)(book)(author);
            ASSERT_TRUE(err1 == error::None);

            auto [err2, ret2] = (*setDecription)(book)(description);
            ASSERT_TRUE(err1 == error::None);

            auto [err3, bookCopy] = book.clone<alloc::Heap>();
            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(bookCopy.isEmpty());

            const bool isPassed = book::test_copy_ctor_with_mutated_object(bookCopy.get(), bookCopy.isOnHeap());
            EXPECT_TRUE(isPassed);

            EXPECT_TRUE(book::get_book_instance_count() == 2);
            EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 2);
        }
        EXPECT_TRUE(book::assert_zero_instance_count());
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(CopyConstructor, clone_instance_on_stack_source_on_stack_mutated)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> classBook = cxxMirror.getRecord(book::class_);
            ASSERT_TRUE(classBook);

            optional<Method> setAuthor = classBook->getMethod(book::str_setAuthor);
            ASSERT_TRUE(setAuthor);

            optional<Method> setDecription = classBook->getMethod(book::str_setDescription);
            ASSERT_TRUE(setDecription);

            double price = book::PRICE;
            string title = book::TITLE;
            string author = book::AUTHOR;
            string description = book::DESCRIPTION;

            auto [err0, book] = classBook->create<alloc::Stack>(price, title);
            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(book.isEmpty());

            auto [err1, ret1] = (*setAuthor)(book)(author);
            ASSERT_TRUE(err1 == error::None);

            auto [err2, ret2] = (*setDecription)(book)(description);
            ASSERT_TRUE(err1 == error::None);

            auto [err3, bookCopy] = book.clone<alloc::Stack>();
            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(bookCopy.isEmpty());

            const bool isPassed = book::test_copy_ctor_with_mutated_object(bookCopy.get(), bookCopy.isOnHeap());
            EXPECT_TRUE(isPassed);

            EXPECT_TRUE(book::get_book_instance_count() == 2);
            EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
        }
        EXPECT_TRUE(book::assert_zero_instance_count());
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(CopyConstructor, clone_instance_on_heap_source_on_stack_mutated)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            optional<Record> classBook = cxxMirror.getRecord(book::class_);
            ASSERT_TRUE(classBook);
            
            optional<Method> setAuthor = classBook->getMethod(book::str_setAuthor);
            ASSERT_TRUE(setAuthor);
            
            optional<Method> setDecription = classBook->getMethod(book::str_setDescription);
            ASSERT_TRUE(setDecription);
            
            double price = book::PRICE;
            string title = book::TITLE;
            string author = book::AUTHOR;
            string description = book::DESCRIPTION;
            
            auto [err0, book] = classBook->create<alloc::Stack>(price, title);
            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(book.isEmpty());
            
            auto [err1, ret1] = (*setAuthor)(book)(author);
            ASSERT_TRUE(err1 == error::None);
            
            auto [err2, ret2] = (*setDecription)(book)(description);
            ASSERT_TRUE(err1 == error::None);
            
            auto [err3, bookCopy] = book.clone<alloc::Heap>();
            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(bookCopy.isEmpty());
            
            const bool isPassed = book::test_copy_ctor_with_mutated_object(bookCopy.get(), bookCopy.isOnHeap());
            EXPECT_TRUE(isPassed);
            
            EXPECT_TRUE(book::get_book_instance_count() == 2);
            EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 1);
        }
        EXPECT_TRUE(book::assert_zero_instance_count());
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }
    
    
    TEST(CopyConstructor, clone_instance_on_stack_source_on_heap_mutated)
    {
        {
            CxxMirror& cxxMirror = MyReflection::instance();
            
            optional<Record> classBook = cxxMirror.getRecord(book::class_);
            ASSERT_TRUE(classBook);
            
            optional<Method> setAuthor = classBook->getMethod(book::str_setAuthor);
            ASSERT_TRUE(setAuthor);
            
            optional<Method> setDecription = classBook->getMethod(book::str_setDescription);
            ASSERT_TRUE(setDecription);
            
            double price = book::PRICE;
            string title = book::TITLE;
            string author = book::AUTHOR;
            string description = book::DESCRIPTION;
            
            auto [err0, book] = classBook->create<alloc::Heap>(price, title);
            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(book.isEmpty());
            
            auto [err1, ret1] = (*setAuthor)(book)(author);
            ASSERT_TRUE(err1 == error::None);
            
            auto [err2, ret2] = (*setDecription)(book)(description);
            ASSERT_TRUE(err1 == error::None);
            
            auto [err3, bookCopy] = book.clone<alloc::Stack>();
            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(bookCopy.isEmpty());
            
            const bool isPassed = book::test_copy_ctor_with_mutated_object(bookCopy.get(), bookCopy.isOnHeap());
            EXPECT_TRUE(isPassed);
            
            EXPECT_TRUE(book::get_book_instance_count() == 2);
            EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 1);
        }
        EXPECT_TRUE(book::assert_zero_instance_count());
        EXPECT_TRUE(rtl::getReflectedHeapInstanceCount() == 0);
    }


    TEST(CopyConstructor, clone_instance_on_stack_source_on_stack_mutate_after_clone)
    {
        // Ensure there are no lingering reflected instances before the test begins
        EXPECT_TRUE(date::get_instance_count() == 0);
        EXPECT_TRUE(event::get_instance_count() == 0);
        EXPECT_TRUE(calender::get_instance_count() == 0);
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            // Retrieve the reflected Record for the 'Calender' struct
            optional<Record> typeCalender = cxxMirror.getRecord(calender::ns, calender::struct_);
            ASSERT_TRUE(typeCalender);

            // Create a stack-allocated object via reflection
            auto [err0, calender0] = typeCalender->create<alloc::Stack>();

            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(calender0.isEmpty());
            ASSERT_FALSE(calender0.isOnHeap());

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
            ASSERT_FALSE(calender1.isOnHeap());
            ASSERT_TRUE(calender0.getTypeId() == calender1.getTypeId());

            // Calender got cloned now.
            EXPECT_TRUE(calender::get_instance_count() == 2);
            // 'Calender' has shared_ptr<Event> and a std::unique_ptr<Event>, so one got shared and one newly created.
            EXPECT_TRUE(event::get_instance_count() == 3);
            // 'Event' has a unique_ptr<Date> and 3 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 3);

            optional<Method> getTheDate = typeCalender->getMethod(calender::str_getTheDate);
            ASSERT_TRUE(getTheDate);
            {
                auto [err_0, date0] = getTheDate->bind(calender0).call();
                ASSERT_TRUE(err_0 == error::None);
                ASSERT_FALSE(date0.isOnHeap());
                ASSERT_FALSE(date0.isEmpty());

                auto [err_1, date1] = getTheDate->bind(calender1).call();
                ASSERT_TRUE(err_1 == error::None);
                ASSERT_FALSE(date1.isOnHeap());
                ASSERT_FALSE(date1.isEmpty());

                // both objects must be equal (shared via shared_ptr inside 'Calender')
                EXPECT_TRUE(date::test_if_obejcts_are_equal(date0.get(), date1.get(), true));

                optional<Record> structDate = cxxMirror.getRecord(date::ns, date::struct_);
                ASSERT_TRUE(structDate);
                optional<Method> updateDate = structDate->getMethod(date::str_updateDate);
                ASSERT_TRUE(updateDate);
                string dateStr = date::DATE_STR1;
                {
                    auto [err, ret] = updateDate->bind(date0).call(dateStr);
                    // Invocation of const-member-function requires const-target, but 'date0' is non-const.
                    EXPECT_TRUE(err == error::ImplicitCallToNonConstOnConstTarget && ret.isEmpty());
                } {
                    // Explicitly bind a const member function to 'date0' and invoke it treating 'date0' as const.
                    auto [err, ret] = updateDate->bind<methodQ::NonConst>(date0).call(dateStr);
                    EXPECT_TRUE(err == error::None && ret.isEmpty());
                    // After mutation, they should be still equal.
                    EXPECT_TRUE(date::test_if_obejcts_are_equal(date0.get(), date1.get(), true));
                }
            }
        }
        // After scope exit, stack instances are cleaned up automatically
        EXPECT_TRUE(calender::get_instance_count() == 0);
        EXPECT_TRUE(event::get_instance_count() == 0);
        EXPECT_TRUE(date::get_instance_count() == 0);
    }


    TEST(CopyConstructor, clone_instance_on_heap_source_on_stack_mutate_after_clone)
    {
        // Ensure there are no lingering reflected instances before the test begins
        EXPECT_TRUE(date::get_instance_count() == 0);
        EXPECT_TRUE(event::get_instance_count() == 0);
        EXPECT_TRUE(calender::get_instance_count() == 0);
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            // Retrieve the reflected Record for the 'Calender' struct
            optional<Record> typeCalender = cxxMirror.getRecord(calender::ns, calender::struct_);
            ASSERT_TRUE(typeCalender);

            // Create a stack-allocated object via reflection
            auto [err0, calender0] = typeCalender->create<alloc::Stack>();

            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(calender0.isEmpty());
            ASSERT_FALSE(calender0.isOnHeap());

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
            ASSERT_TRUE(calender1.isOnHeap());
            ASSERT_TRUE(calender0.getTypeId() == calender1.getTypeId());

            // Calender got cloned now.
            EXPECT_TRUE(calender::get_instance_count() == 2);
            // 'Calender' has shared_ptr<Event> and a std::unique_ptr<Event>, so one got shared and one newly created.
            EXPECT_TRUE(event::get_instance_count() == 3);
            // 'Event' has a unique_ptr<Date> and 3 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 3);

            optional<Method> getTheDate = typeCalender->getMethod(calender::str_getTheDate);
            ASSERT_TRUE(getTheDate);
            {
                auto [err_0, date0] = getTheDate->bind(calender0).call();
                ASSERT_TRUE(err_0 == error::None);
                ASSERT_FALSE(date0.isOnHeap());
                ASSERT_FALSE(date0.isEmpty());

                auto [err_1, date1] = getTheDate->bind(calender1).call();
                ASSERT_TRUE(err_1 == error::None);
                ASSERT_FALSE(date1.isOnHeap());
                ASSERT_FALSE(date1.isEmpty());

                // both objects must be equal (shared via shared_ptr inside 'Calender')
                EXPECT_TRUE(date::test_if_obejcts_are_equal(date0.get(), date1.get(), true));

                optional<Record> structDate = cxxMirror.getRecord(date::ns, date::struct_);
                ASSERT_TRUE(structDate);
                // 'updateDate' is const-member-function in 'Date' class.
                optional<Method> updateDate = structDate->getMethod(date::str_updateDate);
                ASSERT_TRUE(updateDate);
                string dateStr = date::DATE_STR1;
                {
                    auto [err, ret] = updateDate->bind(date0).call(dateStr);
                    // Invocation of const-member-function requires const-target, but 'date0' is non-const.
                    EXPECT_TRUE(err == error::ImplicitCallToNonConstOnConstTarget && ret.isEmpty());
                } {
                    // Explicitly bind a const member function to 'date0' and invoke it treating 'date0' as const.
                    auto [err, ret] = updateDate->bind<methodQ::NonConst>(date0).call(dateStr);
                    EXPECT_TRUE(err == error::None && ret.isEmpty());
                    // After mutation, they should be still equal.
                    EXPECT_TRUE(date::test_if_obejcts_are_equal(date0.get(), date1.get(), true));
                }
            }
        }
        // After scope exit, stack instances are cleaned up automatically
        EXPECT_TRUE(calender::get_instance_count() == 0);
        EXPECT_TRUE(event::get_instance_count() == 0);
        EXPECT_TRUE(date::get_instance_count() == 0);
    }


    TEST(CopyConstructor, clone_instance_on_stack_source_on_heap_mutate_after_clone)
    {
        // Ensure there are no lingering reflected instances before the test begins
        EXPECT_TRUE(date::get_instance_count() == 0);
        EXPECT_TRUE(event::get_instance_count() == 0);
        EXPECT_TRUE(calender::get_instance_count() == 0);
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            // Retrieve the reflected Record for the 'Calender' struct
            optional<Record> typeCalender = cxxMirror.getRecord(calender::ns, calender::struct_);
            ASSERT_TRUE(typeCalender);

            // Create a stack-allocated object via reflection
            auto [err0, calender0] = typeCalender->create<alloc::Heap>();

            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(calender0.isEmpty());
            ASSERT_TRUE(calender0.isOnHeap());

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
            ASSERT_FALSE(calender1.isOnHeap());
            ASSERT_TRUE(calender0.getTypeId() == calender1.getTypeId());

            // Calender got cloned now.
            EXPECT_TRUE(calender::get_instance_count() == 2);
            // 'Calender' has shared_ptr<Event> and a std::unique_ptr<Event>, so one got shared and one newly created.
            EXPECT_TRUE(event::get_instance_count() == 3);
            // 'Event' has a unique_ptr<Date> and 3 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 3);

            optional<Method> getTheDate = typeCalender->getMethod(calender::str_getTheDate);
            ASSERT_TRUE(getTheDate);
            {
                auto [err_0, date0] = getTheDate->bind(calender0).call();
                ASSERT_TRUE(err_0 == error::None);
                ASSERT_FALSE(date0.isOnHeap());
                ASSERT_FALSE(date0.isEmpty());

                auto [err_1, date1] = getTheDate->bind(calender1).call();
                ASSERT_TRUE(err_1 == error::None);
                ASSERT_FALSE(date1.isOnHeap());
                ASSERT_FALSE(date1.isEmpty());

                // both objects must be equal (shared via shared_ptr inside 'Calender')
                EXPECT_TRUE(date::test_if_obejcts_are_equal(date0.get(), date1.get(), true));

                optional<Record> structDate = cxxMirror.getRecord(date::ns, date::struct_);
                ASSERT_TRUE(structDate);
                optional<Method> updateDate = structDate->getMethod(date::str_updateDate);
                ASSERT_TRUE(updateDate);
                string dateStr = date::DATE_STR1;
                {
                    auto [err, ret] = updateDate->bind(date0).call(dateStr);
                    // Invocation of const-member-function requires const-target, but 'date0' is non-const.
                    EXPECT_TRUE(err == error::ImplicitCallToNonConstOnConstTarget && ret.isEmpty());
                } {
                    // Explicitly bind a const member function to 'date0' and invoke it treating 'date0' as const.
                    auto [err, ret] = updateDate->bind<methodQ::NonConst>(date0).call(dateStr);
                    EXPECT_TRUE(err == error::None && ret.isEmpty());
                    // After mutation, they should be still equal.
                    EXPECT_TRUE(date::test_if_obejcts_are_equal(date0.get(), date1.get(), true));
                }
            }
        }
        // After scope exit, stack instances are cleaned up automatically
        EXPECT_TRUE(calender::get_instance_count() == 0);
        EXPECT_TRUE(event::get_instance_count() == 0);
        EXPECT_TRUE(date::get_instance_count() == 0);
    }


    TEST(CopyConstructor, clone_instance_on_heap_source_on_heap_mutate_after_clone)
    {
        // Ensure there are no lingering reflected instances before the test begins
        EXPECT_TRUE(date::get_instance_count() == 0);
        EXPECT_TRUE(event::get_instance_count() == 0);
        EXPECT_TRUE(calender::get_instance_count() == 0);
        {
            CxxMirror& cxxMirror = MyReflection::instance();

            // Retrieve the reflected Record for the 'Calender' struct
            optional<Record> typeCalender = cxxMirror.getRecord(calender::ns, calender::struct_);
            ASSERT_TRUE(typeCalender);

            // Create a stack-allocated object via reflection
            auto [err0, calender0] = typeCalender->create<alloc::Heap>();

            ASSERT_TRUE(err0 == error::None);
            ASSERT_FALSE(calender0.isEmpty());
            ASSERT_TRUE(calender0.isOnHeap());

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
            ASSERT_TRUE(calender1.isOnHeap());
            ASSERT_TRUE(calender0.getTypeId() == calender1.getTypeId());

            // Calender got cloned now.
            EXPECT_TRUE(calender::get_instance_count() == 2);
            // 'Calender' has shared_ptr<Event> and a std::unique_ptr<Event>, so one got shared and one newly created.
            EXPECT_TRUE(event::get_instance_count() == 3);
            // 'Event' has a unique_ptr<Date> and 3 'Event' instances exists, So-
            EXPECT_TRUE(date::get_instance_count() == 3);

            optional<Method> getSavedDate = typeCalender->getMethod(calender::str_getSavedDate);
            ASSERT_TRUE(getSavedDate);
            {
                auto [err_0, date0] = getSavedDate->bind(calender0).call();
                ASSERT_TRUE(err_0 == error::None);
                ASSERT_FALSE(date0.isOnHeap());
                ASSERT_FALSE(date0.isEmpty());

                auto [err_1, date1] = getSavedDate->bind(calender1).call();
                ASSERT_TRUE(err_1 == error::None);
                ASSERT_FALSE(date1.isOnHeap());
                ASSERT_FALSE(date1.isEmpty());

                // both objects must be equal, created via default-constructor, different instances, not shared.
                EXPECT_TRUE(date::test_if_obejcts_are_equal(date0.get(), date1.get(), true));

                optional<Record> structDate = cxxMirror.getRecord(date::ns, date::struct_);
                ASSERT_TRUE(structDate);
                // 'updateDate' is const-member-function in 'Date' class.
                optional<Method> updateDate = structDate->getMethod(date::str_updateDate);
                ASSERT_TRUE(updateDate);
                string dateStr = date::DATE_STR1;
                {
                    auto [err, ret] = updateDate->bind(date0).call(dateStr);
                    // Invocation of const-member-function requires const-target, but 'date0' is non-const.
                    EXPECT_TRUE(err == error::ImplicitCallToNonConstOnConstTarget && ret.isEmpty());
                } {
                    // Explicitly bind a const member function to 'date0' and invoke it treating 'date0' as const.
                    auto [err, ret] = updateDate->bind<methodQ::NonConst>(date0).call(dateStr);
                    EXPECT_TRUE(err == error::None && ret.isEmpty());
                    // After mutation, they should be not be equal, since both are unique instances.
                    EXPECT_FALSE(date::test_if_obejcts_are_equal(date0.get(), date1.get(), true));
                }
            }
        }
        // After scope exit, stack instances are cleaned up automatically
        EXPECT_TRUE(calender::get_instance_count() == 0);
        EXPECT_TRUE(event::get_instance_count() == 0);
        EXPECT_TRUE(date::get_instance_count() == 0);
    }
}
