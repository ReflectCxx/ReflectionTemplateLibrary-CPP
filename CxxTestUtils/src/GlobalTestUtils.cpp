
#include <string>

#include "GlobalTestUtils.h"

#include "../../ReflectionTemplateLib/detail/inc/TypeId.h"

#include "Date.h"
#include "Book.h"
#include "Person.h"
#include "Animal.h"
#include "Library.h"

#include "TestUtilsBook.h"
#include "TestUtilsDate.h"
#include "TestUtilsPerson.h"
#include "TestUtilsAnimal.h"

static std::size_t g_invalidId = 0;

const std::size_t test_utils::getRecordIdFor(const std::string& pRecordName)
{
	if (pRecordName == book::class_) {
		return rtl::detail::TypeId<Book>::get();
	}
	else if (pRecordName == person::class_) {
		return rtl::detail::TypeId<Person>::get();
	}
	else if (pRecordName == animal::class_) {
		return rtl::detail::TypeId<Animal>::get();
	}
	else if (pRecordName == date::struct_) {
		return rtl::detail::TypeId<nsdate::Date>::get();
	}
	else if (pRecordName == calender::struct_) {
		return rtl::detail::TypeId<nsdate::Calender>::get();
	}
	else if(pRecordName == library::class_) {
		return rtl::detail::TypeId<Library>::get();
	}
	else return g_invalidId;
}