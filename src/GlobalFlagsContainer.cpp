#include "../inc/GlobalFlagsContainer.hpp"
#include <iostream>

GlobalFlagsContainer::GlobalFlagsContainer(std::vector<std::string> flags)
{
    setFlags(flags);
}

void GlobalFlagsContainer::setFlags(std::vector<std::string> flags)
{
    for(auto flag : flags)
    {
        if(flag == "--removeComments")
        {
            commentsRemovalFlag = true;
        }
        else if(flag == "--recursiveSearch")
        {
            recursiveSearchFlag = true;
        }
        else
        {
            std::cout << "WRN: Cannot set " << flag << " flag. Skipping..." << std::endl;
        }
    }
}