/*****************************************************************
 *                                                               *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP  *
 *  Copyright (c) 2025 Neeraj Singh (reflectcxx@outlook.com)     *
 *  SPDX-License-Identifier: MIT                                 *
 *                                                               *
 *****************************************************************/


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