#include "../inc/DaedalusLinkerWithComments.hpp"

DaedalusLinkerWithComments::DaedalusLinkerWithComments(const std::string& _outputFilePath,
                                                       const std::vector<fs::path>& _filePaths) : DaedalusLinkerBase(_outputFilePath,
                                                                                                                     _filePaths) {}

void DaedalusLinkerWithComments::link()
{
    clearOutputFileContent();

    std::ofstream output(outputFilePath, std::ios_base::binary | std::ios_base::app);

    for(auto fileToLink : filePaths)
    {
        if(isDaedalusFile(fileToLink))
        {
            std::ifstream input(fileToLink.string(), std::ios_base::binary);
            output.seekp(0, std::ios_base::end);
            output << input.rdbuf();
        }
        else
        {
            continue;
        }
    }
}