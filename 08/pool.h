#pragma once
#include <vector>
#include <ostream>
#include <istream>
#include <iostream>
#include <ctype.h>
#include <stdexcept>
#include <functional>
#include <unistd.h>


class ThreadPool
{
    std::atomic<bool> die {false};
    std::mutex qmutex;
    std::condition_variable new_or_finish;
    std::deque<std::function<void()>> deq;
    std::vector<std::thread> threads;
public:
    explicit ThreadPool(size_t poolSize)
    {
        for(size_t i = 0; i < poolSize; ++i)
        {
            threads.emplace_back(&ThreadPool::threads_function, this);
        }
    }

    ~ThreadPool()
    {
        die = true;
        new_or_finish.notify_all();
        for(auto& thread : threads)
            thread.join();
    }
    void threads_function()
    {
        while(true)
        {

            std::unique_lock<std::mutex> lock(qmutex);
            while(!deq.size() && !die)
                new_or_finish.wait(lock);
            if(die)
                return;
            auto task = deq.front();
            deq.pop_front();
            lock.unlock();
            task();
        }
    }

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>
    {
        auto task = std::make_shared<std::packaged_task<decltype(func(args...))()>>(std::bind(func, args...));
        auto future = task->get_future();
        std::unique_lock<std::mutex> lock(qmutex);
        deq.emplace_back([task](){(*task)();});
        lock.unlock();
        new_or_finish.notify_one();
        return future;
    }


};