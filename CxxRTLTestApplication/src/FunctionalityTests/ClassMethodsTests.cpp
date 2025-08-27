#include <gtest/gtest.h>

#include "TestMirrorProvider.h"
#include "TestUtilsBook.h"
#include "TestUtilsDate.h"
#include "GlobalTestUtils.h"

using namespace std;
using namespace rtl;

using namespace test_utils;
using namespace test_mirror;

namespace rtl_tests
{
	TEST(RTLInterfaceCxxMirror, get_class_methods_with_wrong_names)
	{
		optional<Record> classBook = cxx::mirror().getRecord(book::class_);
		ASSERT_TRUE(classBook);

		optional<Method> badMethod = classBook->getMethod("no_method");
		ASSERT_FALSE(badMethod.has_value());
	}


	TEST(RTLInterfaceCxxMirror, verify_typeIds_of_registered_records)
	{
		const auto& rtl_recordIdMap = cxx::mirror().getRecordIdMap();

		for (const auto& itr0 : cxx::mirror().getNamespaceRecordMap())
		{
			const auto& namespaceRecordMap = itr0.second;
			for (const auto& itr1 : namespaceRecordMap)
			{
				const std::string& recordName = itr1.first;
				const std::size_t recordId = reflected_id::getRecordIdFor(recordName);
				const auto& itr = rtl_recordIdMap.find(recordId);

				ASSERT_TRUE(itr != rtl_recordIdMap.end());

				const rtl::Record& reflectedClass = itr->second;

				auto [err, robj] = reflectedClass.create<rtl::alloc::Stack>();

				if (recordName == event::struct_) {
					//Event's default constructor is private or deleted.
					EXPECT_TRUE(err == rtl::error::TypeNotDefaultConstructible);
					ASSERT_TRUE(robj.isEmpty());
				}
				else if (recordName == library::class_) {
					//Library's copy-constructor is deleted or private.
					EXPECT_TRUE(err == rtl::error::TypeNotCopyConstructible);
					ASSERT_TRUE(robj.isEmpty());
				}
				else if (recordName == "void") {
					//no constructor of class std::string is registered in RTL, but the calss is registered.
					EXPECT_TRUE(err == rtl::error::TypeNotDefaultConstructible);
					ASSERT_TRUE(robj.isEmpty());
				}
				else {
					EXPECT_TRUE(err == rtl::error::None);
					ASSERT_FALSE(robj.isEmpty());
					EXPECT_TRUE(robj.getTypeId() == recordId);
				}
			}
		}
	}


	TEST(ReflectionMethodCall_heapInstance, wrong_args)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> setAuthor = classBook->getMethod(book::str_setAuthor);
			ASSERT_TRUE(setAuthor);

			auto [err0, book] = classBook->create<alloc::Heap>();

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_FALSE(setAuthor->hasSignature<const char*>());

			auto [err1, ret] = (*setAuthor)(book)(book::AUTHOR);

			EXPECT_TRUE(err1 == error::SignatureMismatch);
			ASSERT_TRUE(ret.isEmpty());
			EXPECT_FALSE(book::test_method_setAuthor(book));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(ReflectionMethodCall_stackInstance, wrong_args)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> setAuthor = classBook->getMethod(book::str_setAuthor);
			ASSERT_TRUE(setAuthor);

			auto [err0, book] = classBook->create<alloc::Stack>();

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_FALSE(setAuthor->hasSignature<const char*>());

			auto [err1, ret] = (*setAuthor)(book)(book::AUTHOR);

			EXPECT_TRUE(err1 == error::SignatureMismatch);
			ASSERT_TRUE(ret.isEmpty());
			EXPECT_FALSE(book::test_method_setAuthor(book));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(ClassBookMethod_heapInstance, args_void)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> getPublishedOn = classBook->getMethod(book::str_getPublishedOn);
			ASSERT_TRUE(getPublishedOn);

			auto [err0, book] = classBook->create<alloc::Stack>();

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_TRUE(getPublishedOn->hasSignature<>());	//empty template params checks for zero arguments.
			// Slower. bind<>().call() syntax is faster.
			auto [err1, ret] = (*getPublishedOn)(book)();

			EXPECT_TRUE(err1 == error::None);
			ASSERT_FALSE(ret.isEmpty());
			EXPECT_TRUE(ret.canViewAs<string>());

			const std::string& retStr = ret.view<std::string>()->get();
			EXPECT_TRUE(book::test_method_getPublishedOn_return(retStr));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(ClassBookMethod_stackInstance, args_void)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> getPublishedOn = classBook->getMethod(book::str_getPublishedOn);
			ASSERT_TRUE(getPublishedOn);

			auto [err0, book] = classBook->create<alloc::Stack>();

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_TRUE(getPublishedOn->hasSignature<>());	//empty template params checks for zero arguments.

			auto [err1, ret] = (*getPublishedOn)(book)();

			EXPECT_TRUE(err1 == error::None);
			ASSERT_FALSE(ret.isEmpty());
			EXPECT_TRUE(ret.canViewAs<string>());

