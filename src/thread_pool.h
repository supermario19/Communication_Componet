#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>

class Thread;
class Task;

class ThreadPool {
public:
    // 单例模式
    static ThreadPool *Instance() {
        static ThreadPool pool;
        return &pool;
    }

    // 线程池初始化
    void init(int thread_count);

    // 任务分发
    void dispatch(Task *task);

    // 构造
    ThreadPool() = default;

    // 析构
    ~ThreadPool() = default;
private:
    // 线程数量
    int thread_count = 0;
    // 线程数组
    std::vector<Thread *> threads;
    // 上次分发线程
    int last_thread_id;
};

#endif