#include <gtest/gtest.h>

#include "MyReflection.h"
#include "TestUtilsBook.h"

using namespace std;
using namespace rtl;
using namespace rtl::access;
using namespace test_utils;

namespace rtl_tests 
{
	TEST(RTLInterfaceCxxMirror, get_class_methods_with_wrong_names)
	{
		CxxMirror& cxxMirror = MyReflection::instance();

		optional<Record> classBook = cxxMirror.getRecord(book::class_);
		ASSERT_TRUE(classBook);

		optional<Method> badMethod = classBook->getMethod("no_method");
		EXPECT_FALSE(badMethod.has_value());
	}


	TEST(ReflectionMethodCall_heapInstance, wrong_args)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> setAuthor = classBook->getMethod(book::str_setAuthor);
			ASSERT_TRUE(setAuthor);

			auto [status, bookObj] = classBook->create<alloc::Heap>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());
			ASSERT_FALSE(setAuthor->hasSignature<const char*>());

			status = (*setAuthor)(bookObj)(book::AUTHOR);

			ASSERT_TRUE(status == error::SignatureMismatch);
			ASSERT_FALSE(status.getReturn().has_value());
			EXPECT_FALSE(book::test_method_setAuthor(bookObj.get(), bookObj.isOnHeap()));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ReflectionMethodCall_stackInstance, wrong_args)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> setAuthor = classBook->getMethod(book::str_setAuthor);
			ASSERT_TRUE(setAuthor);

			auto [status, bookObj] = classBook->create<alloc::Stack>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());
			ASSERT_FALSE(setAuthor->hasSignature<const char*>());

			status = (*setAuthor)(bookObj)(book::AUTHOR);

			ASSERT_TRUE(status == error::SignatureMismatch);
			ASSERT_FALSE(status.getReturn().has_value());
			EXPECT_FALSE(book::test_method_setAuthor(bookObj.get(), bookObj.isOnHeap()));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ClassBookMethod_heapInstance, args_void)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> getPublishedOn = classBook->getMethod(book::str_getPublishedOn);
			ASSERT_TRUE(getPublishedOn);

			auto [status, bookObj] = classBook->create<alloc::Heap>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());
			ASSERT_TRUE(getPublishedOn->hasSignature<>());	//empty template params checks for zero arguments.

			status = (*getPublishedOn)(bookObj)();

			ASSERT_TRUE(status);
			ASSERT_TRUE(status.getReturn().has_value());
			ASSERT_TRUE(status.isOfType<string>());

			const std::string& retStr = any_cast<string>(status.getReturn());
			EXPECT_TRUE(book::test_method_getPublishedOn_return(retStr));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ClassBookMethod_stackInstance, args_void)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> getPublishedOn = classBook->getMethod(book::str_getPublishedOn);
			ASSERT_TRUE(getPublishedOn);

			auto [status, bookObj] = classBook->create<alloc::Stack>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());
			ASSERT_TRUE(getPublishedOn->hasSignature<>());	//empty template params checks for zero arguments.

			status = (*getPublishedOn)(bookObj)();

			ASSERT_TRUE(status);
			ASSERT_TRUE(status.getReturn().has_value());
			ASSERT_TRUE(status.isOfType<string>());

			const std::string& retStr = any_cast<string>(status.getReturn());
			EXPECT_TRUE(book::test_method_getPublishedOn_return(retStr));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ClassBookMethod_heapInstance, args_string)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> setAuthor = classBook->getMethod(book::str_setAuthor);
			ASSERT_TRUE(setAuthor);

			auto [status, bookObj] = classBook->create<alloc::Heap>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());
			ASSERT_TRUE(setAuthor->hasSignature<std::string>());

			auto author = std::string(book::AUTHOR);
			status = setAuthor->bind(bookObj).call(author);

			ASSERT_TRUE(status);
			ASSERT_FALSE(status.getReturn().has_value());

			EXPECT_TRUE(book::test_method_setAuthor(bookObj.get(), bookObj.isOnHeap()));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ClassBookMethod_stackInstance, args_string)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> setAuthor = classBook->getMethod(book::str_setAuthor);
			ASSERT_TRUE(setAuthor);

			auto [status, bookObj] = classBook->create<alloc::Stack>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());
			ASSERT_TRUE(setAuthor->hasSignature<std::string>());

			auto author = std::string(book::AUTHOR);
			status = setAuthor->bind(bookObj).call(author);

			ASSERT_TRUE(status);
			ASSERT_FALSE(status.getReturn().has_value());

			EXPECT_TRUE(book::test_method_setAuthor(bookObj.get(), bookObj.isOnHeap()));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ClassBookMethodOverload_heapInstance, args_void)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> updateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(updateBookInfo);

			auto [status, bookObj] = classBook->create<alloc::Heap>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());
			ASSERT_TRUE(updateBookInfo->hasSignature<>());	//empty template params checks for zero arguments.
			
			status = (*updateBookInfo)(bookObj)();

			ASSERT_TRUE(status);
			ASSERT_FALSE(status.getReturn().has_value());
			EXPECT_TRUE(book::test_method_updateBookInfo(bookObj.get(), bookObj.isOnHeap()));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ClassBookMethodOverload_stackInstance, args_void)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> updateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(updateBookInfo);

			auto [status, bookObj] = classBook->create<alloc::Stack>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());
			ASSERT_TRUE(updateBookInfo->hasSignature<>());	//empty template params checks for zero arguments.

			status = (*updateBookInfo)(bookObj)();

			ASSERT_TRUE(status);
			ASSERT_FALSE(status.getReturn().has_value());
			EXPECT_TRUE(book::test_method_updateBookInfo(bookObj.get(), bookObj.isOnHeap()));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ClassBookMethodOverload_heapInstance, args_string_double_charPtr)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> updateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(updateBookInfo);

			auto [status, bookObj] = classBook->create<alloc::Heap>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());
			const bool signatureValid = updateBookInfo->hasSignature<string, double, const char*>();
			ASSERT_TRUE(signatureValid);

			double price = book::PRICE;
			std::string author = book::AUTHOR;
			const char* title = book::TITLE;

			status = (*updateBookInfo)(bookObj)(author, price, title);

			ASSERT_TRUE(status);
			ASSERT_FALSE(status.getReturn().has_value());
			const bool isSuccess = book::test_method_updateBookInfo<string, double, const char*>(bookObj.get(), bookObj.isOnHeap());
			EXPECT_TRUE(isSuccess);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ClassBookMethodOverload_stackInstance, args_string_double_charPtr)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> updateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(updateBookInfo);

			auto [status, bookObj] = classBook->create<alloc::Stack>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());
			const bool signatureValid = updateBookInfo->hasSignature<string, double, const char*>();
			ASSERT_TRUE(signatureValid);

			double price = book::PRICE;
			std::string author = book::AUTHOR;
			const char* title = book::TITLE;

			status = (*updateBookInfo)(bookObj)(author, price, title);

			ASSERT_TRUE(status);
			ASSERT_FALSE(status.getReturn().has_value());
			const bool isSuccess = book::test_method_updateBookInfo<string, double, const char*>(bookObj.get(), bookObj.isOnHeap());
			EXPECT_TRUE(isSuccess);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ClassBookMethodOverload_heapInstance, args_charPtr_double_string)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> updateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(updateBookInfo);

			auto [status, bookObj] = classBook->create<alloc::Heap>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());
			const bool signatureValid = updateBookInfo->hasSignature<const char*, double, string>();
			ASSERT_TRUE(signatureValid);

			double price = book::PRICE;
			std::string author = book::AUTHOR;
			const char* title = book::TITLE;

			status = (*updateBookInfo)(bookObj)(title, price, author);

			ASSERT_TRUE(status);
			ASSERT_FALSE(status.getReturn().has_value());
			const bool isSuccess = book::test_method_updateBookInfo<const char*, double, string>(bookObj.get(), bookObj.isOnHeap());
			EXPECT_TRUE(isSuccess);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ClassBookMethodOverload_stackInstance, args_charPtr_double_string)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> updateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(updateBookInfo);

			auto [status, bookObj] = classBook->create<alloc::Stack>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());
			const bool signatureValid = updateBookInfo->hasSignature<const char*, double, string>();
			ASSERT_TRUE(signatureValid);

			double price = book::PRICE;
			std::string author = book::AUTHOR;
			const char* title = book::TITLE;

			status = (*updateBookInfo)(bookObj)(title, price, author);

			ASSERT_TRUE(status);
			ASSERT_FALSE(status.getReturn().has_value());
			const bool isSuccess = book::test_method_updateBookInfo<const char*, double, string>(bookObj.get(), bookObj.isOnHeap());
			EXPECT_TRUE(isSuccess);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ClassBookMethodOverload_stackInstance, method_args_const_string___call_with_non_const_string)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> addCopyrightTag = classBook->getMethod(book::str_addCopyrightTag);
			ASSERT_TRUE(addCopyrightTag);

			auto [status, bookObj] = classBook->create<alloc::Stack>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());
			const bool signatureValid = addCopyrightTag->hasSignature<string>();
			ASSERT_TRUE(signatureValid);

			//actual signature is 'const string', but we are passing 'string' as argument. which resolves to right call.
			//as long as any param_type in signature is not reference, const-qualifier do not matter.
			status = (*addCopyrightTag)(bookObj)(std::string(book::COPYRIGHT_TAG));

			ASSERT_TRUE(status);
			ASSERT_FALSE(status.getReturn().has_value());
			const bool isSuccess = book::test_method_addCopyrightTag(bookObj.get(), bookObj.isOnHeap());
			EXPECT_TRUE(isSuccess);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ClassBookMethodOverload_heapInstance, method_args_const_string___call_with_non_const_string)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> addCopyrightTag = classBook->getMethod(book::str_addCopyrightTag);
			ASSERT_TRUE(addCopyrightTag);

			auto [status, bookObj] = classBook->create<alloc::Heap>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());
			const bool signatureValid = addCopyrightTag->hasSignature<string>();
			ASSERT_TRUE(signatureValid);

			//actual signature is 'const string', but we are passing 'string' as argument. which resolves to right call.
			//as long as any param_type in signature is not reference, const-qualifier do not matter.
			status = addCopyrightTag->bind(bookObj).call(std::string(book::COPYRIGHT_TAG));

			ASSERT_TRUE(status);
			ASSERT_FALSE(status.getReturn().has_value());
			const bool isSuccess = book::test_method_addCopyrightTag(bookObj.get(), bookObj.isOnHeap());
			EXPECT_TRUE(isSuccess);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ClassBookMethodOverload_stackInstance, method_taking_args_const_string_and_const_string_ref)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> addPreface = classBook->getMethod(book::str_addPreface);
			ASSERT_TRUE(addPreface);

			auto [status, bookObj] = classBook->create<alloc::Stack>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());

			bool invalidSignature = addPreface->hasSignature<string, string&>();
			ASSERT_FALSE(invalidSignature);

			invalidSignature = addPreface->hasSignature<string, const string>();
			ASSERT_FALSE(invalidSignature);

			invalidSignature = addPreface->hasSignature<string, string>();
			ASSERT_FALSE(invalidSignature);

			//if reference is involved, then const-qualifier must be exactly same as in signature reference type.
			const bool signatureValid = addPreface->hasSignature<string, const string&>();
			ASSERT_TRUE(signatureValid);

			const auto& preface = std::string(book::PREFACE);
			const auto& acknowledgements = std::string(book::ACKNOWLEDGEMENTS);

			//if the signature has any one type as reference, then types must be explicitly specified using bind<...>()
			//And reference type must be specified with exact qualifiers, other 'by value' types do no need to explicitly specify the cv-qualifiers.
			status = addPreface->bind<string, const string&>(bookObj).call(acknowledgements, preface);

			ASSERT_TRUE(status);
			ASSERT_FALSE(status.getReturn().has_value());
			const bool isSuccess = book::test_method_addPreface(bookObj.get(), bookObj.isOnHeap());
			EXPECT_TRUE(isSuccess);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}


	TEST(ClassBookMethodOverload_heapInstance, method_taking_args_const_string_and_const_string_ref)
	{
		{
			CxxMirror& cxxMirror = MyReflection::instance();

			optional<Record> classBook = cxxMirror.getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> addPreface = classBook->getMethod(book::str_addPreface);
			ASSERT_TRUE(addPreface);

			auto [status, bookObj] = classBook->create<alloc::Heap>();

			ASSERT_TRUE(status);
			ASSERT_FALSE(bookObj.isEmpty());

			bool invalidSignature = addPreface->hasSignature<string, string&>();
			ASSERT_FALSE(invalidSignature);

			invalidSignature = addPreface->hasSignature<string, const string>();
			ASSERT_FALSE(invalidSignature);

			invalidSignature = addPreface->hasSignature<string, string>();
			ASSERT_FALSE(invalidSignature);

			//if reference is involved, then const-qualifier must be exactly same as in signature reference type.
			const bool signatureValid = addPreface->hasSignature<string, const string&>();
			ASSERT_TRUE(signatureValid);

			const auto& preface = std::string(book::PREFACE);
			const auto& acknowledgements = std::string(book::ACKNOWLEDGEMENTS);

			//if the signature has any one type as reference, then types must be explicitly specified using bind<...>()
			//And reference type must be specified with exact qualifiers, other 'by value' types do no need to explicitly specify the cv-qualifiers.
			status = addPreface->bind<string, const string&>(bookObj).call(acknowledgements, preface);

			ASSERT_TRUE(status);
			ASSERT_FALSE(status.getReturn().has_value());
			const bool isSuccess = book::test_method_addPreface(bookObj.get(), bookObj.isOnHeap());
			EXPECT_TRUE(isSuccess);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		EXPECT_TRUE(Instance::getInstanceCount() == 0);
	}
}