#include "TimeStamp.h"
//static int SecondToMicro = TimeStamp::SecondToMicro;
TimeStamp TimeStamp::now(){
    struct timeval msANDs; // timeval 包括 ms与s 击 s:ms since 1970:01:01:00
    gettimeofday(&msANDs, NULL); // NULL 不需要时区
    return TimeStamp(msANDs.tv_sec * SecondToMicro + msANDs.tv_usec); // 构造函数
}

std::string TimeStamp::stringToDate(bool showMicroSecond) const{
    char buf[64];
    
    time_t seconds = static_cast<int64_t>(MicroSinceEpoch / SecondToMicro);
    time_t MicroSeonds = static_cast<int64_t>(MicroSinceEpoch % SecondToMicro);

    tm *time = localtime(&seconds); // iostream second转化到时间
    const char *formatted;

    if(showMicroSecond == true){
        // 年 月 日
        formatted = "%4d/%02d/%02d %02d:%02d:%02d.%06ld";
    }else{
        formatted = "%4d/%02d/%02d %02d:%02d:%02d";
    }
    snprintf(buf, sizeof buf, "%4d/%02d/%02d %02d:%02d:%02d.%06ld", //呃呃
        time->tm_year + 1900,
        time->tm_mon + 1,
        time->tm_mday,
        time->tm_hour,
        time->tm_min,
        time->tm_sec, MicroSeonds
    );
    return buf;
}
// test 2025/03/29 21:02:05.472843
// int main(){
//     TimeStamp time;
//     std::cout << time.now().stringToDate(true) << "\n";
// }