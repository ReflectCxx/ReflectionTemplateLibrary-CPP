
#include <cassert>
#include <iostream>

#include "Reflection.h"

using namespace rtl;
using namespace rtl_tests;

int main()
{
	auto& cxxMirror = MyReflection::instance();

	const double& price = 99.99;
	const unsigned int& pages = 1050;
	const char* bookName = "Somehow, I manage.";
	const std::string& author = "Micheal G. Scott";

	std::cout << "\n\n[Reflection]-------Function call, sets value-------";
	auto addBook = cxxMirror.getFunction("book", "addBookInfo");
	if (addBook.has_value()) {
		addBook.value().execute(bookName, author, pages, price);
	}


	std::cout << "\n\n[Reflection]-------Function call, returns value-------";
	auto showBook = cxxMirror.getFunction("book", "showBookInfo");
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
	else {
		std::cout << "\n[Reflection] Call failed..!";
	}

	


	const auto& classDateOpt = cxxMirror.getRecord("test_project", "Date");
	std::cout << "\n\n[Reflection]-------Constructor/Destructor call--------";
	if (classDateOpt.has_value()) {

		std::cout << "\nCreating \"Date\" instances via reflection..";

		const auto& classDate = classDateOpt.value();
		auto dateObj0 = classDate.newInstance();

		if (dateObj0 == nullptr) {
			std::cout << "\nError..! \"Date()\" ctor call via reflection failed.";
			return 0;
		}

		const std::string& dateStr = "17/06/2024";
		auto dateObj1 = classDate.newInstance(dateStr);

		if (dateObj1 == nullptr) {
			std::cout << "\nError..! \"Date(std::string)\" ctor call via reflection failed.";
			return 0;
		}


		std::cout << "\n\n[Reflection]-------Member function call--------";
		const auto& getDateOpt = classDate.getMethod("getDateAsString");
		if (getDateOpt.has_value()) {
			const auto& getDateStr = getDateOpt.value();
			const auto& retOpt = getDateStr(dateObj1).invoke();

			if (retOpt != nullptr) {
				std::cout << "\ncall to Date::getDateAsString() return value : " << retOpt->get<std::string>().value();
			}
		}
		else {
			std::cout << "\nerror..! couldn't resolve function call - Date::getDateAsString().";
		}

		std::cout << "\n\n\"Date\" instances created via reflection will destroy now.";
	}
	
	std::cout << std::endl;

	return 0;
}