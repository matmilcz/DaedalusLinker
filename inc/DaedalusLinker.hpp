#pragma once

#include <string>
#include <boost/filesystem.hpp>
#include <vector>

namespace fs = boost::filesystem;

class DaedalusLinker
{
public:
    DaedalusLinker(const std::string& _outputFilePath,
                   const std::vector<fs::path>& _filePaths,
                   const bool _commentsRemovalFlag = false);

    void link();

protected:
    std::string outputFilePath;
    std::vector<fs::path> filePaths;

private:
    bool commentsRemovalFlag;
    
    void clearOutputFileContent();
};