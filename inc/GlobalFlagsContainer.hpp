#pragma once

#include <string>
#include <vector>

struct GlobalFlagsContainer
{
    bool commentsRemovalFlag = false;
    bool recursiveSearchFlag = false;

    GlobalFlagsContainer(std::vector<std::string> flags);
    void setFlags(std::vector<std::string> flags);
};