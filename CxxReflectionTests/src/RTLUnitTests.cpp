
#include <cassert>
#include <iostream>

#include "Reflection.h"

using namespace rtl;
using namespace rtl_tests;

int main()
{
	auto& cxxMirror = MyReflection::instance();

	auto showBook = cxxMirror.getFunction("book", "showBookInfo");

	std::cout << "\n1st Call : ";
	
	if (showBook.has_value()) {
		showBook.value().execute();
	}

	const double& price = 99.99;
	const unsigned int& pages = 1050;
	const char* bookName = "Somehow, I manage.";
	const std::string& author = "Micheal G. Scott";

	std::cout << "\n2nd Call : ";
	auto addBook = cxxMirror.getFunction("book", "addBookInfo");
	if (addBook.has_value()) {
		addBook.value().execute(bookName, author, pages, price);
	}

	std::cout << "\n\n[Reflection]-------Function call, returns value-------";
	if (showBook.has_value()) {
		const auto retPtr = showBook.value().execute();
		const auto bookOpt = retPtr->get<std::string>();

		if (bookOpt.has_value()) {
			const auto& bookStr = bookOpt.value();
			std::cout << bookStr;
		}
		else {
			std::cout << "\nWrong type used to get value in RObject..!!";
		}
	}


	const auto& classDateOpt = cxxMirror.getRecord("test_project", "Date");
	std::cout << "\n\n[Reflection]-------Constructor/Destroctor call--------";
	if (classDateOpt.has_value()) {
		const auto& classDate = classDateOpt.value();
		auto dateObj0 = classDate.newInstance();

		const std::string& dateStr = "17/06/2024";
		auto dateObj1 = classDate.newInstance(dateStr);
	}
	
	std::cout << std::endl;

	return 0;
}