#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <cstdlib>

int main()
{
    while (true)
    {
        std::cout << "shell> ";
        std::string input;
        std::getline(std::cin, input);

        if (input == "exit")
            break;

        char* argv[10];
        int i = 0;

        char* token = std::strtok(&input[0], " ");
        while (token != nullptr && i < 10)
        {
            argv[i] = token;
            i++;
            token = std::strtok(nullptr, " ");
        }
        argv[i] = nullptr;

        pid_t pid = fork();

        if (pid == 0)
        {
            if (i > 0 && std::strncmp(argv[0], "silent", 6) == 0)
            {
                pid_t child_pid = getpid();
                std::string filename = std::to_string(child_pid) + ".log";
                FILE* log_file = fopen(filename.c_str(), "w");

                if (log_file != nullptr)
                {
                    dup2(fileno(log_file), STDOUT_FILENO);
                    dup2(fileno(log_file), STDERR_FILENO);
                    fclose(log_file);
                    execvp(argv[1], &argv[1]);
                }
                else
                {
                    std::cerr << "Failed to open log file" << std::endl;
                    exit(1);
                }
            }
            else
                execvp(argv[0], argv);

            std::cerr << "Command execution failed!" << std::endl;
            exit(1);
        }
        else if (pid > 0)
        {
            int status;
            waitpid(pid, &status, 0);
        }
        else
        {
            std::cerr << "Fork failed!" << std::endl;
            exit(1);
        }
    }

    return 0;
}
