/**
 * @file rvm_threadsafe_queue.hpp
 * @author Potapov Veniamin (venya99fox@inbox.ru)
 * @brief Threadsafe queue implementation
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#ifndef RVM_THREADSAFE_QUEUE_CLASS
#define RVM_THREADSAFE_QUEUE_CLASS

#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

template<typename T>
class rvm_ThreadsafeQueue
{
private:
    mutable std::mutex mut;
    std::queue<T> data_queue;
    std::condition_variable data_cond;
public:
    rvm_ThreadsafeQueue()
    {}
    rvm_ThreadsafeQueue(rvm_ThreadsafeQueue const& other)
    {
        std::lock_guard<std::mutex> lk(other.mut);
        data_queue=other.data_queue;
    }
    void push(T new_value)
    {
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(new_value);
        data_cond.notify_one();
    }
    void wait_and_pop(T& value)
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk,[this]{return !data_queue.empty();});
        value=data_queue.front();
        data_queue.pop();
    }

    bool try_pop(T& value)
    {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty())
            return false;
        value=data_queue.front();
        data_queue.pop();
        return true;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }
};
#endif // RVM_THREADSAFE_QUEUE_CLASS
 