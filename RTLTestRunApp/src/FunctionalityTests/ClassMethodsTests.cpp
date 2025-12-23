
#include <rtl/access.h>
#include <gtest/gtest.h>

#include "TestMirrorProvider.h"
#include "TestUtilsBook.h"
#include "TestUtilsDate.h"
#include "GlobalTestUtils.h"

#include "../CxxTestProps/inc/StringWrap.h"

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
				const traits::uid_t recordId = cxx::reflected_id(recordName);
				const auto& itr = rtl_recordIdMap.find(recordId);

				ASSERT_TRUE(itr != rtl_recordIdMap.end());

				const rtl::Record& reflectedClass = itr->second;

				auto [err, robj] = reflectedClass.ctor()(rtl::alloc::Stack);

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
				else if (recordName == StrWrapB::struct_ ||
                         recordName == StrWrapC::struct_ ||
                         recordName == StrWrapD::struct_) {
					EXPECT_TRUE(err == rtl::error::TypeNotDefaultConstructible);
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

			optional<Method> mthSetAuthor = classBook->getMethod(book::str_setAuthor);
			ASSERT_TRUE(mthSetAuthor);

			auto [err0, book] = classBook->ctor()(alloc::Heap);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_FALSE(mthSetAuthor->hasSignature<const char*>());

			auto setAuthor = mthSetAuthor->targetT<>().argsT<const char*>().returnT<>();
			EXPECT_FALSE(setAuthor);

			auto [err1, ret] = setAuthor(book)(book::AUTHOR);

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

			optional<Method> mthSetAuthor = classBook->getMethod(book::str_setAuthor);
			ASSERT_TRUE(mthSetAuthor);

			auto [err0, book] = classBook->ctor()(alloc::Stack);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_FALSE(mthSetAuthor->hasSignature<const char*>());

			auto setAuthor = mthSetAuthor->targetT().argsT<const char*>().returnT();
			EXPECT_FALSE(setAuthor);

			auto [err1, ret] = setAuthor(book)(book::AUTHOR);

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

			optional<Method> mthGetPublishedOn = classBook->getMethod(book::str_getPublishedOn);
			ASSERT_TRUE(mthGetPublishedOn);

			auto [err0, book] = classBook->ctor()(alloc::Stack);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_TRUE(mthGetPublishedOn->hasSignature<>());	//empty template params checks for zero arguments.

			auto getPublishedOn = mthGetPublishedOn->targetT().argsT().returnT();
			EXPECT_TRUE(getPublishedOn);

			auto [err1, ret] = getPublishedOn(book)();

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

			optional<Method> mthGetPublishedOn = classBook->getMethod(book::str_getPublishedOn);
			ASSERT_TRUE(mthGetPublishedOn);

			auto [err0, book] = classBook->ctor()(alloc::Stack);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_TRUE(mthGetPublishedOn->hasSignature<>());	//empty template params checks for zero arguments.

			auto getPublishedOn = mthGetPublishedOn->targetT().argsT().returnT();
			EXPECT_TRUE(getPublishedOn);

			auto [err1, ret] = getPublishedOn(book)();

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

			optional<Method> mthSetAuthor = classBook->getMethod(book::str_setAuthor);
			ASSERT_TRUE(mthSetAuthor);

			auto [err0, book] = classBook->ctor()(alloc::Heap);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_TRUE(mthSetAuthor->hasSignature<std::string>());

			auto setAuthor = mthSetAuthor->targetT().argsT<std::string>().returnT();
			EXPECT_TRUE(setAuthor);

			auto [err1, ret] = setAuthor(book)(book::AUTHOR);

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

			optional<Method> mthSetAuthor = classBook->getMethod(book::str_setAuthor);
			ASSERT_TRUE(mthSetAuthor);

			auto [err0, book] = classBook->ctor()(alloc::Stack);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_TRUE(mthSetAuthor->hasSignature<std::string>());

			auto setAuthor = mthSetAuthor->targetT().argsT<std::string>().returnT();
			EXPECT_TRUE(setAuthor);

			auto [err1, ret] = setAuthor(book)(book::AUTHOR);

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

			optional<Method> mthUpdateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(mthUpdateBookInfo);

			auto [err0, book] = classBook->ctor()(alloc::Heap);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_TRUE(mthUpdateBookInfo->hasSignature<>());	//empty template params checks for zero arguments.
			
			auto updateBookInfo = mthUpdateBookInfo->targetT().argsT().returnT();
			EXPECT_TRUE(updateBookInfo);

			auto [err1, ret] = updateBookInfo(book)();

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

			optional<Method> mthUpdateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(mthUpdateBookInfo);

			auto [err0, book] = classBook->ctor()(alloc::Stack);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_TRUE(mthUpdateBookInfo->hasSignature<>());	//empty template params checks for zero arguments.

			auto updateBookInfo = mthUpdateBookInfo->targetT().argsT().returnT();
			EXPECT_TRUE(updateBookInfo);

			auto [err1, ret] = updateBookInfo(book)();

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

			optional<Method> mthUpdateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(mthUpdateBookInfo);

			auto [err0, book] = classBook->ctor()(alloc::Heap);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_TRUE((mthUpdateBookInfo->hasSignature<string, double, const char*>()));

			auto updateBookInfo = mthUpdateBookInfo->targetT().argsT<std::string, double, const char*>().returnT();
			EXPECT_TRUE(updateBookInfo);

			auto [err1, ret] = updateBookInfo(book)(book::AUTHOR, book::PRICE, book::TITLE);

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

			optional<Method> mthUpdateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(mthUpdateBookInfo);

			auto [err0, book] = classBook->ctor()(alloc::Stack);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_TRUE((mthUpdateBookInfo->hasSignature<string, double, const char*>()));

			auto updateBookInfo = mthUpdateBookInfo->targetT().argsT<std::string, double, const char*>().returnT();
			EXPECT_TRUE(updateBookInfo);

			auto [err1, ret] = updateBookInfo(book)(book::AUTHOR, book::PRICE, book::TITLE);

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

			optional<Method> mthUpdateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(mthUpdateBookInfo);

			auto [err0, book] = classBook->ctor()(alloc::Heap);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_TRUE((mthUpdateBookInfo->hasSignature<const char*, double, string>()));

			auto updateBookInfo = mthUpdateBookInfo->targetT().argsT<const char*, double, string>().returnT();
			EXPECT_TRUE(updateBookInfo);

			auto [err1, ret] = updateBookInfo(book)(book::TITLE, book::PRICE, book::AUTHOR);

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

			optional<Method> mthUpdateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(mthUpdateBookInfo);

			auto [err0, book] = classBook->ctor()(alloc::Stack);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_TRUE((mthUpdateBookInfo->hasSignature<const char*, double, string>()));

			auto updateBookInfo = mthUpdateBookInfo->targetT().argsT<const char*, double, std::string>().returnT();
			EXPECT_TRUE(updateBookInfo);

			auto [err1, ret] = updateBookInfo(book)(book::TITLE, book::PRICE, book::AUTHOR);

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

			optional<Method> mthAddCopyrightTag = classBook->getMethod(book::str_addCopyrightTag);
			ASSERT_TRUE(mthAddCopyrightTag);

			auto [err0, book] = classBook->ctor()(alloc::Stack);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_TRUE(mthAddCopyrightTag->hasSignature<string>());

			auto addCopyrightTag = mthAddCopyrightTag->targetT().argsT<std::string>().returnT();
			EXPECT_TRUE(addCopyrightTag);

			//actual signature is 'const string', but we are passing 'string' as argument. which resolves to right call.
			//as long as any param_type in signature is not reference, const-qualifier do not matter.
			auto [err1, ret] = addCopyrightTag(book)(book::COPYRIGHT_TAG);

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

			optional<Method> mthAddCopyrightTag = classBook->getMethod(book::str_addCopyrightTag);
			ASSERT_TRUE(mthAddCopyrightTag);

			auto [err0, book] = classBook->ctor()(alloc::Heap);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());
			EXPECT_TRUE((mthAddCopyrightTag->hasSignature<string>()));

			auto addCopyrightTag = mthAddCopyrightTag->targetT().argsT<std::string>().returnT();
			EXPECT_TRUE(addCopyrightTag);

			//actual signature is 'const string', but we are passing 'string' as argument. which resolves to right call.
			//as long as any param_type in signature is not reference, const-qualifier do not matter.
			auto [err1, ret] = addCopyrightTag(book)(book::COPYRIGHT_TAG);

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

			optional<Method> mthAddPreface = classBook->getMethod(book::str_addPreface);
			ASSERT_TRUE(mthAddPreface);

			auto [err0, book] = classBook->ctor()(alloc::Stack);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			EXPECT_FALSE((mthAddPreface->hasSignature<string, string&>()));
			EXPECT_FALSE((mthAddPreface->hasSignature<string, const string>()));
			EXPECT_FALSE((mthAddPreface->hasSignature<string, string>()));
			//if reference is involved, then const-qualifier must be exactly same as in signature reference type.
			EXPECT_TRUE((mthAddPreface->hasSignature<string, const string&>()));

			auto addPreface = mthAddPreface->targetT().argsT<string, string>().returnT();
			EXPECT_TRUE(addPreface);

			//if the signature has any one type as reference, then types must be explicitly specified using bind<...>()
			//And reference type must be specified with exact qualifiers, other 'by value' types do no need to explicitly specify the cv-qualifiers.
			auto [err1, ret] = addPreface.bind<string, const string&>(book)(book::ACKNOWLEDGEMENTS, book::PREFACE);

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

			optional<Method> mthAddPreface = classBook->getMethod(book::str_addPreface);
			ASSERT_TRUE(mthAddPreface);

			auto [err0, book] = classBook->ctor()(alloc::Heap);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			EXPECT_FALSE((mthAddPreface->hasSignature<string, string>()));
			EXPECT_FALSE((mthAddPreface->hasSignature<string, string&>()));
			EXPECT_FALSE((mthAddPreface->hasSignature<string, const string>()));
			//if reference is involved, then const-qualifier must be exactly same as in signature reference type.
			EXPECT_TRUE((mthAddPreface->hasSignature<string, const string&>()));

			auto addPreface = mthAddPreface->targetT().argsT<string, string>().returnT();
			EXPECT_TRUE(addPreface);

			//if the signature has any one type as reference, then types must be explicitly specified using bind<...>()
			//And reference type must be specified with exact qualifiers, other 'by value' types do no need to explicitly specify the cv-qualifiers.
			auto [err1, ret] = addPreface.bind<string, const string&>(book)(book::ACKNOWLEDGEMENTS, book::PREFACE);

			EXPECT_TRUE(err1 == error::None);
			ASSERT_TRUE(ret.isEmpty());

			const bool isSuccess = book::test_method_addPreface(book);
			EXPECT_TRUE(isSuccess);
		}
		EXPECT_TRUE(book::assert_zero_instance_count());
		ASSERT_TRUE(rtl::getRtlManagedHeapInstanceCount() == 0);
	}
}