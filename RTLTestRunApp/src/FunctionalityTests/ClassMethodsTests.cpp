
#include <rtl_access.h>
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
		const auto& rtl_recordsNameMap = cxx::mirror().getRecordsMap();
		for (const auto& itr : rtl_recordsNameMap)
		{
			const std::string& recordName = itr.first;
			const traits::uid_t recordId = cxx::reflected_id(recordName);
			const auto& itr0 = rtl_recordIdMap.find(recordId);

			ASSERT_TRUE(itr0 != rtl_recordIdMap.end());

			const rtl::Record& reflectedClass = itr0->second;

			auto [err, robj] = reflectedClass.ctorT<>()(rtl::alloc::Stack);

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


	TEST(ReflectionMethodCall_heapInstance, wrong_args)
	{
		{
			optional<Record> classBook = cxx::mirror().getRecord(std::string(rtcl::type::Book::id));
			ASSERT_TRUE(classBook);

			auto [err0, book] = classBook->ctorT<>()(alloc::Heap);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			optional<Method> oSetAuthor = classBook->getMethod(std::string(rtcl::type::Book::method::setAuthor));
			ASSERT_TRUE(oSetAuthor);
			EXPECT_FALSE(oSetAuthor->hasSignature<const char*>());

			auto setAuthor = oSetAuthor->targetT<>().argsT<const char*>().returnT<>();
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

			auto [err0, book] = classBook->ctorT<>()(alloc::Stack);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			optional<Method> oSetAuthor = classBook->getMethod(book::str_setAuthor);
			ASSERT_TRUE(oSetAuthor);
			EXPECT_FALSE(oSetAuthor->hasSignature<const char*>());

			auto setAuthor = oSetAuthor->targetT().argsT<const char*>().returnT();
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

			auto [err0, book] = classBook->ctorT<>()(alloc::Stack);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			optional<Method> oGetPublishedOn = classBook->getMethod(book::str_getPublishedOn);
			ASSERT_TRUE(oGetPublishedOn);
			EXPECT_TRUE(oGetPublishedOn->hasSignature<>());	//empty template params checks for zero arguments.

			auto getPublishedOn = oGetPublishedOn->targetT().argsT().returnT();
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

			auto [err0, book] = classBook->ctorT<>()(alloc::Stack);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			optional<Method> oGetPublishedOn = classBook->getMethod(book::str_getPublishedOn);
			ASSERT_TRUE(oGetPublishedOn);
			EXPECT_TRUE(oGetPublishedOn->hasSignature<>());	//empty template params checks for zero arguments.

			auto getPublishedOn = oGetPublishedOn->targetT().argsT().returnT();
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

			auto [err0, book] = classBook->ctorT<>()(alloc::Heap);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			optional<Method> oSetAuthor = classBook->getMethod(book::str_setAuthor);
			ASSERT_TRUE(oSetAuthor);
			EXPECT_TRUE(oSetAuthor->hasSignature<std::string>());

			auto setAuthor = oSetAuthor->targetT().argsT<std::string>().returnT();
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

			auto [err0, book] = classBook->ctorT<>()(alloc::Stack);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			optional<Method> oSetAuthor = classBook->getMethod(book::str_setAuthor);
			ASSERT_TRUE(oSetAuthor);
			EXPECT_TRUE(oSetAuthor->hasSignature<std::string>());

			auto setAuthor = oSetAuthor->targetT().argsT<std::string>().returnT();
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

			auto [err0, book] = classBook->ctorT<>()(alloc::Heap);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			optional<Method> oUpdateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(oUpdateBookInfo);
			EXPECT_TRUE(oUpdateBookInfo->hasSignature<>());	//empty template params checks for zero arguments.
			
			auto updateBookInfo = oUpdateBookInfo->targetT().argsT().returnT();
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

			auto [err0, book] = classBook->ctorT<>()(alloc::Stack);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			optional<Method> oUpdateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(oUpdateBookInfo);
			EXPECT_TRUE(oUpdateBookInfo->hasSignature<>());	//empty template params checks for zero arguments.

			auto updateBookInfo = oUpdateBookInfo->targetT().argsT().returnT();
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

			auto [err0, book] = classBook->ctorT<>()(alloc::Heap);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			optional<Method> oUpdateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(oUpdateBookInfo);
			EXPECT_TRUE((oUpdateBookInfo->hasSignature<string, double, const char*>()));

			auto updateBookInfo = oUpdateBookInfo->targetT().argsT<std::string, double, const char*>().returnT();
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

			auto [err0, book] = classBook->ctorT<>()(alloc::Stack);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			optional<Method> oUpdateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(oUpdateBookInfo);
			EXPECT_TRUE((oUpdateBookInfo->hasSignature<string, double, const char*>()));

			auto updateBookInfo = oUpdateBookInfo->targetT().argsT<std::string, double, const char*>().returnT();
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

			auto [err0, book] = classBook->ctorT<>()(alloc::Heap);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			optional<Method> oUpdateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(oUpdateBookInfo);
			EXPECT_TRUE((oUpdateBookInfo->hasSignature<const char*, double, string>()));

			auto updateBookInfo = oUpdateBookInfo->targetT().argsT<const char*, double, string>().returnT();
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

			auto [err0, book] = classBook->ctorT<>()(alloc::Stack);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			optional<Method> oUpdateBookInfo = classBook->getMethod(book::str_updateBookInfo);
			ASSERT_TRUE(oUpdateBookInfo);
			EXPECT_TRUE((oUpdateBookInfo->hasSignature<const char*, double, string>()));

			auto updateBookInfo = oUpdateBookInfo->targetT().argsT<const char*, double, std::string>().returnT();
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

			auto [err0, book] = classBook->ctorT<>()(alloc::Stack);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			optional<Method> oAddCopyrightTag = classBook->getMethod(book::str_addCopyrightTag);
			ASSERT_TRUE(oAddCopyrightTag);
			EXPECT_TRUE(oAddCopyrightTag->hasSignature<string>());

			auto addCopyrightTag = oAddCopyrightTag->targetT().argsT<std::string>().returnT();
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

			auto [err0, book] = classBook->ctorT<>()(alloc::Heap);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			optional<Method> oAddCopyrightTag = classBook->getMethod(book::str_addCopyrightTag);
			ASSERT_TRUE(oAddCopyrightTag);
			EXPECT_TRUE((oAddCopyrightTag->hasSignature<string>()));

			auto addCopyrightTag = oAddCopyrightTag->targetT().argsT<std::string>().returnT();
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

			auto [err0, book] = classBook->ctorT<>()(alloc::Stack);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			optional<Method> oAddPreface = classBook->getMethod(book::str_addPreface);
			ASSERT_TRUE(oAddPreface); 
			EXPECT_FALSE((oAddPreface->hasSignature<string, string&>()));
			EXPECT_FALSE((oAddPreface->hasSignature<string, const string>()));
			EXPECT_FALSE((oAddPreface->hasSignature<string, string>()));
			//if reference is involved, then const-qualifier must be exactly same as in signature reference type.
			EXPECT_TRUE((oAddPreface->hasSignature<string, const string&>()));

			auto addPreface = oAddPreface->targetT().argsT<string, string>().returnT();
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

			auto [err0, book] = classBook->ctorT<>()(alloc::Heap);

			EXPECT_TRUE(err0 == error::None);
			ASSERT_FALSE(book.isEmpty());

			optional<Method> oAddPreface = classBook->getMethod(book::str_addPreface);
			ASSERT_TRUE(oAddPreface); 
			EXPECT_FALSE((oAddPreface->hasSignature<string, string>()));
			EXPECT_FALSE((oAddPreface->hasSignature<string, string&>()));
			EXPECT_FALSE((oAddPreface->hasSignature<string, const string>()));
			//if reference is involved, then const-qualifier must be exactly same as in signature reference type.
			EXPECT_TRUE((oAddPreface->hasSignature<string, const string&>()));

			auto addPreface = oAddPreface->targetT().argsT<string, string>().returnT();
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