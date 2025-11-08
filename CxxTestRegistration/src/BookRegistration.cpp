
#include <Reflect.hpp>

#include "Book.h"
#include "Registration.h"
#include "TestUtilsBook.h"

using namespace test_utils;

namespace test_mirror
{
    void addTypeIdBook(std::unordered_map<std::string, std::size_t>& id)
    {
        id.insert(std::make_pair(book::class_, rtl::detail::TypeId<Book>::get()));
    }

	void registerTypeBook(std::vector<rtl::Function>& fns)
	{
		//  class 'Book', methods & constructors.
        //  Registering default constructor.
        fns.push_back(rtl::type().record<Book>(book::class_)
                                 .build());
        
        //  Registering overloaded constructor, signature must be specified as template parameter.
        fns.push_back(rtl::type().member<Book>()
                                 .constructor<double, std::string>()
                                 .build());
        
        //  Unique methods, no overloads.
        fns.push_back(rtl::type().member<Book>()
                                 .method(book::str_setAuthor)
                                 .build(&Book::setAuthor));
        
        //  Unique method, taking 'std::string' & 'const std::string&' as argument, auto deduced via function-pointer.
        fns.push_back(rtl::type().member<Book>()
                                 .method(book::str_addPreface)
                                 .build(&Book::addPreface));
        
        //  Furthur registrations of unique-menthods, signature auto-deduced via function pointer.
        fns.push_back(rtl::type().member<Book>()
                                 .method(book::str_setDescription)
                                 .build(&Book::setDescription));

        fns.push_back(rtl::type().member<Book>()
                                 .method(book::str_getPublishedOn)
                                 .build(&Book::getPublishedOn));

        fns.push_back(rtl::type().member<Book>()
                                 .method(book::str_addCopyrightTag)
                                 .build(&Book::addCopyrightTag));

        //  Registering overloaded methods, signature must be specified as template params since other overloads exists, else compiler error.
        fns.push_back(rtl::type().member<Book>()
                                 .method<void>(book::str_updateBookInfo)
                                 .build(&Book::updateBookInfo));

        fns.push_back(rtl::type().member<Book>()
                                 .method<const char*, double, std::string>(book::str_updateBookInfo)
                                 .build(&Book::updateBookInfo));

        fns.push_back(rtl::type().member<Book>()
                                 .method<std::string, double, const char*>(book::str_updateBookInfo)
                                 .build(&Book::updateBookInfo));
	}
}