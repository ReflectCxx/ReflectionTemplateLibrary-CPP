
#include "CppMirrorBuilder.h"

#include "Book.h"
#include "Reflection.h"

using namespace rtl;
using namespace std;

const CppMirror<>& Reflection::system()
{
    static CppMirror<> cppMirror = CppMirror<>(
    {
        add<Book, ctor::VOID, ctor::COPY, ctorArgs<const string&>, 
        ctorArgs<double, string>, ctorArgs<Date&, string>>("Book")->add(
        {
            { "getTitle", add(&Book::getTitle) },
            { "getAuthor", add(&Book::getAuthor) },
            { "getBookInfo", add<typeQ::CONST>(&Book::getBookInfo) },
            { "getPublishedOn", add(&Book::getPublishedOn) },
            { "getPublishedOn", add<typeQ::CONST>(&Book::getPublishedOn) },

            { "setAuthor", args<const char*>::add(&Book::setAuthor) },
            { "setAuthor", args<std::string>::add(&Book::setAuthor) },
            { "setAuthor", args<std::string&>::add(&Book::setAuthor) },
            { "setAuthor", args<const std::string&>::add(&Book::setAuthor) },

            { "setPublishedOn", args<Date&>::add(&Book::setPublishedOn) },
            { "setPublishedOn", args<const Date&>::add(&Book::setPublishedOn) },
            { "setPublishedOn", args<int, int, int>::add(&Book::setPublishedOn) },
        })
    });

    return cppMirror;
}
