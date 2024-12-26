#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctime>

void do_command(char* argv[])
{
    clock_t start = clock();
    pid_t pid = fork();
    if (!pid)
    {
        execvp(argv[0], argv);
        std::cerr << "Failed to execute command" << std::endl;
        exit(1);
    }
    else if (pid > 0) 
    {
        int status;
        waitpid(pid, &status, 0);
        clock_t end = clock();
        double duration = double(end - start) / CLOCKS_PER_SEC;

        if (!status) 
        {
            std::cout << "Command completed with exit code " 
                      << status 
                      << " and took " 
                      << duration 
                      << " seconds." << std::endl;
        }
        else 
            std::cout << "Command did not complete successfully." << std::endl;
    } 
    else
        std::cerr << "Fork failed" << std::endl;
}

int main(int argc, char* argv[]) 
{
    if (argc < 2) 
    {
        std::cerr << "Usage: " << argv[0] << " <command> [arguments]" << std::endl;
        return 1;
    }
    do_command(argv + 1);
    return 0;
}
