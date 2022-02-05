#ifndef TIME_H
#define TIME_H

#include <chrono>
#include <string>

class Time
{
    public:
        Time();
        Time(std::chrono::time_point<std::chrono::system_clock> t);
        inline std::chrono::time_point<std::chrono::system_clock> time() { return _t; }; 
        static std::chrono::time_point<std::chrono::system_clock> now() { return std::chrono::system_clock::now(); }
        static double since(Time* t);
        std::string toString();

    private:
        std::chrono::time_point<std::chrono::system_clock> _t;
};

#endif