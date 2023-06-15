#pragma once
#include <queue>
#include <mutex>

template<typename T>
class safeQueue
{
private:
    std::queue<T> dataQueue;
    std::mutex mtx;
public:
    safeQueue(){};
    ~safeQueue(){};
    void push(T data)
    {
        std::unique_lock<std::mutex> lck(mtx);
        dataQueue.push(std::move(data));
    }
    bool pop(T& data)
    {
        std::unique_lock<std::mutex> lck(mtx);
        if (dataQueue.empty())
            return false;
        data = std::move(dataQueue.front());
        dataQueue.pop();
        return true;
    }
    bool empty()
    {
        std::unique_lock<std::mutex> lck(mtx);
        return dataQueue.empty();
    }
};