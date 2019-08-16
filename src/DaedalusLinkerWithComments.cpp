#include <DaedalusLinkerWithComments.hpp>

DaedalusLinkerWithComments::DaedalusLinkerWithComments(const std::string& _outputFilePath,
                                                       const std::vector<fs::path>& _filePaths) 
                                                       : DaedalusLinkerBase(_outputFilePath,
                                                                            _filePaths) {}

void DaedalusLinkerWithComments::link(std::ostream& output)
{
    for(auto fileToLink : filePaths)
    {
        if(isDaedalusFile(fileToLink))
        {
            std::ifstream input(fileToLink.string(), std::ios_base::binary);
            if(input.is_open())
            {
                writeInputContentToOutput(input, output);
                input.close();
            }
            else
            {
                std::cout << "WRN: Could not open " << fileToLink.string() << ". Skipping..." << std::endl;
            }
        }
    }
}

void DaedalusLinkerWithComments::writeInputContentToOutput(std::istream& input, std::ostream& output)
{
    output.seekp(0, std::ios_base::end);
    output << input.rdbuf();
}