#include "Time.hpp"
#include <chrono>
#include <string>
#include <sys/time.h>
#include <ctime>

Time::Time()
{
    _t = std::chrono::system_clock::now();
}

Time::Time(std::chrono::time_point<std::chrono::system_clock> t)
{
    _t = t;
}

double Time::since(Time* t)
{
    std::chrono::duration<double> elapsed = now() - t->time();

    return elapsed.count();
}

// ref: https://www.delftstack.com/howto/cpp/system-time-in-cpp/
std::string Time::toString()
{
    std::time_t time = std::chrono::system_clock::to_time_t(_t);
    std::string time_str = std::ctime(&time);
    time_str.resize(time_str.size() - 1);
    return time_str;    
}