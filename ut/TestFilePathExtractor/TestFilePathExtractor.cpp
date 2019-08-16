#include "TestFilePathExtractor.hpp"

TestFilePathExtractor::TestFilePathExtractor()
{
    inputStr.reserve(inputStrWithWildcards.size() + inputStrWithoutWildcards.size());
    inputStr.insert(inputStr.end(), inputStrWithWildcards.begin(), inputStrWithWildcards.end());
    inputStr.insert(inputStr.end(), inputStrWithoutWildcards.begin(), inputStrWithoutWildcards.end());

    setExemplaryInput();
}

void TestFilePathExtractor::setExemplaryInput()
{
    const std::string newLine = "\n";
    auto in = inputStrWithWildcards[0] + newLine +
              inputStrWithWildcards[1] + newLine +
              inputStrWithoutWildcards[0] + newLine + 
              inputStrWithoutWildcards[1] + newLine + 
              inputStrWithoutWildcards[2] + newLine + 
              inputStrWithoutWildcards[3];
    input.str(in);
}

std::vector<fs::path> TestFilePathExtractorWithoutRecursiveSearchFlag::getFilePathsWithWildcardsFromFile(std::istream& input)
{
    return filePathExtractor.getFilePathsWithWildcardsFromFile(input);
}

MockFilePathExtractor::MockFilePathExtractor(const fs::path& _inputFilePath, const bool _recursiveSearchFlag) 
                                            : FilePathExtractor(_inputFilePath, _recursiveSearchFlag) {}


TEST_F(TestFilePathExtractorWithoutRecursiveSearchFlag, shouldReadFilePathsWithWildcardsFromInput)
{
    auto filePathsWithWildcards = getFilePathsWithWildcardsFromFile(input);

    for(auto file = 0; file < inputStr.size(); ++file)
    {
        EXPECT_EQ(filePathsWithWildcards[file].string(), inputStr[file]);
    }
}

TEST_F(TestFilePathExtractorWithoutRecursiveSearchFlag, shouldIgnoreWildcards)
{
    EXPECT_CALL(mockFilePathExtractor, getFilePathsFromDirectory).WillRepeatedly(::testing::Return(std::vector<fs::path>()));
    auto filePathsWithWildcards = getFilePathsWithWildcardsFromFile(input);
    auto filePaths = mockFilePathExtractor.replaceWildcardsWithFilePaths(filePathsWithWildcards);

    EXPECT_EQ(filePaths.size(), filePathsWithWildcards.size() - inputStrWithWildcards.size());
}