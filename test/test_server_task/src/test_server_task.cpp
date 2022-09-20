#include <iostream>
#include <event2/event.h>
#include <cstring>
#include "thread_pool.h"
#include "server_task.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <signal.h>
#endif

using namespace std;

void listen_cb(evutil_socket_t sock, sockaddr *address, int socklen, void *arg) {
    cout << "listen_cb in main()" << endl;
}

int main(int argc, char *argv[]) {
    // 跨平台
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
#else
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
        return 1;
    }
#endif
    // 获取端口号和线程数量
    int server_port;
    int thread_count;
    if (argc > 2) {
        server_port = atoi(argv[1]);
        thread_count = atoi(argv[2]);
    }

    // 初始化主线程池
    ThreadPool::Instance()->init(thread_count);

    // 初始化监听线程线程池
    ThreadPool server_pool;
    server_pool.init(1);

    // 初始化监听任务
    auto *task = new ServerTask();
    task->set_server_port(server_port);
    task->listen_cb = listen_cb;
    
    // 服务线程池接受任务
    server_pool.dispatch(task);

    while (1) {
        
    }

    return 0;
} 
