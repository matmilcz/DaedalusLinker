#pragma once

#include <boost/filesystem.hpp>
#include <vector>
#include <string_view>

namespace fs = boost::filesystem;

class FilePathExtractor
{
public:
    FilePathExtractor(const fs::path& _inputFilePath, const bool _recursiveSearchFlag = false);

    std::vector<fs::path> extractFilePaths();
    std::vector<fs::path> getExtractedFilePaths();

private:
    fs::path inputFilePath;
    const std::string_view wildcardSymbol = "*";
    const bool recursiveSearchFlag;
    std::vector<fs::path> extractedFilePaths;

    std::vector<fs::path> replaceWildcardsWithFilePaths(const std::vector<fs::path>& filePathsWithWildcards);
    std::vector<fs::path> getFilePathsFromDirectory(const fs::path& directory);
    std::vector<fs::path> getFilePathsWithWildcardsFromFile();
    fs::path getRelativePath(const fs::path& path);
    bool isWildcard(const fs::path& path) const;
    bool isDirectory(const fs::path& path) const;
};