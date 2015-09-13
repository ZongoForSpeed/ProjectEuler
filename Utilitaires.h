#pragma once

#include <iostream>
#include <vector>
template<typename Nombre>
std::ostream& operator<<(std::ostream& os, const std::vector<Nombre> & v)
{
    os << "[";
    bool first = true;
    for (const Nombre & n: v)
    {
        if (first)
            first = false;
        else
            std::cout << " ";
        std::cout << n;
    }
    os << "]";
    return os;
}
