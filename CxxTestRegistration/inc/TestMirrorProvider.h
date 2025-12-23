#pragma once

#include <rtl_traits.h>

namespace rtl {
	class CxxMirror;
}

namespace test_mirror
{
	struct cxx {

		static const rtl::CxxMirror& mirror();

		static const rtl::traits::uid_t reflected_id(const std::string& pRecordName);
	};
}