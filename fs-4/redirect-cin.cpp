#include <iostream>
#include <fstream>
#include <string>

void initialize(int argc, char** argv, std::ifstream& inputFile)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input-file>" << std::endl;
        exit(1);
    }
    const char* filePath = argv[1];
    inputFile.open(filePath);
    if (!inputFile)
    {
        std::cerr << "Error opening file: " << filePath << std::endl;
        exit(1);
    }
}

int main(int argc, char** argv)
{
    std::ifstream inputFile;
    initialize(argc, argv, inputFile);

    std::string input;
    inputFile >> input;
    std::string reversed(input.rbegin(), input.rend());
    std::cout << reversed << std::endl;

    inputFile.close();
    return 0;
}
