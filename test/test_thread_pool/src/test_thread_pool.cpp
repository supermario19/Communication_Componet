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

int main() {
    // 跨平台
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
#else
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
        return 1;
    }
#endif
    // 初始化线程池
    ThreadPool::Instance()->init(10);

    while (1) {
        
    }

    return 0;
} 
