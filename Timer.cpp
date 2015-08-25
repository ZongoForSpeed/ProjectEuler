#include "Timer.h"
#include <iostream>

Timer::Timer(const std::string &t) : _titre(t)
{
	std::cout << "Debut " << _titre << " ..." << std::endl;
    _timer.start();
}

Timer::~Timer()
{
    _timer.stop();
	std::cout << "Fin " << _titre << " en " << _timer.format(6, "%w") << " secondes " << std::endl;
}