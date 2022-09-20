#include "client_task.h"
#include "com_task.h"
#include "thread_pool.h"

void ClientTask::get_dir() {
    // 创建一个连接任务 
    auto task = new ComTask();

    // 线程池分发任务
    ThreadPool::Instance()->dispatch(task);
}