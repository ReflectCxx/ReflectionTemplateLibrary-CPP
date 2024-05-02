
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <fstream>
#include "IncludesManager.h"
#include "Logger.h"
#include "Constants.h"
#include "CommandLineParser.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/FileSystem.h"

namespace fs = std::filesystem;

extern void extractIncludesFromCxxSources(	const std::vector<std::string>&, const std::vector<std::string>&, 
											std::unordered_set<std::string>&, 
											std::unordered_map<std::string, std::vector<std::string>>&);

namespace {

	static std::size_t countMatchingSegments(const std::vector<std::string>& pKeySegments, const std::vector<std::string>& pathSegments)
	{
		std::size_t count = 0;
		for (std::size_t i = 0; i < pKeySegments.size() && i < pathSegments.size(); ++i) {
			if (pKeySegments[i] == pathSegments[i]) {
				count++;
			}
			else break;
		}
		return count;
	}


	static void splitPath(const std::string& pPath, std::vector<std::string>& pSegments)
	{
		size_t start = 0;
		size_t end = pPath.find('/');
		while (end != std::string::npos) {
			pSegments.push_back(pPath.substr(start, end - start));
			start = end + 1;
			end = pPath.find('/', start);
		}
		pSegments.push_back(pPath.substr(start));
	}


	static std::string findClosestPath(const std::string& keyPath, const std::vector<std::string>& pathsToCompare)
	{
		std::string closestPath;
		std::size_t maxMatchCount = 0;
		std::vector<std::string> keySegments;

		splitPath(keyPath, keySegments);
		for (const auto& path : pathsToCompare)
		{
			std::vector<std::string> pathSegments;
			splitPath(path, pathSegments);

			std::size_t matchCount = countMatchingSegments(keySegments, pathSegments);
			if (matchCount > maxMatchCount) {
				maxMatchCount = matchCount;
				closestPath = path;
			}
		}
		return closestPath;
	}


	static const std::string toUnixStylePath(const std::string& pFilePath)
	{
		std::string incStr(pFilePath);
		size_t pos = std::string::npos;
		const std::string& keyStr = "../";
		std::string incPosixStr = llvm::sys::path::convert_to_slash(incStr, llvm::sys::path::Style::posix);
		incPosixStr = llvm::sys::path::remove_leading_dotslash(incStr, llvm::sys::path::Style::posix).str();
		std::replace(incPosixStr.begin(), incPosixStr.end(), '\\', '/');
		while ((pos = incPosixStr.find(keyStr)) == 0) {
			incPosixStr.erase(pos, keyStr.length());
		}
		return incPosixStr;
	}


	static const std::optional<std::string> getHeaderPathIfPresentInSourceDir(const std::string& pHashIncStr, const fs::path& pSrcDir)
	{
		if (pHashIncStr.find('/') != std::string::npos) 
		{
			if (pHashIncStr.compare(0, 2, "./") == 0) {
				const auto& file = toUnixStylePath(pHashIncStr);
				const auto& filePath = fs::path(pSrcDir.string() + "/" + file);
				if (fs::exists(filePath)) {
					return filePath.string();
				}
			}
			if (pHashIncStr.compare(0, 3, "../") == 0)
			{
				try {
					const auto& filePath = fs::canonical(pSrcDir / pHashIncStr);
					if (fs::exists(filePath)) {
						return toUnixStylePath(filePath.string());
					}
				}
				catch (const std::exception& e) {
					clang_reflect::Logger::out("exception while locating path.");
					clang_reflect::Logger::outException(std::string(e.what()));
					return std::nullopt;
				}
			}
		}
		else {
			const auto& filePath = fs::path(pSrcDir.string() + "/" + pHashIncStr);
			if (fs::exists(filePath)) {
				return filePath.string();
			}
		}
		return std::nullopt;
	}
}


namespace clang_reflect {

	IncludesManager::IncludesManager()
	{

	}


	IncludesManager& IncludesManager::Instance()
	{
		static IncludesManager instance;
		return instance;
	}


