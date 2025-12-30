
#include <Reflect.hpp>

#include "Date.h"
#include "Registration.h"
#include "TestUtilsDate.h"

using namespace test_utils;

namespace test_mirror
{
    void Register::typeIdDate(std::unordered_map<std::string, rtl::traits::uid_t>& id)
    {
        id.insert(std::make_pair(date::struct_, rtl::traits::uid<nsdate::Date>::value));
    }

	void Register::typeDate(std::vector<rtl::Function>& fns)
	{
        //  Constructors registration, class/struct name and type must be passed 'record<TYPE>("NAME")'.
        //  Registers default constructor with implicit registration of destructor & copy-constructor.
        fns.push_back(rtl::type().ns(date::ns)
                                 .record<nsdate::Date>(date::struct_)
                                 .build());

        //  Overloaded constructor, taking 'string' as argument, signature must be specified as template parameter.
        fns.push_back(rtl::type().member<nsdate::Date>()
                                 .constructor<std::string>()
                                 .build());

        //  Again, register an overloaded constructor with diffeent signature.
        fns.push_back(rtl::type().member<nsdate::Date>()
                                 .constructor<unsigned, unsigned, unsigned>()
                                 .build());
        
        //  Registring, Unique method, no overloads. Taking param 'std::string', auto deduced via function-pointer.
        fns.push_back(rtl::type().member<nsdate::Date>()
                                 .method(date::str_updateDate)
                                 .build(&nsdate::Date::updateDate));
        
        //  Registring const-method, 'methodConst()' function must be used. compiler error otherwise.
        fns.push_back(rtl::type().member<nsdate::Date>()
                                 .methodConst(date::str_getAsString)
                                 .build(&nsdate::Date::getAsString));
	}
}