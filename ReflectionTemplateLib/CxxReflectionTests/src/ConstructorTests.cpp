
#include "TestFact.hpp"
#include "ConstructorTests.h"

using namespace std;
using namespace rtl;

const vector<void(*)(const TestFact&)> ConstructorTests::UNIT_TEST_CASES = {

	____REFLECTION_UNIT_TEST_CASE____
	{
		fact.TEST("CONSTRUCTOR VOID: NON-CONST OBJECT CREATION");
		fact.EXPECTATION("1. Default constructor must be called via Reflection.\n\t"
				 "2. Object created by Reflection & direct constructor call must have same state.");

		auto book = unique_ptr<Book>(new Book());
		auto reflBook = Reflection::system().getClass("Book").instance();

		fact.ASSERT_STATES_EQUAL(book, reflBook);
		fact.RESULT_DESCRIPTION(book, reflBook);
	},

	____REFLECTION_UNIT_TEST_CASE____
	{
		fact.TEST("CONSTRUCTOR VOID: CONST OBJECT CREATION");
		fact.EXPECTATION("1. Default constructor must be called via Reflection.\n\t"
				 "2. Object created by Reflection must be constant.\n\t"
				 "3. Const objects created by Reflection & direct constructor call must have same state.");

		auto book = unique_ptr<const Book>(new Book());
		auto reflBook = Reflection::system().getClass("Book").instanceConst();

		fact.ASSERT_STATES_EQUAL(book, reflBook);
		fact.RESULT_DESCRIPTION(book, reflBook);
	},

	____REFLECTION_UNIT_TEST_CASE____
	{
		fact.TEST("CONSTRUCTOR OVERLOADING: COPY");
		fact.EXPECTATION("1. Copy constructor must be called via Reflection.\n\t"
				 "2. Copy constructed objects by Reflection & direct constructor call must have same state.");

		auto book = unique_ptr<Book>(new Book(*GET_BOOK_INSTANCE().get()));
		auto reflBookSrc = ReflObject<>::create(GET_BOOK_INSTANCE());
		auto reflBook = Reflection::system().getClass("Book").instance<ctor::COPY>(reflBookSrc);

		fact.ASSERT_STATES_EQUAL(book, reflBook);
		fact.RESULT_DESCRIPTION(book, reflBook);
	},

	____REFLECTION_UNIT_TEST_CASE____
	{
		fact.TEST("CONSTRUCTOR OVERLOADING: ARGS DIFFERENT VALUE TYPES");
		fact.EXPECTATION("1. Constructor with args types <double, string> must be called via Reflection.\n\t"
				 "2. Objects created by Reflection & by direct constructor<double, string> call must have same state.");

		auto book = unique_ptr<Book>(new Book(BOOK_PRICE, string(BOOK_TITLE)));
		auto reflBook = Reflection::system().getClass("Book").instance(BOOK_PRICE, string(BOOK_TITLE));

		fact.ASSERT_STATES_EQUAL(book, reflBook);
		fact.RESULT_DESCRIPTION(book, reflBook);
	},

	____REFLECTION_UNIT_TEST_CASE____
	{
		fact.TEST("CONSTRUCTOR OVERLOADING: ARGS CONST REFERENCE TYPE");
		fact.EXPECTATION("1. Constructor Book::Book(const string&) must be called via Reflection.\n\t"
				 "2. Objects created by Reflection & by direct Book::Book(const string&) call must have same state.");

		auto book = unique_ptr<Book>(new Book(BOOK_TITLE));
/*	Whenever calling method or constructor with const or references arguments, template params must be explicitly specified because compiler
	might deduce it differently than intended & RTL architecture is strictly typed. First template param for instance<>() method is always the
	type of object we want to create, by default its void, we can give Book here as well. By default "VOID" is implicit but must be specified
	first if we're specifying the constructor arguments.
*/		auto reflBook = Reflection::system().getClass("Book").instance<void, const string&>(BOOK_TITLE);

		fact.ASSERT_STATES_EQUAL(book, reflBook);
		fact.RESULT_DESCRIPTION(book, reflBook);
	},

	____REFLECTION_UNIT_TEST_CASE____
	{
		fact.TEST("CONSTRUCTOR OVERLOADING: ARGS NON-CONST REFERENCE TYPE");
		fact.EXPECTATION("1. Constructor Book::Book(Date&, string) must be called via Reflection.\n\t"
				 "2. Objects created by Reflection & by direct Book::Book(Date&, string) call must have same state.");

		auto date = GET_DATE_INSTANCE();
		auto book = unique_ptr<Book>(new Book(date, string(BOOK_TITLE)));
		auto reflBook = Reflection::system().getClass("Book").instance<void, Date&>(date, string(BOOK_TITLE));

		fact.ASSERT_STATES_EQUAL(book, reflBook);
		fact.RESULT_DESCRIPTION(book, reflBook);
	}

};
