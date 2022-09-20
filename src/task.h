#ifndef TASK_H
#define TASK_H
#include <event2/event.h>

class Task {
public:
    // 初始化任务
    virtual bool init() = 0;

    // thread_id get()/set()方法
    int get_thread_id() {
        return this->thread_id;
    }    
    void set_thread_id(int thread_id) {
        this->thread_id = thread_id;
    }

    // sock get()/set()方法
    int get_sock() {
        return this->sock;
    }
    void set_sock(int sock) {
        this->sock = sock;
    }

    // event_base get()/set()方法
    struct event_base *get_base() {
        return base;
    }
    void set_base(event_base *base) {
        this->base = base;
    } 
private:
    struct event_base *base;
    int sock;
    int thread_id;
};

#endif