			const std::string& retStr = ret.view<std::string>()->get();
			EXPECT_TRUE(book::test_method_getPublishedOn_return(retStr));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(ClassBookMethod_heapInstance, args_string)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> setAuthor = classBook->getMethod(book::str_setAuthor);
			ASSERT_TRUE(setAuthor);

			auto [err0, book] = classBook->create<alloc::Heap>();

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_TRUE(setAuthor->hasSignature<std::string>());

			auto author = std::string(book::AUTHOR);
			auto [err1, ret] = setAuthor->bind(book).call(author);

			EXPECT_TRUE(err1 == error::None);
			ASSERT_TRUE(ret.isEmpty());
			EXPECT_TRUE(book::test_method_setAuthor(book));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(ClassBookMethod_stackInstance, args_string)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> setAuthor = classBook->getMethod(book::str_setAuthor);
			ASSERT_TRUE(setAuthor);

			auto [err0, book] = classBook->create<alloc::Stack>();

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_TRUE(setAuthor->hasSignature<std::string>());

			auto author = std::string(book::AUTHOR);
			auto [err1, ret] = setAuthor->bind(book).call(author);

			EXPECT_TRUE(err1 == error::None);
			ASSERT_TRUE(ret.isEmpty());
			EXPECT_TRUE(book::test_method_setAuthor(book));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(ClassBookMethodOverload_heapInstance, args_void)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> updateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(updateBookInfo);

			auto [err0, book] = classBook->create<alloc::Heap>();

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_TRUE(updateBookInfo->hasSignature<>());	//empty template params checks for zero arguments.
			
			auto [err1, ret] = (*updateBookInfo)(book)();

			EXPECT_TRUE(err1 == error::None);
			ASSERT_TRUE(ret.isEmpty());
			EXPECT_TRUE(book::test_method_updateBookInfo(book));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(ClassBookMethodOverload_stackInstance, args_void)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> updateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(updateBookInfo);

			auto [err0, book] = classBook->create<alloc::Stack>();

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_TRUE(updateBookInfo->hasSignature<>());	//empty template params checks for zero arguments.

			auto [err1, ret] = (*updateBookInfo)(book)();

			EXPECT_TRUE(err1 == error::None);
			ASSERT_TRUE(ret.isEmpty());
			EXPECT_TRUE(book::test_method_updateBookInfo(book));
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(ClassBookMethodOverload_heapInstance, args_string_double_charPtr)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> updateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(updateBookInfo);

			auto [err0, book] = classBook->create<alloc::Heap>();

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			const bool signatureValid = updateBookInfo->hasSignature<string, double, const char*>();
			EXPECT_TRUE(signatureValid);

			double price = book::PRICE;
			std::string author = book::AUTHOR;
			const char* title = book::TITLE;

			auto [err1, ret] = (*updateBookInfo)(book)(author, price, title);

			EXPECT_TRUE(err1 == error::None);
			ASSERT_TRUE(ret.isEmpty());

			const bool isSuccess = book::test_method_updateBookInfo<string, double, const char*>(book);
			EXPECT_TRUE(isSuccess);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(ClassBookMethodOverload_stackInstance, args_string_double_charPtr)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> updateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(updateBookInfo);

			auto [err0, book] = classBook->create<alloc::Stack>();

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			const bool signatureValid = updateBookInfo->hasSignature<string, double, const char*>();
			EXPECT_TRUE(signatureValid);

			double price = book::PRICE;
			std::string author = book::AUTHOR;
			const char* title = book::TITLE;

			auto [err1, ret] = (*updateBookInfo)(book)(author, price, title);

			EXPECT_TRUE(err1 == error::None);
			ASSERT_TRUE(ret.isEmpty());

			const bool isSuccess = book::test_method_updateBookInfo<string, double, const char*>(book);
			EXPECT_TRUE(isSuccess);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(ClassBookMethodOverload_heapInstance, args_charPtr_double_string)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> updateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(updateBookInfo);

			auto [err0, book] = classBook->create<alloc::Heap>();

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			const bool signatureValid = updateBookInfo->hasSignature<const char*, double, string>();
			EXPECT_TRUE(signatureValid);

			double price = book::PRICE;
			std::string author = book::AUTHOR;
			const char* title = book::TITLE;

			auto [err1, ret] = (*updateBookInfo)(book)(title, price, author);

			EXPECT_TRUE(err1 == error::None);
			ASSERT_TRUE(ret.isEmpty());

			const bool isSuccess = book::test_method_updateBookInfo<const char*, double, string>(book);
			EXPECT_TRUE(isSuccess);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(ClassBookMethodOverload_stackInstance, args_charPtr_double_string)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> updateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(updateBookInfo);

			auto [err0, book] = classBook->create<alloc::Stack>();

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			const bool signatureValid = updateBookInfo->hasSignature<const char*, double, string>();
			EXPECT_TRUE(signatureValid);

			double price = book::PRICE;
			std::string author = book::AUTHOR;
			const char* title = book::TITLE;

			auto [err1, ret] = (*updateBookInfo)(book)(title, price, author);

			EXPECT_TRUE(err1 == error::None);
			ASSERT_TRUE(ret.isEmpty());

