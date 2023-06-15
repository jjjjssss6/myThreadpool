#pragma once
#include <functional>
#include <vector>
#include <thread>
#include <iostream>
#include "safeQueue.h"

class threadpool
{
private:
    bool done;
    int threadNum;
    std::vector<std::thread> thds;
    safeQueue<std::function<void()>> workers;
    void work()
    {
        while (!done)
        {
            std::function<void()> task;
            if (workers.pop(task))
            {
                task();
            }
            else
            {
                std::this_thread::yield();
            }
        }
    }
public:
    threadpool() : done(false), threadNum(std::thread::hardware_concurrency())
    {
        for (int i = 0; i < threadNum; i++)
        {
            thds.emplace_back(std::thread(&threadpool::work, this));
        }
    }
    ~threadpool()
    {
        done = true;
        for (int i = 0; i < threadNum; i++)
        {
            if (thds[i].joinable())
                thds[i].join();
        }
    }
    template<typename Func>
    void submit(Func f)
    {
        workers.push(std::function<void()>(f));
    }
};