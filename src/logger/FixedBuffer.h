#ifndef FIXED_BUFFER_H
#define FIXED_BUFFER_H

#include "NoCopyAble.h"
#include <string.h>
#include <string>
const int SmallBuffer = 4000;
const int LargeBuffer = 4000*1000;
/*
    一个固定大小的缓冲区，用于LogStream
*/
template<int SIZE>
class FixedBuffer : NoCopyAble{
public:
    FixedBuffer() : current(data) { };
    ~FixedBuffer() {};
    // 追加数据
    void append(const char * newdata, size_t len){
        if(static_cast<size_t>(GetAvail()) > len){
            memcpy(current, newdata, len);
            current += len;
        }
    };    
    // 移动写入指针
    void add(size_t len) { current += len; };

    // 返回可用空间          
    int GetAvail() const { return data + sizeof(data) - current; };
    
    // 返回已使用空间                           
    size_t GetLen() const { return sizeof(data); };
    
    // 返回当前写入指针位置     
    char * GetCur() { return current; };              
    
    // 转换缓冲区内容为string
    std::string toString() const { return std::to_string(data, GetLen); };                                
    
    // 重置缓冲区
    void reset() { current = data; };               
    
    // 清空缓冲区
    void clear() { memset(data, 0, sizeof data); };   

private:
    char data[SIZE];
    char *current;

};

#endif