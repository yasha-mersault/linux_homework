#ifndef PARALLEL_SCHEDULER_H
#define PARALLEL_SCHEDULER_H

#include <thread>
#include <queue>
#include <functional>
#include <vector>
#include <mutex>
#include <condition_variable>

class parallel_scheduler
{
public:
    parallel_scheduler(size_t capacity);
    ~parallel_scheduler();
    template <typename Func, typename Arg>
    void run(Func&& func, Arg&& arg);
private:
    void worker();
    size_t capacity;
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> task_queue;
    std::mutex queue_mutex;
    std::condition_variable cv;
    bool stop;
};

template <typename Func, typename Arg>
void parallel_scheduler::run(Func&& func, Arg&& arg)
{
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        task_queue.push([f = std::forward<Func>(func), a = std::forward<Arg>(arg)]() {f(a);});
    }
    cv.notify_one();
}
#endif // PARALLEL_SCHEDULER_H
