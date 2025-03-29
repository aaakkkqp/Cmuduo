#ifndef THREADPOOL
#define THREADPOOL

#include "NoCopyAble.h"
#include "Thread.h"
#include <mutex>
#include <condition_variable>
#include <queue>
class ThreadPool : NoCopyAble{
public:
    explicit ThreadPool(const std::string &name = std::string("ThreadPool")); //名字当然叫ThreadPool(
    ~ThreadPool();
    //bool isRunning() const {return running;};
    void start();
    void stop();
private:
    std::string name; // 先起个名字
    bool isFull() const;
    bool running;
    void work();
    void add(std::function<void()>);
    std::function<void()> init(); 
    mutable std::mutex mutex_; //  互斥锁 保证线程同步
    std::condition_variable cond_v; // 条件变量锁
    std::deque<std::function<void()>> taskQue; // 任务队列
    std::vector<std::unique_ptr<Thread>> pool; // 主体池子

    int size; // 容量
};
#endif