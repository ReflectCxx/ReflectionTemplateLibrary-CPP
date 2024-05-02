#pragma once

#include <map>
#include <deque>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace clang_reflect {

	class IncludesManager
	{
		std::multimap<std::string, std::string> m_incPathDictionary;
		std::unordered_map<std::string, std::vector<std::string>> m_srcHashIncludes;

		IncludesManager();

		void dumpSelfData();

		void initIncludesToDirecectoryMap(const std::unordered_set<std::string>& pIncludes, const std::vector<std::string>& pFilePaths);

		void locateHashIncludesInSource(const std::string& pSrcFile, const std::vector<std::string>& pSrcHashIncs, 
										std::deque<std::string>& pVisitedQueue, std::unordered_set<std::string>& pIncludeDirs);	
	public:

		IncludesManager(const IncludesManager&) = delete;
		IncludesManager& operator=(const IncludesManager&) = delete;

		static IncludesManager& Instance();

		void initSourceHeaderDependencyGraph(const std::vector<std::string>& pHeaderFiles, const std::vector<std::string>& pSrcFiles);

		void loadIncludeDirsForSource(const std::string& pSrcFile, std::unordered_set<std::string>& pIncludeDirs);
	};
}