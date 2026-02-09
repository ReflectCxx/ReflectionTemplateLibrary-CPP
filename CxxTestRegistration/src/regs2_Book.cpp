

#include "reg_ids.h"
#include "reg_decls.h"

#include "Book.h"


namespace regs2::type0 {
    void init(std::vector<rtl::Function>& fns) {

        fns.push_back(rtl::type().record<Book>(cxx::type::Book::id)
                                 .build());

        fns.push_back(rtl::type().member<Book>()
                                 .constructor<double, std::string>().build());

        fns.push_back(rtl::type().member<Book>()
                                 .method(cxx::type::Book::fn::setAuthor::id)
                                 .build(&Book::setAuthor));

        fns.push_back(rtl::type().member<Book>()
                                 .methodConst(cxx::type::Book::fn::getTitle::id)
                                 .build(&Book::getTitle));

        fns.push_back(rtl::type().member<Book>()
                                 .method(cxx::type::Book::fn::addCopyrightTag::id)
                                 .build(&Book::addCopyrightTag));

        fns.push_back(rtl::type().member<Book>()
                                 .method(cxx::type::Book::fn::setDescription::id)
                                 .build(&Book::setDescription));

        fns.push_back(rtl::type().member<Book>()
                                 .method(cxx::type::Book::fn::getPublishedOn::id)
                                 .build(&Book::getPublishedOn));

        fns.push_back(rtl::type().member<Book>()
                                 .methodStatic(cxx::type::Book::fn::getInstanceCount::id)
                                 .build(&Book::getInstanceCount));

        fns.push_back(rtl::type().member<Book>()
                                 .method<void>(cxx::type::Book::fn::updateBookInfo::id)
                                 .build(&Book::updateBookInfo));

        fns.push_back(rtl::type().member<Book>()
                                 .method<const char *, double, std::string>(cxx::type::Book::fn::updateBookInfo::id)
                                 .build(&Book::updateBookInfo));

        fns.push_back(rtl::type().member<Book>()
                                 .method<std::string, double, const char *>(cxx::type::Book::fn::updateBookInfo::id)
                                 .build(&Book::updateBookInfo));

        fns.push_back(rtl::type().member<Book>()
                                 .method(cxx::type::Book::fn::addPreface::id)
                                 .build(&Book::addPreface));
    }
}

