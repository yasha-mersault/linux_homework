#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <pwd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
void signal_handler(int sig, siginfo_t *info, void *context)
{
    if (sig == SIGUSR1)
    {
        pid_t sender_pid = info->si_pid;
        uid_t sender_uid = info->si_uid;
        struct passwd *user_info = getpwuid(sender_uid);
        std::string sender_username = user_info ? user_info->pw_name : "Unknown";
        unsigned long eip = 0xDEADBEEF;  // EIP
        unsigned long eax = 0xCAFEBABE;  // EAX
        unsigned long ebx = 0xBADC0DE;  // EBX

        std::cout << "Received a SIGUSR1 signal from process " << sender_pid
                  << " executed by " << sender_uid << " (" << sender_username << ").\n";
        std::cout << "State of the context: EIP = " << std::hex << eip
                  << ", EAX = " << eax << ", EBX = " << ebx << std::dec << ".\n";
    }
}
/////////////////////////////////////////////////////
int main()
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = signal_handler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGUSR1, &sa, nullptr) == -1)
    {
        std::cerr << "Error setting up signal handler.\n";
        return 1;
    }
    std::cout << "PID: " << getpid() << std::endl;
    while (true)
        sleep(10); 

    return 0;
}
