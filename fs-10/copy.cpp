#include <iostream>
#include <fstream>
int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: ./copy <source-file> <destination-file>" << std::endl;
        return 1;
    }
    std::ifstream source(argv[1], std::ios::binary);
    if (!source)
    {
        std::cerr << "Error: Could not open source file." << std::endl;
        return 1;
    }
    std::ofstream destination(argv[2], std::ios::binary);
    if (!destination)
    {
        std::cerr << "Error: Could not open destination file." << std::endl;
        return 1;
    }
    char byte;
    size_t totalBytesCopied = 0;
    while (source.read(&byte, 1))
    {
        destination.write(&byte, 1);
        totalBytesCopied++;
    }
    std::cout << "Successfully copied " << totalBytesCopied << " bytes." << std::endl;
    return 0;
}
