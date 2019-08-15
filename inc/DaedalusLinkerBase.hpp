#pragma once

#include <string>
#include <boost/filesystem.hpp>
#include <vector>
#include <fstream>

namespace fs = boost::filesystem;

class DaedalusLinkerBase
{
public:
    DaedalusLinkerBase(const std::string& _outputFilePath,
                       const std::vector<fs::path>& _filePaths);

    virtual void link() = 0;

protected:
    std::string outputFilePath;
    std::vector<fs::path> filePaths;
    const std::string_view daedalusExtension = ".d";

    bool isDaedalusFile(const fs::path& path);
    void clearOutputFileContent();
};