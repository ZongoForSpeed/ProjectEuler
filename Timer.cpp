#include "Timer.h"
#include <iostream>

Timer::Timer(const std::string &t) : titre(t)
{
	std::cout << "Debut " << titre << " ..." << std::endl;
    _timer.start();
}

Timer::~Timer()
{
    _timer.stop();
	std::cout << "Fin " << titre << " en " << _timer.format(6, "%w") << " secondes " << std::endl;
}