#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <FilePathExtractor.hpp>
#include <ostream>
#include <vector>

class TestFilePathExtractor : public ::testing::Test
{
public:
    TestFilePathExtractor();

protected:
    const fs::path inputFilePath = "fakePath/fakeFile.fakeExt";
    std::istringstream input;
    const std::vector<std::string> inputStrWithWildcards{ { std::string{"Path4/*"},
                                                            std::string{"Path5/*"} } };
    const std::vector<std::string> inputStrWithoutWildcards{ { std::string{"Path1/file1.ext"},
                                                               std::string{"Path2/file1.ext"},
                                                               std::string{"Path2/file2.ext"},
                                                               std::string{"Path3/file1.ext"} } };
    std::vector<std::string> inputStr;

    void setExemplaryInput();
};

class MockFilePathExtractor : public FilePathExtractor
{
public:
    MockFilePathExtractor(const fs::path& _inputFilePath, const bool _recursiveSearchFlag = false);

    MOCK_METHOD(std::vector<fs::path>, getFilePathsFromDirectory, (const fs::path& directory), (override));

    std::vector<fs::path> replaceWildcardsWithFilePaths(const std::vector<fs::path>& filePathsWithWildcards) override
    {
        return FilePathExtractor::replaceWildcardsWithFilePaths(filePathsWithWildcards);
    }
};

class TestFilePathExtractorWithoutRecursiveSearchFlag : public TestFilePathExtractor
{
protected:
    FilePathExtractor filePathExtractor{inputFilePath, false};
    MockFilePathExtractor mockFilePathExtractor{inputFilePath, false};

    std::vector<fs::path> getFilePathsWithWildcardsFromFile(std::istream& input);
};