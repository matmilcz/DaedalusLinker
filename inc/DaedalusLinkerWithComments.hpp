#pragma once

#include "DaedalusLinkerBase.hpp"

class DaedalusLinkerWithComments : public DaedalusLinkerBase
{
public:
    DaedalusLinkerWithComments(const std::string& _outputFilePath,
                               const std::vector<fs::path>& _filePaths);

    virtual void link();
};