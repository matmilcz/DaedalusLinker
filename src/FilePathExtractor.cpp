#include <FilePathExtractor.hpp>

FilePathExtractor::FilePathExtractor(const fs::path& _inputFilePath, const bool _recursiveSearchFlag) 
                                    : inputFilePath(_inputFilePath),
                                      recursiveSearchFlag(_recursiveSearchFlag) {}

FilePathExtractor::~FilePathExtractor() {}
                                                                    
std::vector<fs::path> FilePathExtractor::extractFilePaths()
{
    std::ifstream input{inputFilePath.string(), std::ios::in};

    if(not input.is_open())
    {
        std::cout << "WRN: Could not open file: " << inputFilePath.string() 
                  << "! Returning empty vector..." << std::endl;
    }

    auto filePathsWithWildcards = getFilePathsWithWildcardsFromFile(input);
    input.close();

    extractedFilePaths = replaceWildcardsWithFilePaths(filePathsWithWildcards);
    return extractedFilePaths;
}

std::vector<fs::path> FilePathExtractor::getExtractedFilePaths()
{
    return extractedFilePaths;
}

std::vector<fs::path> FilePathExtractor::replaceWildcardsWithFilePaths(const std::vector<fs::path>& filePathsWithWildcards)
{
    std::vector<fs::path> filePaths;

    for(const auto& path : filePathsWithWildcards)
    {
        if(isWildcard(path))
        {
            auto filePathsFromWildcard = getFilePathsFromDirectory(getRelativePath(path).parent_path());
            filePaths.reserve(filePaths.size() + std::distance(filePathsFromWildcard.begin(), filePathsFromWildcard.end()));
            filePaths.insert(filePaths.end(), filePathsFromWildcard.begin(), filePathsFromWildcard.end());
        }
        else
        {
            filePaths.push_back(getRelativePath(path));
        }
    }

    return filePaths;
}

std::vector<fs::path> FilePathExtractor::getFilePathsFromDirectory(const fs::path& directory)
{
    std::vector<fs::path> filePaths;

    for(const auto& entry : fs::directory_iterator{directory})
    {
        if(isDirectory(entry.path()))
        {
            if(recursiveSearchFlag)
            {
                auto paths = getFilePathsFromDirectory(entry);
                filePaths.reserve(filePaths.size() + std::distance(paths.begin(), paths.end()));
                filePaths.insert(filePaths.end(), paths.begin(), paths.end());
            }
            else
            {
                continue;
            }
        }
        else
        {
            filePaths.push_back(entry.path());
        }
        
    }

    return filePaths;
}

std::vector<fs::path> FilePathExtractor::getFilePathsWithWildcardsFromFile(std::istream& input)
{
    std::vector<fs::path> filePathsWithWildcards;
    std::string line;

    while(std::getline(input, line))
    {
        filePathsWithWildcards.push_back(fs::path{line});
    }

    return filePathsWithWildcards;
}

fs::path FilePathExtractor::getRelativePath(const fs::path& path)
{
    fs::path relativePath = inputFilePath.parent_path();
    relativePath /= path;
    return relativePath;
}

bool FilePathExtractor::isWildcard(const fs::path& path) const
{
    return path.filename().string() == wildcardSymbol;
}

bool FilePathExtractor::isDirectory(const fs::path& path) const
{
    return path.extension().string() == "";
}