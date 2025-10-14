#pragma once

#include <string>
#include <chrono>

class Timer {
    const std::chrono::high_resolution_clock::time_point _debut;
    const std::string _titre;

public:
    explicit Timer(std::string t);

    ~Timer();

    [[nodiscard]] double timestamp() const;
};
