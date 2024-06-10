#pragma once
#include <queue>
#include <thread>
#include <mutex> // 对应linux中的pthread_mutex_t 线程互斥
#include <condition_variable> // 对应linux中的pthread_condition_t 线程通信 除此之外还有二元信号量


// 异步写日志的日志队列
template<typename T>
class LockQueue
{
public:
    // 多个worker线程都会写日志queue
    void Push(const T& data)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(data);
        // 调用 notify_one() 时，m_condvariable 没有进入阻塞状态，则 notify_one() 操作不会有任何可见效果
        m_condvariable.notify_one();
    }

    // 一个线程读日志queue，写日志文件
    T Pop()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        while (m_queue.empty())
        {
            // 日志队列为空，线程进入wait状态，并释放锁
            m_condvariable.wait(lock); 
        }
        T data = m_queue.front();
        m_queue.pop();
        return data;
    }
private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_condvariable;

};