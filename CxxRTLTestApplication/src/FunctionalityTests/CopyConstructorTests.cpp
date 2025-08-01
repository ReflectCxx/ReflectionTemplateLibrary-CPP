#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsBook.h"

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
}