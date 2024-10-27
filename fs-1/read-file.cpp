#include <iostream>
#include <fstream>
#include <string>
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }
    const char* filePath = argv[1];
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file '" << filePath << "'" << std::endl;
        return 1;
    }
    std::string line;
    while (std::getline(file, line))
        std::cout << line << std::endl;
    if (file.bad())
    {
        std::cerr << "Error: An error occurred while reading the file." << std::endl;
        return 1;
    }
    file.close();
    return 0;
}
