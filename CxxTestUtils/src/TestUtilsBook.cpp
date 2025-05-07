
#include "TestUtilsBook.h"

//User defined types.
#include "Book.h"

using namespace std;
using namespace nsdate;

namespace test_utils
{
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
	const bool book::test_dynamic_alloc_instance_ctor<>(const any& pInstance, bool pIsOnHeap)
	{
		if (pIsOnHeap) {
			Book* rbook = any_cast<Book*>(pInstance);
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
	const bool book::test_dynamic_alloc_instance_ctor<double, string>(const any& pInstance, bool pIsOnHeap)
	{
		if (pIsOnHeap) {
			Book* rbook = any_cast<Book*>(pInstance);
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


	const bool book::test_method_setAuthor(const any& pInstance, bool pIsOnHeap)
	{
		Book book;
		book.setAuthor(AUTHOR);
		if (pIsOnHeap) {
			Book* rbook = any_cast<Book*>(pInstance);
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
	const bool book::test_method_updateBookInfo<>(const any& pInstance, bool pIsOnHeap)
	{
		Book book;
		book.updateBookInfo();
		if (pIsOnHeap) {
			Book* rbook = any_cast<Book*>(pInstance);
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
	const bool book::test_method_updateBookInfo<const char*, double, string>(const any& pInstance, bool pIsOnHeap)
	{
		Book book;
		book.updateBookInfo(TITLE, PRICE, string(AUTHOR));
		if (pIsOnHeap) {
			Book* rbook = any_cast<Book*>(pInstance);
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
	const bool book::test_method_updateBookInfo<string, double, const char*>(const any& pInstance, bool pIsOnHeap)
	{
		Book book;
		book.updateBookInfo(string(AUTHOR), PRICE, TITLE);
		if (pIsOnHeap) {
			Book* rbook = any_cast<Book*>(pInstance);
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


	const bool test_utils::book::test_unique_copy_ctor_const_ref(const std::any& pInstance, bool pOnHeap)
	{
		Book obj(PRICE, TITLE);
		obj.setAuthor(AUTHOR);
		obj.setDescription(DESCRIPTION);
		Book copyObj(obj);

		if (pOnHeap) {
			Book* rbook = any_cast<Book*>(pInstance);
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