#pragma once

#include <rtl_traits.h>
#include <rtcl_meta_ids.h>

#include "reg_ids.h"

namespace rtl {
	class CxxMirror;
}

namespace cxx {

	const rtl::CxxMirror& mirror();

	const rtl::traits::uid_t reflected_id(const std::string& pRecordName);
};
