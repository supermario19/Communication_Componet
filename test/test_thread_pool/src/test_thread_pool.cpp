#include <iostream>
#include <event2/event.h>
#include <cstring>
#include "thread_pool.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <signal.h>
#endif

using namespace std;

#define PORT 12345

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

    while (1) {

    }

    return 0;
} 
