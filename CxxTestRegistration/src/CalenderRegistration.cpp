
#include <Reflect.hpp>

#include "Registration.h"

#include "Date.h"
#include "TestUtilsDate.h"

using namespace test_utils;

namespace test_mirror
{
    void addTypeIdCalender(std::unordered_map<std::string, std::size_t>& id)
    {
        id.insert(std::make_pair(calender::struct_, rtl::detail::TypeId<nsdate::Calender>::get()));
    }

	void registerTypeCalender(std::vector<rtl::Function>& fns)
	{
        //  Registring static-method, 'methodStatic()' function must be used. compiler error otherwise.
        fns.push_back(rtl::type().member<nsdate::Calender>()
                                 .methodStatic(calender::str_create)
                                 .build(&nsdate::Calender::create));

        //  Registring unique methods of class Calender, no overloads.
        fns.push_back(rtl::type().member<nsdate::Calender>()
                                 .method(calender::str_getTheEvent)
                                 .build(&nsdate::Calender::getTheEvent));

        fns.push_back(rtl::type().member<nsdate::Calender>()
                                 .method(calender::str_getTheDate)
                                 .build(&nsdate::Calender::getTheDate));

        fns.push_back(rtl::type().member<nsdate::Calender>()
                                 .method(calender::str_getSavedEvent)
                                 .build(&nsdate::Calender::getSavedEvent));

        fns.push_back(rtl::type().member<nsdate::Calender>()
                                 .method(calender::str_getSavedDate)
                                 .build(&nsdate::Calender::getSavedDate));

        //  class Calender, registering after the methods. (order doesn't matter)
        fns.push_back(rtl::type().ns(date::ns)
                                 .record<nsdate::Calender>(calender::struct_)
                                 .build());
	}
}