/*****************************************************************************
 *                                                                           *
 *  Reflection Template Library (RTL) - A Run-Time Reflection System for C++ *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP              *
 *                                                                           *
 *  Copyright (c) 2026 Neeraj Singh <reflectcxx@outlook.com>                 *
 *  SPDX-License-Identifier: MIT                                             *
 *                                                                           *
 *****************************************************************************/


#pragma once

namespace rtl {

	class CxxMirror;

	struct CxxMirrorToJson
	{
		static const std::string toJson(const CxxMirror& pCxxMirror);
		static void dump(const CxxMirror& pCxxMirror, const std::string& pFilePathStr);
	};
}