			const bool isSuccess = book::test_method_updateBookInfo<const char*, double, string>(book);
			EXPECT_TRUE(isSuccess);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(ClassBookMethodOverload_stackInstance, method_args_const_string___call_with_non_const_string)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> addCopyrightTag = classBook->getMethod(book::str_addCopyrightTag);
			ASSERT_TRUE(addCopyrightTag);

			auto [err0, book] = classBook->create<alloc::Stack>();

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			const bool signatureValid = addCopyrightTag->hasSignature<string>();
			EXPECT_TRUE(signatureValid);

			//actual signature is 'const string', but we are passing 'string' as argument. which resolves to right call.
			//as long as any param_type in signature is not reference, const-qualifier do not matter.
			auto [err1, ret] = (*addCopyrightTag)(book)(std::string(book::COPYRIGHT_TAG));

			EXPECT_TRUE(err1 == error::None);
			ASSERT_TRUE(ret.isEmpty());

			const bool isSuccess = book::test_method_addCopyrightTag(book);
			EXPECT_TRUE(isSuccess);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(ClassBookMethodOverload_heapInstance, method_args_const_string___call_with_non_const_string)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> addCopyrightTag = classBook->getMethod(book::str_addCopyrightTag);
			ASSERT_TRUE(addCopyrightTag);

			auto [err0, book] = classBook->create<alloc::Heap>();

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			const bool signatureValid = addCopyrightTag->hasSignature<string>();
			EXPECT_TRUE(signatureValid);

			//actual signature is 'const string', but we are passing 'string' as argument. which resolves to right call.
			//as long as any param_type in signature is not reference, const-qualifier do not matter.
			auto [err1, ret] = (*addCopyrightTag)(book)(std::string(book::COPYRIGHT_TAG));

			EXPECT_TRUE(err1 == error::None);
			ASSERT_TRUE(ret.isEmpty());

			const bool isSuccess = book::test_method_addCopyrightTag(book);
			EXPECT_TRUE(isSuccess);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(ClassBookMethodOverload_stackInstance, method_taking_args_const_string_and_const_string_ref)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> addPreface = classBook->getMethod(book::str_addPreface);
			ASSERT_TRUE(addPreface);

			auto [err0, book] = classBook->create<alloc::Stack>();

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			bool invalidSignature = addPreface->hasSignature<string, string&>();
			EXPECT_FALSE(invalidSignature);

			invalidSignature = addPreface->hasSignature<string, const string>();
			EXPECT_FALSE(invalidSignature);

			invalidSignature = addPreface->hasSignature<string, string>();
			EXPECT_FALSE(invalidSignature);

			//if reference is involved, then const-qualifier must be exactly same as in signature reference type.
			const bool signatureValid = addPreface->hasSignature<string, const string&>();
			EXPECT_TRUE(signatureValid);

			const auto& preface = std::string(book::PREFACE);
			const auto& acknowledgements = std::string(book::ACKNOWLEDGEMENTS);

			//if the signature has any one type as reference, then types must be explicitly specified using bind<...>()
			//And reference type must be specified with exact qualifiers, other 'by value' types do no need to explicitly specify the cv-qualifiers.
			auto [err1, ret] = addPreface->bind<string, const string&>(book).call(acknowledgements, preface);

			EXPECT_TRUE(err1 == error::None);
			ASSERT_TRUE(ret.isEmpty());

			const bool isSuccess = book::test_method_addPreface(book);
			EXPECT_TRUE(isSuccess);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}


	TEST(ClassBookMethodOverload_heapInstance, method_taking_args_const_string_and_const_string_ref)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(book::class_);
			ASSERT_TRUE(classBook);

			optional<Method> addPreface = classBook->getMethod(book::str_addPreface);
			ASSERT_TRUE(addPreface);

			auto [err0, book] = classBook->create<alloc::Heap>();

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			bool invalidSignature = addPreface->hasSignature<string, string&>();
			EXPECT_FALSE(invalidSignature);

			invalidSignature = addPreface->hasSignature<string, const string>();
			EXPECT_FALSE(invalidSignature);

			invalidSignature = addPreface->hasSignature<string, string>();
			EXPECT_FALSE(invalidSignature);

			//if reference is involved, then const-qualifier must be exactly same as in signature reference type.
			const bool signatureValid = addPreface->hasSignature<string, const string&>();
			EXPECT_TRUE(signatureValid);

			const auto& preface = std::string(book::PREFACE);
			const auto& acknowledgements = std::string(book::ACKNOWLEDGEMENTS);

			//if the signature has any one type as reference, then types must be explicitly specified using bind<...>()
			//And reference type must be specified with exact qualifiers, other 'by value' types do no need to explicitly specify the cv-qualifiers.
			auto [err1, ret] = addPreface->bind<string, const string&>(book).call(acknowledgements, preface);

			EXPECT_TRUE(err1 == error::None);
			ASSERT_TRUE(ret.isEmpty());

			const bool isSuccess = book::test_method_addPreface(book);
			EXPECT_TRUE(isSuccess);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}
}