#ifndef NOCOPYABLE_H
#define NOCOPYABEL_H

/*
禁止拷贝的类
    通过删除 = 与 构造函数 禁止拷贝
*/
class NoCopyAble{
public:
    NoCopyAble(const NoCopyAble &) = delete;
    NoCopyAble &operator=(const NoCopyAble &) = delete;

protected:
    NoCopyAble() = default;
    ~NoCopyAble() = default;
};

#endif