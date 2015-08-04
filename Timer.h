#pragma once
#include <string>
#include <boost/timer/timer.hpp>

class Timer
{
private:
    boost::timer::cpu_timer _timer;
	std::string titre;

public:
	Timer(const std::string &t);
    ~Timer();
};
