
#include <Reflect.hpp>

#include "Date.h"
#include "Registration.h"
#include "TestUtilsDate.h"

using namespace test_utils;

namespace test_mirror
{
	void registerTypeEvent(std::vector<rtl::Function>& fns)
	{
		//  Registering 'Event' for reflection; instance creation via reflection fails since its default constructor is private or deleted.
		//  At least one member must be registered for RTL to recognize the type. be it property, member-function or constructor.
		fns.push_back(rtl::type().ns(event::ns)
								 .record<nsdate::Event>(event::struct_)
								 .build());

		fns.push_back(rtl::type().member<nsdate::Event>()
								 .method(event::str_reset)
								 .build(&nsdate::Event::reset));
	}
}