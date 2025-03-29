//#ifdef EVENTLOOP_H
//#define EVENTLOOP_H

#include "NoCopyAble.h"
#include <atomic>
/* 禁止Eventloop copy
    1防止多个对象共享独占资源    
    2确保eventloop对象只能运行在绑定的线程中
*/
class EventLoop : NoCopyAble{
public:
    EventLoop();
    ~EventLoop();

//  基础功能：循环监听事件以及退出事件
    void loop();
    void quit();
    std::atomic<bool> isloop; // true = 正在循环 atomic 线程安全
    
};

//#endif