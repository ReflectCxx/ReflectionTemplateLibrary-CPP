

#include "reg_ids.h"
#include "reg_decls.h"

#include "Book.h"
#include "Library.h"


namespace regs9::type0 {
    void init(std::vector<rtl::Function>& fns) {

        fns.push_back(rtl::type().record<Library>(cxx::type::Library::id)
                                 .build());

        fns.push_back(rtl::type().member<Library>()
                                 .methodStatic(cxx::type::Library::fn::getBookByTitle::id)
                                 .build(&Library::getBookByTitle));

        fns.push_back(rtl::type().member<Library>()
                                 .methodStatic(cxx::type::Library::fn::getInstanceCount::id)
                                 .build(&Library::getInstanceCount));

        fns.push_back(rtl::type().member<Library>()
                                 .methodStatic(cxx::type::Library::fn::getBooksCount::id)
                                 .build(&Library::getBooksCount));

        fns.push_back(rtl::type().member<Library>()
                                 .methodStatic(cxx::type::Library::fn::addBook::id)
                                 .build(&Library::addBook));
    }
}

