#include "parallel_scheduler.h"
#include <iostream>

parallel_scheduler::parallel_scheduler(size_t capacity) : capacity(capacity), stop(false)
{
    for (size_t i = 0; i < capacity; ++i)
        threads.push_back(std::thread(&parallel_scheduler::worker, this));
}

parallel_scheduler::~parallel_scheduler()
{
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        stop = true;
    }
    cv.notify_all();
    for (auto& t : threads)
        if (t.joinable())
            t.join();
}
void parallel_scheduler::worker()
{
    while (true)
    {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            cv.wait(lock, [this]() { return stop || !task_queue.empty(); });
            if (stop && task_queue.empty())
                return;
            task = std::move(task_queue.front());
            task_queue.pop();
        }
        task();
    }
}
