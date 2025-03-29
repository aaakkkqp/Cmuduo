#ifndef LOGGING_H
#define LOGGING

class Logging{
public:
    enum LOG_LEVEL{ // 错误依次提高 LOG记录ERROR及以上的错误
        DEBUG,
        INFO,
        WARNING, // 未预期的错误
        ERROR,   // 程序操作失败 eg: IO失败
        CRITICAL 
    };
    Logging(const char* file);
    
};

#endif