
#include "TestUtilsBook.h"

//User defined types.
#include "Book.h"
#include "Library.h"

using namespace std;
using namespace nsdate;

namespace test_utils
{
	const bool library::assert_zero_instance_count()
	{
		return (Library::getInstanceCount() == 0);
	}

	const int book::get_book_instance_count()
	{
		return Book::getInstanceCount();
	}

	const bool book::assert_zero_instance_count()
	{
		return (Book::getInstanceCount() == 0);
	}


	const bool book::test_method_getPublishedOn_return(const std::string& pRetStr)
	{
		Book bookObj;
		return (bookObj.getPublishedOn() == pRetStr);
	}


	template<>
	const bool book::test_dynamic_alloc_instance_ctor<>(const any& pInstance, bool pCastAsPtr)
	{
		if (pCastAsPtr) {
			const Book* rbook = any_cast<const Book*>(pInstance);
			if (rbook == nullptr) {
				return false;
			}
			return (Book() == *rbook);
		}
		else {
			auto rbook = any_cast<Book>(&pInstance);
			return (Book() == *rbook);
		}
	}


	template<>
	const bool book::test_dynamic_alloc_instance_ctor<double, string>(const any& pInstance, bool pCastAsPtr)
	{
		if (pCastAsPtr) {
			const Book* rbook = any_cast<const Book*>(pInstance);
			if (rbook == nullptr) {
				return false;
			}
			return (Book(PRICE, TITLE) == *rbook);
		}
		else {
			const Book* rbook = any_cast<Book>(&pInstance);
			return (Book(PRICE, TITLE) == *rbook);
		}
	}


	const bool book::test_method_setAuthor(const any& pInstance, bool pCastAsPtr)
	{
		Book book;
		book.setAuthor(AUTHOR);
		if (pCastAsPtr) {
			const Book* rbook = any_cast<const Book*>(pInstance);
			if (rbook == nullptr) {
				return false;
			}
			return (book == *rbook);
		}
		else {
			auto rbook = any_cast<Book>(&pInstance);
			return (book == *rbook);
		}
	}

	const bool book::test_method_addCopyrightTag(const std::any& pInstance, bool pCastAsPtr)
	{
		Book book;
		book.addCopyrightTag(COPYRIGHT_TAG);

		if (pCastAsPtr) {
			const Book* rbook = any_cast<const Book*>(pInstance);
			if (rbook == nullptr) {
				return false;
			}
			return (book == *rbook);
		}
		else {
			auto rbook = any_cast<Book>(&pInstance);
			return (book == *rbook);
		}
	}


	const bool book::test_method_addPreface(const std::any& pInstance, bool pCastAsPtr)
	{
		Book book;
		book.addPreface(ACKNOWLEDGEMENTS, PREFACE);

		if (pCastAsPtr) {
			const Book* rbook = any_cast<const Book*>(pInstance);
			if (rbook == nullptr) {
				return false;
			}
			return (book == *rbook);
		}
		else {
			auto rbook = any_cast<Book>(&pInstance);
			return (book == *rbook);
		}
	}


	template<>
	const bool book::test_method_updateBookInfo<>(const any& pInstance, bool pCastAsPtr)
	{
		Book book;
		book.updateBookInfo();
		if (pCastAsPtr) {
			const Book* rbook = any_cast<const Book*>(pInstance);
			if (rbook == nullptr) {
				return false;
			}
			return (book == *rbook);
		}
		else {
			auto rbook = any_cast<Book>(&pInstance);
			return (book == *rbook);
		}
	}


	template<>
	const bool book::test_method_updateBookInfo<const char*, double, string>(const any& pInstance, bool pCastAsPtr)
	{
		Book book;
		book.updateBookInfo(TITLE, PRICE, string(AUTHOR));
		if (pCastAsPtr) {
			const Book* rbook = any_cast<const Book*>(pInstance);
			if (rbook == nullptr) {
				return false;
			}
			return (book == *rbook);
		}
		else {
			auto rbook = any_cast<Book>(&pInstance);
			return (book == *rbook);
		}
	}


	template<>
	const bool book::test_method_updateBookInfo<string, double, const char*>(const any& pInstance, bool pCastAsPtr)
	{
		Book book;
		book.updateBookInfo(string(AUTHOR), PRICE, TITLE);
		if (pCastAsPtr) {
			const Book* rbook = any_cast<const Book*>(pInstance);
			if (rbook == nullptr) {
				return false;
			}
			return (book == *rbook);
		}
		else {
			auto rbook = any_cast<Book>(&pInstance);
			return (book == *rbook);
		}
	}


	const bool test_utils::book::test_copy_ctor_with_mutated_object(const std::any& pInstance, bool pCastAsPtr)
	{
		Book obj(PRICE, TITLE);
		obj.setAuthor(AUTHOR);
		obj.setDescription(DESCRIPTION);
		Book copyObj(obj);

		if (pCastAsPtr) {
			const Book* rbook = any_cast<const Book*>(pInstance);
			if (rbook == nullptr) {
				return false;
			}
			return (copyObj == *rbook);
		}
		else {
			const Book* rbook = any_cast<Book>(&pInstance);
			return (copyObj == *rbook);
		}
	}
}