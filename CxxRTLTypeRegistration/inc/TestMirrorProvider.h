#pragma once

#include "RTLibInterface.h"

namespace test_mirror
{
	struct cxx
	{
		static rtl::CxxMirror& mirror();
	};


	// Optional setup: do this if you prefer to access your registered types by unique 'ID', not by string.
	struct reflected_id {

		static std::size_t date;
		static std::size_t book;
		static std::size_t event;
		static std::size_t animal;
		static std::size_t person;
		static std::size_t library;
		static std::size_t calender;

		static std::size_t char_t;
		static std::size_t void_t;
		static std::size_t std_string;
		static std::size_t std_string_view;

		static const std::size_t getRecordIdFor(const std::string& pRecordName);
	};
}