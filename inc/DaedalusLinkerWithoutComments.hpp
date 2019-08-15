#pragma once

#include "DaedalusLinkerBase.hpp"

typedef std::pair<size_t, size_t> BeginEndPos;

class DaedalusLinkerWithoutComments : public DaedalusLinkerBase
{
public:
    DaedalusLinkerWithoutComments(const std::string& _outputFilePath,
                                  const std::vector<fs::path>& _filePaths);

    virtual void link();

private:
    const std::string_view commentSymbol = "//";
    const std::string_view quoteSymbol = "\"";

    std::string getStringWithoutComment(const std::string& line);
    bool checkIfInQuotes(size_t commentPos, const std::vector<BeginEndPos>& quotesBeginEndPositions);
    std::vector<BeginEndPos> getQuotesBeginEndPositions(const std::string& line);
    bool checkIfContainsCommentSymbol(const std::string& line);
};