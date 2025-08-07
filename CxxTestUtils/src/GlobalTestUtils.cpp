
#include <string>

#include "GlobalTestUtils.h"

#include "TypeId.h"

#include "Date.h"
#include "Book.h"
#include "Person.h"
#include "Animal.h"
#include "Library.h"

#include "TestUtilsBook.h"
#include "TestUtilsDate.h"
#include "TestUtilsPerson.h"
#include "TestUtilsAnimal.h"

namespace
{
	static std::size_t g_invalidId = 0;
}


namespace test_utils {

	std::size_t id::date = rtl::detail::TypeId<nsdate::Date>::get();

	std::size_t id::book = rtl::detail::TypeId<Book>::get();

	std::size_t id::event = rtl::detail::TypeId<nsdate::Event>::get();

	std::size_t id::person = rtl::detail::TypeId<Person>::get();

	std::size_t id::animal = rtl::detail::TypeId<Animal>::get();

	std::size_t id::library = rtl::detail::TypeId<Library>::get();

	std::size_t id::calender = rtl::detail::TypeId<nsdate::Calender>::get();

	std::size_t id::std_string = rtl::detail::TypeId<std::string>::get();

	std::size_t id::std_string_view = rtl::detail::TypeId<std::string_view>::get();

	const std::size_t getRecordIdFor(const std::string& pRecordName)
	{
		if (pRecordName == book::class_) {
			return id::book;
		}
		else if (pRecordName == person::class_) {
			return id::person;
		}
		else if (pRecordName == animal::class_) {
			return id::animal;
		}
		else if (pRecordName == date::struct_) {
			return id::date;
		}
		else if (pRecordName == event::struct_) {
			return id::event;
		}
		else if (pRecordName == calender::struct_) {
			return id::calender;
		}
		else if (pRecordName == library::class_) {
			return id::library;
		}
		else if (pRecordName == "string") {
			return id::std_string;
		}
		else if (pRecordName == "string_view") {
			return id::std_string_view;
		}
		else return g_invalidId;
	}
}