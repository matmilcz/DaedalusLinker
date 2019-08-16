#pragma once

#include <boost/filesystem.hpp>
#include <vector>
#include <string_view>
#include <fstream>
#include <iostream>

namespace fs = boost::filesystem;

class FilePathExtractor
{
    friend class TestFilePathExtractorWithoutRecursiveSearchFlag;
public:
    FilePathExtractor(const fs::path& _inputFilePath, const bool _recursiveSearchFlag = false);
    virtual ~FilePathExtractor();

    std::vector<fs::path> extractFilePaths();
    std::vector<fs::path> getExtractedFilePaths();

protected:
    virtual std::vector<fs::path> getFilePathsFromDirectory(const fs::path& directory);
    virtual std::vector<fs::path> replaceWildcardsWithFilePaths(const std::vector<fs::path>& filePathsWithWildcards);

private:
    fs::path inputFilePath;
    const std::string_view wildcardSymbol = "*";
    const bool recursiveSearchFlag = false;
    std::vector<fs::path> extractedFilePaths;

    std::vector<fs::path> getFilePathsWithWildcardsFromFile(std::istream& input);
    fs::path getRelativePath(const fs::path& path);
    bool isWildcard(const fs::path& path) const;
    bool isDirectory(const fs::path& path) const;
};