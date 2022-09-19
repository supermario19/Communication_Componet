#ifndef THREAD_H
#define THREAD_H
#include "event2/event.h"
#include <list>
#include <mutex>

class Task;

class Thread {
public:
    Thread() = default;
    ~Thread() = default;

    // 线程启动
    void start();

    // 线程设置
    bool set_up();

    // 线程主函数
    void thread_main();

    // 回掉函数
    void notify(evutil_socket_t sock);

    // 线程激活
    void active();

    // 添加任务
    void add_task(Task *t);

    // 设置线程id
    void set_thread_id(int thread_id);

    // 获取线程id
    int get_thread_id();

    // 设置notify_fd
    void set_notify_fd(int notify_id);

    // 获取线程id
    int get_notify_fd();
private:
    // 线程编号
    int thread_id;
    // 管道写端口
    int notify_fd;
    // 上下文
    struct event_base *base;
    // 任务列表
    std::list<Task *> tasks;
    // lock
    std::mutex tasks_mutex;
};

#endif