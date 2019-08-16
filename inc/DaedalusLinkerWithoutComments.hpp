#pragma once

#include <DaedalusLinkerBase.hpp>
#include <optional>
#include <iostream>

typedef std::pair<size_t, size_t> BeginEndPos;

class DaedalusLinkerWithoutComments : public DaedalusLinkerBase
{
public:
    DaedalusLinkerWithoutComments(const std::string& _outputFilePath,
                                  const std::vector<fs::path>& _filePaths);

    virtual void link(std::ostream& output);

private:
    const std::string_view commentSymbol = "//";
    const std::string_view quoteSymbol = "\"";

    void writeStringWithoutCommentToOutput(std::string line, std::ostream& output);
    std::string getStringWithoutComment(const std::string& line);
    std::string getStringWithoutCommentFromStringWithQuotes(const std::string& line);
    std::string getStringWithoutCommentFromStringWithoutQuotes(const std::string& line, const std::vector<BeginEndPos>& quotesBeginEndPositions);
    bool checkIfInQuotes(size_t commentPos, const std::vector<BeginEndPos>& quotesBeginEndPositions);
    std::vector<BeginEndPos> getQuotesBeginEndPositions(const std::string& line);
    bool checkIfContainsCommentSymbol(const std::string& line);
};