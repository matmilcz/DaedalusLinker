#include "../inc/DaedalusLinkerWithoutComments.hpp"
#include <optional>
#include <iostream>

DaedalusLinkerWithoutComments::DaedalusLinkerWithoutComments(const std::string& _outputFilePath,
                                                             const std::vector<fs::path>& _filePaths) : DaedalusLinkerBase(_outputFilePath,
                                                                                                                           _filePaths) {}

void DaedalusLinkerWithoutComments::link()
{
    clearOutputFileContent();

    std::ofstream output(outputFilePath, std::ios_base::binary | std::ios_base::app);

    for(auto fileToLink : filePaths)
    {
        if(isDaedalusFile(fileToLink))
        {
            std::ifstream input(fileToLink.string());

            std::string line;
            while(std::getline(input, line))
            {
                if(checkIfContainsCommentSymbol(line))
                {
                    line = getStringWithoutComment(line);
                }
                
                output << line;

                if(line != "")
                {
                    output << "\n";
                }
            }
        }
        else
        {
            continue;
        }
    }
}

std::string DaedalusLinkerWithoutComments::getStringWithoutComment(const std::string& line)
{
    auto quotesBeginEndPositions = getQuotesBeginEndPositions(line);
    
    if(quotesBeginEndPositions.empty())
    {
        auto commentPos = line.find(commentSymbol, 0);
        return line.substr(0, commentPos);
    }
    else
    {
        size_t commentPos = 0;

        do
        {
            commentPos = line.find(commentSymbol, commentPos);
            ++commentPos;
        }
        while(checkIfInQuotes(commentPos, quotesBeginEndPositions));

        return line.substr(0, commentPos - 1);
    }
}

bool DaedalusLinkerWithoutComments::checkIfInQuotes(size_t commentPos, const std::vector<BeginEndPos>& quotesBeginEndPositions)
{
    for(auto quotePos : quotesBeginEndPositions)
    {
        if(commentPos > quotePos.first and commentPos < quotePos.second)
        {
            return true;
        }
    }

    return false;
}

std::vector<BeginEndPos> DaedalusLinkerWithoutComments::getQuotesBeginEndPositions(const std::string& line)
{
    std::vector<BeginEndPos> positions;
    std::optional<size_t> beginPos;

    size_t pos = line.find(quoteSymbol, 0);
    while(pos != std::string::npos)
    {
        if(not beginPos.has_value())
        {
            beginPos = pos;
        }
        else
        {
            positions.push_back(std::make_pair(beginPos.value(), pos));
            beginPos.reset();
        }
        pos = line.find(quoteSymbol, pos + 1);
    }

    return positions;
}

bool DaedalusLinkerWithoutComments::checkIfContainsCommentSymbol(const std::string& line)
{
    if(line.find(commentSymbol) == std::string::npos)
    {
        return false;
    }
    else
    {
        return true;
    }
    
}