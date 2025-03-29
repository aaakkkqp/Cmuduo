#ifndef CURRENT_THREAD
#define CURRENT_THREAD

#include <unistd.h>
#include <sys/syscall.h>
namespace CurrentThread{
    // __thread 每个线程各有一个实体互不干扰
    extern __thread int _cacheThreadID;
    void cacheid();
    inline int tid(){
        // 不期望 _cacheTreadID == 0 low expect 减少编译器优化开支
        if(__builtin_expect(_cacheThreadID == 0, 0)){
            cacheid();
        }
        return _cacheThreadID;
    }
}

#endif