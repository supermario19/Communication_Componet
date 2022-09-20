#ifndef SERVER_TASK_H
#define SERVER_TASK_H
#include "task.h"
#include <event2/event.h>

// 函数指针
typedef void (*listen_cb_ptr)(evutil_socket_t sock, sockaddr *address, int socklen, void *arg);


class ServerTask : public Task {
public:
    // 初始化任务
    virtual bool init() override;

    // server_port get() / set()方法
    void set_server_port(int server_port) {
        this->server_port = server_port;
    } 

    int get_server_port() {
        return server_port;
    }

public:
    // 回调函数
    listen_cb_ptr listen_cb;

private:
    // 监听端口号
    int server_port;
};

#endif