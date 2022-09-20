#include "thread_pool.h"
#include "thread.h"
#include "task.h"
#include <unistd.h>
#include <thread>

using namespace std;

void ThreadPool::init(int thread_count) {
    // 上次分发任务线程
    this->last_thread_id = -1;

    // 线程id
    this->thread_count = thread_count;

    // 创建thread_count个线程
    for (int i = 0; i < thread_count; i++) {
        // 创建线程并且加入线程队列
        Thread *t = new Thread();
        t->set_thread_id(i + 1);
        t->start();
        threads.push_back(t);
        this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void ThreadPool::dispatch(Task *task) {
    if (!task) {
        return ;
    }
    int tid = (last_thread_id + 1) % thread_count;
    
    task->set_thread_id(tid);

    Thread *th = threads[tid];

    last_thread_id = tid;

    // 线程派发任务
    th->add_task(task);

    // 激活线程
    th->active();
}