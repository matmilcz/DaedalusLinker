#pragma once

#include <DaedalusLinkerBase.hpp>
#include <iostream>

class DaedalusLinkerWithComments : public DaedalusLinkerBase
{
public:
    DaedalusLinkerWithComments(const std::string& _outputFilePath,
                               const std::vector<fs::path>& _filePaths);

    virtual void link(std::ostream& output);

private:
    void writeInputContentToOutput(std::istream& input, std::ostream& output);
};