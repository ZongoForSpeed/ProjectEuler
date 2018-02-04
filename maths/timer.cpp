#include <iostream>

#include "timer.h"

Timer::Timer(const std::string &t) : _titre(t) {
    std::cout << "Debut " << _titre << " ..." << std::endl;
    _debut = std::chrono::high_resolution_clock::now();
}

Timer::~Timer() {
    std::chrono::high_resolution_clock::time_point fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(fin - _debut);

    std::cout << "Fin " << _titre << " en " << time_span.count() << " secondes " << std::endl;
}
