#include "com_task.h"
#include <event2/bufferevent.h>
#include <cstring>
#include <iostream>
#include <sys/time.h>

using namespace std;

// 读回调函数
static void read_cb_internal(struct bufferevent *bev, void *ctx) {
    cout << "read_cb_internal" << endl;
}

// 写回调函数
static void write_cb_internal(struct bufferevent *bev, void *ctx) {
    cout << "write_cb_internal" << endl;
}

// 异常事件回调函数
static void event_cb_internal(struct bufferevent *bev, short what, void *ctx) {
    cout << "event_cb_internal" << endl;
}

bool ComTask::init() {
    // 1. 创建bufferevent上下文
    bev = bufferevent_socket_new(get_base(), -1, BEV_OPT_CLOSE_ON_FREE);

    if (!bev) {
        cerr << "bufferevent_socket_new error" << endl;
        return false;
    }

    // 2. 设置回调函数
    bufferevent_setcb(bev, read_cb_internal, write_cb_internal, event_cb_internal, bev);

    // 3. 设置读写
    bufferevent_enable(bev, EV_READ | EV_WRITE);

    // 4. 设置超时时间
    timeval timeout = {10, 0};
    bufferevent_set_timeouts(bev, &timeout, &timeout);

    // 5. 建立连接
    if (server_ip.empty()) {
        return true;
    }
    sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    evutil_inet_pton(AF_INET, server_ip.c_str(), &address.sin_addr.s_addr);
    address.sin_port = htons(server_port);
    int re = bufferevent_socket_connect(bev, (sockaddr *)&address, sizeof(address));
    if (re != 0) {
        return false;
    }
    return true;
}