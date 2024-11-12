#include <unistd.h>
#include <iostream>
#include <cstring>
#include <fcntl.h>
#define LINE1 "first line\n"
#define LINE2 "second line\n"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "usage: " << argv[0] << " <filepath>" << std::endl;
        return 1;
    }
    const char *filepath = argv[1];
    int fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        std::cerr << "error opening file!" << std::endl;
        return 1;
    }
    int fd1 = dup(fd);
    if (fd1 == -1)
    {
        std::cerr << "error duplicating file descriptor!" << std::endl;
        close(fd);
        return 1;
    }
    write(fd, LINE1, std::strlen(LINE1));
    write(fd1, LINE2, std::strlen(LINE2));
    close(fd);
    close(fd1);
    return 0;
}
