#include <iostream>
#include <cassert>
#include <vector>

#include "inc/GlobalFlagsContainer.hpp"
#include "inc/FilePathExtractor.hpp"
#include "inc/DaedalusLinker.hpp"

#define MIN_NUM_OF_ARGS 3
#define IN_FILE_PATH_ARG 1
#define OUT_FILE_PATH_ARG 2

bool checkNumOfArgs(int argc)
{
    if(argc < MIN_NUM_OF_ARGS)
    {
        std::cerr << "ERR: Input and output files must be provided. Exiting..." << std::endl;
        return false;
    }
    else
    {
        return true;
    }
    
}

int main(int argc, char* argv[])
{
    if(not checkNumOfArgs(argc))
    {
        return -1;
    }

    GlobalFlagsContainer globalFlagsContainer(std::vector<std::string>(argv + MIN_NUM_OF_ARGS, argv + argc));

    std::string inputFilePath = argv[IN_FILE_PATH_ARG];
    std::string outputFilePath = argv[OUT_FILE_PATH_ARG];

    FilePathExtractor filePathExtractor(inputFilePath, globalFlagsContainer.recursiveSearchFlag);
    auto extractedFilePaths = filePathExtractor.extractFilePaths();

    DaedalusLinker daedalusLinker(outputFilePath, extractedFilePaths, globalFlagsContainer.commentsRemovalFlag);
    daedalusLinker.link();

    return 0;
}
