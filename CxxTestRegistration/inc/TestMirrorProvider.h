#pragma once

namespace rtl {
	class CxxMirror;
}

namespace test_mirror
{
	struct cxx {

		static const rtl::CxxMirror& mirror();

		static const std::size_t reflected_id(const std::string& pRecordName);
	};
}