	void IncludesManager::initSourceHeaderDependencyGraph(const std::vector<std::string>& pHeaderFiles,
														  const std::vector<std::string>& pSrcFiles)
	{
		std::unordered_set<std::string> includes;
		extractIncludesFromCxxSources(pHeaderFiles, pSrcFiles, includes, m_srcHashIncludes);
		initIncludesToDirecectoryMap(includes, pHeaderFiles);

		Logger::out("Total header files found: " + std::to_string(pHeaderFiles.size()));
		Logger::out("Total #include(s) statements found in sources: " + std::to_string(includes.size()));
		Logger::out("Total header files located and mapped with #include(s): " + std::to_string(m_incPathDictionary.size()));

		dumpSelfData();
	}

	
	void IncludesManager::initIncludesToDirecectoryMap(const std::unordered_set<std::string>& pIncludes, const std::vector<std::string>& pFilePaths)
	{
		for (const std::string& includeFile : pIncludes)
		{
			const std::string nativePath = toUnixStylePath(includeFile);
			for (llvm::StringRef incPath : pFilePaths)
			{
				if (incPath.endswith(nativePath)) {
					if (incPath.endswith("/" + nativePath)) {
						std::string dirPosix = incPath.substr(0, incPath.size() - nativePath.size() - 1).str();
						m_incPathDictionary.insert(std::pair<std::string, std::string>(includeFile, dirPosix));
					}
				}
			}
		}
		Logger::out("Located include files: " + std::to_string(m_incPathDictionary.size()));
	}


	void IncludesManager::dumpSelfData()
	{
		std::fstream fout(INC_MANAGERS_DATA, std::ios::out);
		if (!fout.is_open()) {
			Logger::outException("unable to create file: " + std::string(INC_MANAGERS_DATA));
			return;
		}
		for (const auto& itr : m_srcHashIncludes) {
			fout << "\n" << itr.first << ": ";
			for (const auto& hashInc : itr.second) {
				fout << hashInc << ",";
			}
		}
		for (const auto& itr : m_incPathDictionary) {
			fout << "\n" << itr.first << ": " << itr.second << ",";
		}
		fout.close();
		Logger::out("Dumped IncludesManager's data to file.");
	}


	void IncludesManager::loadIncludeDirsForSource(const std::string& pSrcFile, std::unordered_set<std::string>& pIncludeDirs)
	{
		std::deque<std::string> headersQueue;
		std::unordered_set<std::string> visitedHeaders;
		const std::string& srcFilePath = toUnixStylePath(pSrcFile);
		headersQueue.push_back(srcFilePath);
		while (!headersQueue.empty())
		{
			const std::string nextFile = headersQueue.front();
			headersQueue.pop_front();
			if (visitedHeaders.insert(nextFile).second == false) {
				continue;
			}

			fs::path dirPathCurrent = fs::path(nextFile).parent_path();
			const auto& itr0 = m_srcHashIncludes.find(nextFile);
			if (itr0 != m_srcHashIncludes.end()) {
				locateHashIncludesInSource(nextFile, itr0->second, headersQueue, pIncludeDirs);
			}
		}
	}


	void IncludesManager::locateHashIncludesInSource(const std::string& pSrcFile, const std::vector<std::string>& pSrcHashIncs, std::deque<std::string>& pHeadersQueue, std::unordered_set<std::string>& pIncludeDirs)
	{
		const auto& dirPathCurrent = fs::path(pSrcFile).parent_path();
		for (const auto& hashIncStr : pSrcHashIncs)
		{
			const auto& incFilePathStr = getHeaderPathIfPresentInSourceDir(hashIncStr, dirPathCurrent);
			if (incFilePathStr.has_value()) {
				pHeadersQueue.push_back(incFilePathStr.value());
				continue;
			}
			const auto& itr1 = m_incPathDictionary.find(hashIncStr);
			if (itr1 != m_incPathDictionary.end())
			{
				std::string incDirPath = itr1->second;
				pIncludeDirs.insert(incDirPath);
				const auto& range = m_incPathDictionary.equal_range(hashIncStr);
				std::size_t dirCount = std::distance(range.first, range.second);
				if (dirCount > 1) {
					std::vector<std::string> possiblePaths;
					for (auto it = range.first; it != range.second; ++it) {
						possiblePaths.push_back(it->second);
					}
					incDirPath = findClosestPath(pSrcFile, possiblePaths);
				}
				const std::string& incPathPosix = toUnixStylePath(hashIncStr);
				const std::string& includePathStr = (incDirPath + (incDirPath.back() != '/' ? "/" : "") + incPathPosix);
				pHeadersQueue.push_back(includePathStr);
			}
		}
	}
}