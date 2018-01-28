#pragma once

#include <string>
#include <boost/timer/timer.hpp>

class Timer {
    boost::timer::cpu_timer _timer;
    std::string _titre;

public:
    explicit Timer(const std::string &t);

    ~Timer();

    void etape(const std::string &t);
};
