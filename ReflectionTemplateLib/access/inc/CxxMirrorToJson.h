#pragma once

namespace rtl {

	namespace access {
		class CxxMirror;
	}

	struct CxxMirrorToJson
	{
		static void dump(access::CxxMirror& pCxxMirror, const std::string& pFilePathStr);
	};
}