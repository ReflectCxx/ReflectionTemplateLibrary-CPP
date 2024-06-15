
#include <cassert>
#include <iostream>

#include "Reflection.h"

using namespace rtl;
using namespace rtl_tests;

int main()
{
	auto& cxxMirror = CxxReflection::instance();

	auto showBook = cxxMirror.getFunction("book", "showBookInfo");

	std::cout << "\n1st Call : ";
	
	if (showBook.has_value()) {
		cxxMirror(showBook.value())();
	}

	const double& price = 99.99;
	const unsigned int& pages = 1050;
	const char* bookName = "Somehow, I manage.";
	const std::string& author = "Micheal G. Scott";

	std::cout << "\n2nd Call : ";
	auto addBook = cxxMirror.getFunction("book", "addBookInfo");
	if (addBook.has_value()) {
		cxxMirror(addBook.value())(bookName, author, pages, price);
	}

	std::cout << "\n3rd Call : ";
	if (showBook.has_value()) {
		cxxMirror(showBook.value())();
	}

	return 0;
}