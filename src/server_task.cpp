#include "server_task.h"
#include <event2/event.h>
#include <event2/listener.h>
#include <iostream>
#include <cstring>

using namespace std;

// 回调函数
static void listen_cb_internal(struct evconnlistener *evc, evutil_socket_t sock, struct sockaddr *address, int socklen, void *arg) {
    auto *task = (ServerTask *)arg;
    if (task->listen_cb) 
        task->listen_cb(sock, address, socklen, arg);
    else
        cerr << "listen_callback is not set" << endl;
}

bool ServerTask::init() {
    if (server_port <= 0) {
        cerr << "server_port is invaild" << endl;
        return false;
    }
    // 监听端口
    sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(server_port);

    // 设置回调函数
    auto *evc = evconnlistener_new_bind(this->get_base(), listen_cb_internal, this, 
                                        LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE, 10, 
                                        (sockaddr *)&address, sizeof(address));
    if (!evc) {
        cerr << "listen port " << server_port << " failed" << endl;
        return false;
    }
    cout << "listen port " << server_port << " success" << endl;


    return true;
}