#ifndef COM_TASK_H
#define COM_TASK_H
#include "task.h"
#include <string>

struct bufferevent;

class ComTask : public Task {
public:
    // 初始化函数
    virtual bool init() override;

    // 设定服务器ip, port
    void set_server_ip(std::string ip) {
        this->server_ip = server_ip;
    } 
    void set_server_port(int server_port) {
        this->server_port = server_port;
    }
private:
    // 上下文
    struct bufferevent *bev;
    // 服务区ip
    std::string server_ip;
    // 服务器端口号
    int server_port = 0;
};

#endif