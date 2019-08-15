#include "../inc/DaedalusLinkerBase.hpp"

DaedalusLinkerBase::DaedalusLinkerBase(const std::string& _outputFilePath,
                                       const std::vector<fs::path>& _filePaths) : outputFilePath(_outputFilePath),
                                                                                  filePaths(_filePaths) {}

bool DaedalusLinkerBase::isDaedalusFile(const fs::path& path)
{
    return path.extension().string() == daedalusExtension;
}

void DaedalusLinkerBase::clearOutputFileContent()
{
    std::ofstream output(outputFilePath, std::ios::out | std::ofstream::trunc);
    output.close();
}