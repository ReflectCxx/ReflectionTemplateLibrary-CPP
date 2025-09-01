/*************************************************************************
 *                                                                       *
 *  Reflection Template Library (RTL) - Modern C++ Reflection Framework  *
 *  https://github.com/ReflectCxx/ReflectionTemplateLibrary-CPP          *
 *                                                                       *
 *  Copyright (c) 2025 Neeraj Singh <reflectcxx@outlook.com>             *
 *  SPDX-License-Identifier: MIT                                         *
 *                                                                       *
 *************************************************************************/


#pragma once

namespace rtl {

	class CxxMirror;

	struct CxxMirrorToJson
	{
		static const std::string toJson(const CxxMirror& pCxxMirror);
		static void dump(const CxxMirror& pCxxMirror, const std::string& pFilePathStr);
	};
}