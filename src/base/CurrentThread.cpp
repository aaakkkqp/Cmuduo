#include "CurrentThread.h"

namespace CurrentThread{
    __thread int _cacheID = 0;
    void cacheID(){
        if(_cacheID == 0){ // = 0即未缓存线程， syscall得到tid
            _cacheID = static_cast<int>(::syscall(SYS_gettid));
        }
    }
}