#ifndef TIMESTAMP
#define TIMESTAMP
//时间戳类
#include <sys/time.h>
#include <string>
#include <iostream>
class TimeStamp{
public:
    // 0 是失败的时间戳
    TimeStamp() : MicroSinceEpoch(0){};
    explicit TimeStamp(int64_t MicroSecond) : MicroSinceEpoch(MicroSecond) {};
    
    ~TimeStamp(){};

    static TimeStamp now(); // 获取当前时间戳 返回类为TimeStamp
    static TimeStamp invaild(){ return TimeStamp(); }; // 无效的时间戳

    std::string stringToDate(bool showMicroSecond) const; // 转化string为时间格式 yy:mm:dd
    
    int64_t GetMicroSecondStamp() const { return MicroSinceEpoch; }; // 毫秒时间戳
    time_t GetSecondStamp()const { return static_cast<time_t>(MicroSinceEpoch / SecondToMicro); }; // 秒时间戳
    
    static const int SecondToMicro = 1000000; // 换算单位 1s = 1000_000μs
private:
    int64_t MicroSinceEpoch; 
    /* 
        int64_t 固定占64位 因为时间格式固定
        存储为ms方便时间高精度
        再之后需求高精度时间不需要增加额外修改,也不会丢失过多信息
    */
};
#endif