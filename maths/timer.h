#pragma once

#include <string>
#include <chrono>

class Timer {
    std::chrono::high_resolution_clock::time_point _debut;
    std::string _titre;

public:
    explicit Timer(const std::string &t);

    ~Timer();

    double timestamp() const;
};
