#pragma once

#include <memory>

#include "RObject.h"

namespace test_utils
{
	struct date
	{
		static constexpr const unsigned day = 1;
		static constexpr const unsigned month = 1;
		static constexpr const unsigned year = 2000;
		static constexpr const char* DATE_STR = "23/12/2024";

		static const bool assertZeroInstanceCount();

		static const bool testNewInstanceDefaultCtor(const std::unique_ptr<rtl::access::RObject>& pInstance);

		static const bool testNewInstanceCtorString(const std::unique_ptr<rtl::access::RObject>& pInstance);

		static const bool testNewInstanceCtorUnsignedInt(const std::unique_ptr<rtl::access::RObject>& pInstance);
	};
}