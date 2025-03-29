#include "Thread.h"
#include "CurrentThread.h"
#include <semaphore>
static std::atomic<int> ThreadPid = 0; // 导出静态变量

Thread::Thread(std::function<void()> func, const std::string &name = std::string()) : 
    started(false),
    joined(false),
    threadId(0),
    func(std::move(func)), // move 拿到func的所有权
    name(name)
{
    int _id = ++ThreadPid;
    std::string _name = "Thread" + std::to_string(_id);
    //std::cout << 
    this->name = _name;
}
Thread::~Thread(){
    if(started == true && joined == false){
        pThread->detach();
        // 分离线程 分离的线程只会在线程结束后自动释放
        // 主程序不会等待分离的线程
    }
}
void Thread::start(){
    started = true;
    sem_t sem; // 信号量计数，thread 版 set
    sem_init(&sem, false, 0); // 初始化
    pThread = std::shared_ptr<std::thread> (new std::thread([&](){
            threadId = CurrentThread::tid(); // 获取线程id
            sem_post(&sem); 
            func(); // 执行func 
        }
    ));
    /*
     * 这里必须等待获取上面新创建的线程的tid
     * 未获取到信息则不会执行sem_post，所以会被阻塞住
     * 如果不使用信号量操作，则别的线程访问tid时候，可能上面的线程还没有获取到tid
     */
    sem_wait(&sem);
}
void Thread::join(){
    joined = true;
    // 等待线程结束
    pThread->join();
}