#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <sstream>

bool is_prime(int n)
{
    if (n <= 1)
        return false;
    for (int i = 2; i * i <= n; ++i)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

int calculate_prime(int m)
{
    int count = 0;
    int num = 2;
    while (count < m)
    {
        if (is_prime(num))
            count++;
        if (count < m)
            num++;
    }
    return num;
}

int main()
{
    int pipe1[2], pipe2[2];
    pid_t pid;

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
    {
        std::cerr << "Pipe creation failed" << std::endl;
        return 1;
    }

    pid = fork();
    if (pid == -1)
    {
        std::cerr << "Fork failed" << std::endl;
        return 1;
    }

    if (pid == 0)
    {
        close(pipe1[1]);
        close(pipe2[0]);

        while (true)
        {
            int m;
            read(pipe1[0], &m, sizeof(m));
            if (m == -1)
                break;

            std::cout << "[Child] Calculating " << m << "-th prime number..." << std::endl;
            int result = calculate_prime(m);
            std::cout << "[Child] Sending calculation result of prime(" << m << ")..." << std::endl;
            write(pipe2[1], &result, sizeof(result));
        }

        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);
    }
    else
    {
        close(pipe1[0]);
        close(pipe2[1]);

        while (true)
        {
            std::string input;
            std::cout << "[Parent] Please enter the number: ";
            std::getline(std::cin, input);
            if (input == "exit")
                break;

            int m = std::stoi(input);
            std::cout << "[Parent] Sending " << m << " to the child process..." << std::endl;
            write(pipe1[1], &m, sizeof(m));

            std::cout << "[Parent] Waiting for the response from the child process..." << std::endl;
            int result;
            read(pipe2[0], &result, sizeof(result));
            std::cout << "[Parent] Received calculation result of prime(" << m << ") = " << result << "..." << std::endl;
        }

        int exit_signal = -1;
        write(pipe1[1], &exit_signal, sizeof(exit_signal));

        close(pipe1[1]);
        close(pipe2[0]);
        wait(NULL);
    }

    return 0;
}
