#pragma once

namespace rtl {
	class CxxMirror;
}

namespace test_mirror
{
	struct cxx {

		static const rtl::CxxMirror& mirror();
	};
}

namespace test_mirror
{
	// Optional setup: do this if you prefer to access your registered types by unique 'ID', not by string.
	struct reflected_id {

		static std::size_t date;
		static std::size_t book;
		static std::size_t event;
		static std::size_t animal;
		static std::size_t person;
		static std::size_t library;
		static std::size_t calender;
		static std::size_t string_m;
		static std::size_t string_c;
		static std::size_t string_s;

		static std::size_t char_t;
		static std::size_t int_t;
		static std::size_t std_string;
		static std::size_t std_string_view;

		static const std::size_t getRecordIdFor(const std::string& pRecordName);
	};
}