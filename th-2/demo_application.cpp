#include <iostream>
#include <chrono>
#include "parallel_scheduler.h"
void example_task(int id)
{
    std::cout << "Task " << id << " is starting.\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Task " << id << " is done.\n";
}
int main()
{
    size_t pool_size = 4;
    parallel_scheduler scheduler(pool_size);
    for (int i = 0; i < 10; ++i)
        scheduler.run(example_task, i);
    std::this_thread::sleep_for(std::chrono::seconds(12));
    return 0;
}
