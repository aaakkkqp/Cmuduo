#ifndef THREAD
#define THREAD
#include "NoCopyAble.h"
#include <functional>
#include <string>
#include <atomic>
#include <thread>
#include <memory>
class Thread : NoCopyAble{
public:
    void start(); // 开始线程
    void join(); // 加入线程
    // 线程不应该被隐式转换
    explicit Thread(std::function<void()> func, const std::string &name = std::string());
    ~Thread();

    bool isStarted() const { return started;};
    int GetThreadPid() const { return threadPid;};
    const std::string& GetName() const { return name;}; // const引用绑定

private:
    std::shared_ptr<std::thread> pThread; // 线程
    bool started; // 线程是否开始
    bool joined;  // 线程是否待加入
    int threadId; // 线程id
    std::string name; // 线程名字
    std::function<void()> func; // 线程函数，具体做的啥
    static std::atomic<int> threadPid; // 线程索引id, 全局应该只有一个
};

#endif