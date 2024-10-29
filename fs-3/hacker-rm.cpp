#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <file-to-erase>" << endl;
        return 1;
    }
    string filePath = argv[1];
    fstream file(filePath, ios::in | ios::out | ios::binary);
    if (!file)
    {
        cerr << "Error opening file" << endl;
        return 1;
    }
    file.seekg(0, ios::end);
    long fileSize = file.tellg(); 
    file.seekg(0);
    for (long i = 0; i < fileSize; ++i)
        file.put('\0');
    file.close();
    if (remove(filePath.c_str()) == 0)
        cout << "File securely deleted: " << filePath << endl;
    else
        cerr << "Error deleting file" << endl;
    return 0;
}
