#include "../inc/DaedalusLinker.hpp"
#include "../inc/DaedalusLinkerWithComments.hpp"
#include "../inc/DaedalusLinkerWithoutComments.hpp"
#include <iostream>
#include <memory>

DaedalusLinker::DaedalusLinker(const std::string& _outputFilePath,
                               const std::vector<fs::path>& _filePaths,
                               const bool _commentsRemovalFlag) 
                               : outputFilePath(_outputFilePath),
                                 filePaths(_filePaths),
                                 commentsRemovalFlag(_commentsRemovalFlag) {}

void DaedalusLinker::link()
{
    std::unique_ptr<DaedalusLinkerBase> linker;

    if(commentsRemovalFlag)
    {
        linker = std::make_unique<DaedalusLinkerWithoutComments>(outputFilePath, filePaths);
    }
    else
    {
        linker = std::make_unique<DaedalusLinkerWithComments>(outputFilePath, filePaths);
    }

    clearOutputFileContent();
    std::ofstream output(outputFilePath, std::ios_base::binary | std::ios_base::app);

    linker->link(output);

    output.close();
}

void DaedalusLinker::clearOutputFileContent()
{
    std::ofstream output(outputFilePath, std::ios::out | std::ofstream::trunc);
    output.close();
}