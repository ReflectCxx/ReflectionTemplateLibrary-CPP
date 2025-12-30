
#include <Reflect.hpp>

#include "Book.h"
#include "Library.h"
#include "Registration.h"
#include "TestUtilsBook.h"

using namespace test_utils;

namespace test_mirror
{
    void Register::typeIdLibrary(std::unordered_map<std::string, rtl::traits::uid_t>& id)
    {
        id.insert(std::make_pair(library::class_, rtl::traits::uid<Library>::value));
    }

	void Register::typeLibrary(std::vector<rtl::Function>& fns)
	{
		//  Registering Library's constructor. Stack allocation (rtl::alloc::Stack) will fail since its copy constructor is deleted 
        //  and its required by 'std::any' to store its object via copy-construction. But instance on heap (rtl::alloc::HEAP) can be
        //  constructed since, in that case, 'std::any' stores only the poiner which does not requires copy constructor to be called.
        fns.push_back(rtl::type().record<Library>(library::class_)
                                 .build());
        
        //  Registring static-method, 'methodStatic()' function must be used. compiler error otherwise.
        fns.push_back(rtl::type().member<Library>()
                                 .methodStatic(library::str_addBook)
                                 .build(&Library::addBook));

        fns.push_back(rtl::type().member<Library>()
                                 .methodStatic(library::str_getBookByTitle)
                                 .build(&Library::getBookByTitle));
	}
}