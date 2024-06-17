
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

	std::cout << "\n3rd Call : ";
	if (showBook.has_value()) {
		showBook.value().execute();
	}


	const auto& classDateOpt = cxxMirror.getRecord("test_project", "Date");
	std::cout << "Constructor call...\n";
	if (classDateOpt.has_value()) {
		const auto& classDate = classDateOpt.value();
		classDate.newInstance();
	}
	return 0;
}