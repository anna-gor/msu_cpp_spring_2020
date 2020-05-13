#pragma once
#include <iostream>
#include <ctype.h>
#include <vector>
#include <future>
#include <thread>
#include <condition_variable>
#include <queue>
#include <functional>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <sys/stat.h>

int sort(const std::string& file_to_sort);

class ThreadPool
{

    std::condition_variable condition_;
    std::queue<std::function<void()>> myqueue;
    std::mutex m;
    std::vector< std::thread > pool;
    std::atomic<bool> terminate;

    void thread_func();

public:

    ThreadPool(size_t poolSize);

    ~ThreadPool();

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>{
        using type = decltype(func(args...));
        std::lock_guard<std::mutex> lock(m);
        auto task = std::make_shared<std::packaged_task<decltype(func(args...))()>>(std::bind(func, args...));
        auto future = task->get_future();
        myqueue.push([task](){(*task)();});
        condition_.notify_one();
        return future;
    }

};