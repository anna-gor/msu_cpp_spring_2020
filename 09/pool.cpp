#include "pool.h"

void ThreadPool::thread_func(){
    std::function<void()> task;
    while(true)
    {
        {

            std::unique_lock<std::mutex> lock(m);
            while (myqueue.empty() && !terminate)
                condition_.wait(lock);
            if (myqueue.empty())
                return;
            task =  myqueue.front();
            myqueue.pop();
        }
        task();
    }
}

ThreadPool::ThreadPool(size_t poolSize):  terminate(false){
    for (size_t i = 0; i < poolSize; ++i){
        pool.emplace_back(&ThreadPool::thread_func, this);
    }
}

 ThreadPool::~ThreadPool(){
    terminate = true;
    condition_.notify_all();
    for(auto &thread: pool)
        thread.join();
}