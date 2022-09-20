#ifndef CLIENT_TASK_H
#define CLIENT_TASK_H
#include <string>
#include "com_task.h"
#include "thread_pool.h"

class ClientTask {
public:
    // 单例模式
    static ClientTask *Instance() {
        static ClientTask client;
        return &client;
    }

    // 初始化(线程)
    bool init() {
        ThreadPool::Instance()->init(10);
        return true;
    }

    // 获取目录
    void get_dir();

    // 设定服务器ip, port
    void set_server_ip(std::string ip) {
        this->server_ip = server_ip;
    }
    void set_server_root(std::string root) {
        this->server_root = server_root;
    } 
    void set_server_port(int server_port) {
        this->server_port = server_port;
    }
private:
    // 构造/析构函数
    ClientTask() = default;
    ~ClientTask() = default;
private:
    // 服务区ip
    std::string server_ip;
    // 服务区目录
    std::string server_root;
    // 服务器端口号
    int server_port = 0;
};

#endif