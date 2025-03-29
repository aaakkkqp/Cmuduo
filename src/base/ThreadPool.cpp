#include "ThreadPool.h"
ThreadPool::ThreadPool(const std::string &name) : 
    name(name), 
    running(false), 
    mutex_(),  // 默认的构造
    cond_v() 
{}
ThreadPool::~ThreadPool(){
    stop(); // 唤醒剩下的
    for(const auto &i : pool){
        i->join(); // 等待所有线程结束
    }
}
void ThreadPool::start(){
    running = true;
    pool.reserve(size); // 扩容，避免vector的动态扩容(会随着大量的析构与重新分配)
    for(int i = 0; i < pool.size(); i++){
        pool.emplace_back(new Thread(std::bind(&ThreadPool::work, this), name + std::to_string(i)));
        // 绑定...
        pool[i]->start(); // 开始
    }
    if(pool.size() == 0 && init){
        init(); // 即使不创建也回调
    }
}
void ThreadPool::stop(){
    std::lock_guard<std::mutex> lock(mutex_); // 结束时防止析构函数里忘记解锁
    running = false;
    cond_v.notify_all(); // 唤醒所有线程
}
void ThreadPool::add(std::function<void()> func){
    std::unique_lock<std::mutex> lock(mutex_); // unique_lock 锁定, 保护taskQue的资源
    taskQue.emplace_back(func);
    cond_v.notify_one();
}
void ThreadPool::work(){
    try{
        if(init){
            init();
        }
        std::function<void()> task;
        while(true){
            { // 限制lock的生命周期, 否则每次循环其他线程也会持有锁
                std::unique_lock<std::mutex> lock(mutex_);
                while(taskQue.empty()){
                    if(running == false) {
                        return;
                    }
                    cond_v.wait(lock);
                }
                task = taskQue.front();
                taskQue.pop_back();
            }
            if(task != nullptr){ // 如果有task就运行
                task();
            }
        }
    }catch(...){
        
    }
}

