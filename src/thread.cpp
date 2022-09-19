#include "thread.h"
#include <iostream>
#include <thread>
#ifdef _WIN32
#else
#include <unistd.h>
#endif
#include "task.h"

using namespace std;

// 激活线程任务回调函数
void notify_cb(evutil_socket_t sock, short what, void *arg) {
    Thread *t = (Thread *)arg;

    t->notify(sock);
}

void Thread::start() {
    set_up();

    // 启动线程
    thread th(&Thread::thread_main, this);

    // 分离线程
    th.detach();
}

void Thread::thread_main() {
    cout << "thread " << thread_id << "begin" << endl;
    
    // 事件分发
    event_base_dispatch(base);

    // 事件销毁 
    event_base_free(base);

    cout << "thread " << thread_id << "end" << endl;
}

bool Thread::set_up() {
    // 创建event_base(无锁)
    event_config *evc = event_config_new();
    event_config_set_flag(evc, EVENT_BASE_FLAG_NOLOCK);
    base = event_base_new_with_config(evc);
    event_config_free(evc);
    if (!base) {
        cerr << "event_base_new() error" << endl;
        return false;
    }
    // 创建管道
#ifdef _WIN32
    // fds[0]为读端,fds[1]为写端口
    evutil_socket_t fds[2];
    if (evutil_socketpair(AF_INET, SOCK_STREAM, 0, fds) < 0) {
        cout << "evutil_socketpair() error" << endl;
        return false;
    }
    // 设置为非阻塞
    evutil_make_socket_nonblocking(fds[0]);
    evutil_make_socket_nonblocking(fds[1]);
#else
    int fds[2];
    if (pipe(fds)) {
        cerr << "pipe() error" << endl;
        return false;
    }
#endif

    // 读取端口加入监听事件, 写入端口保存
    notify_fd = fds[1];
    event *ev = event_new(base, fds[0], EV_READ | EV_PERSIST, notify_cb, this);
    event_add(ev, nullptr);
}

void Thread::notify(evutil_socket_t sock) {
    char buffer[2] = {0};
#ifdef _WIN32
    int len = recv(sock, buffer, 1, 0);
#else
    int len = read(sock, buffer, 1);
#endif
    
    if (len <= 0) {
        return;
    }
    cout << "thread " << thread_id << " active" << endl;

    // 获取任务并且初始化
    tasks_mutex.lock();
    if (tasks.empty()) {
        tasks_mutex.unlock();
        return;
    }
    Task *t = tasks.front();
    tasks.pop_front();
    tasks_mutex.unlock();

    t->init();
}

void Thread::active() {
#ifdef _WIN32
    int re = send(notify_fd, "c", 1, 0);
#else
    int re = write(notify_fd, "c", 1);
#endif
    if (re < 0) {
        cerr << "active() error" << endl;
    }
}

void Thread::add_task(Task *t) {
    if (!t) {
        return ;
    }
    t->set_base(base);
    tasks_mutex.lock();
    tasks.push_back(t);
    tasks_mutex.unlock();
}

void Thread::set_thread_id(int thread_id) {
    this->thread_id = thread_id;
}

int Thread::get_thread_id() {
    return thread_id;
}

// 设置notify_fd
void Thread::set_notify_fd(int notify_id) {
    this->notify_fd = notify_fd;
}

// 获取线程id
int Thread::get_notify_fd() {
    return notify_fd;
}