#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) 
{
    if (argc != 3)
    {
        std::cerr << "Usage: ./simple-copy <source-file> <destination-file>" << std::endl;
        return 1;
    }
    const std::string sourceFilePath = argv[1];
    const std::string destinationFilePath = argv[2];
    std::ifstream sourceFile(sourceFilePath);
    if (!sourceFile)
    {
        std::cerr << "Error: Could not open source file: " << sourceFilePath << std::endl;
        return 1;
    }
    std::ofstream destinationFile(destinationFilePath);
    if (!destinationFile)
    {
        std::cerr << "Error: Could not open/create destination file: " << destinationFilePath << std::endl;
        return 1;
    }
    destinationFile << sourceFile.rdbuf();
    std::cout << "Successfully copied from " << sourceFilePath << " to " << destinationFilePath << std::endl;
    return 0;
}
