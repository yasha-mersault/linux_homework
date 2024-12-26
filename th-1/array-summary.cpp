#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <vector>
#include <numeric>

void sum_array_segment(int* arr, long start, long end, long& result)
{
    result = 0;
    for (long i = start; i < end; ++i)
        result += arr[i];
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: ./array-summary <array_size> <num_threads>" << std::endl;
        return 1;
    }

    long N = std::strtol(argv[1], nullptr, 10);
    int M = std::atoi(argv[2]);

    if (N <= 0 || M <= 0)
    {
        std::cerr << "Invalid input. Ensure array size (N) and number of threads (M) are positive." << std::endl;
        return 1;
    }

    int* arr = new int[N];
    std::srand(std::time(0));

    for (long i = 0; i < N; ++i)
        arr[i] = std::rand() % 100;

    long result = 0;
    clock_t start_time = clock();
    for (long i = 0; i < N; ++i)
        result += arr[i];
    clock_t end_time = clock();
    double time_without_threads = double(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "Time spent without threads: " << time_without_threads << std::endl;
    long segment_size = N / M;
    std::vector<std::thread> threads;
    std::vector<long> thread_results(M, 0);
    start_time = clock();
    for (int i = 0; i < M; ++i)
    {
        long start = i * segment_size;
        long end = (i == M - 1) ? N : start + segment_size;
        threads.push_back(std::thread(sum_array_segment, arr, start, end, std::ref(thread_results[i])));
    }
    for (auto& t : threads)
        t.join();
    long thread_sum = 0;
    for (long i = 0; i < M; ++i)
        thread_sum += thread_results[i];
    end_time = clock();
    double time_with_threads = double(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "Time spent with " << M << " threads: " << time_with_threads << std::endl;
    delete[] arr;
    return 0;
}

