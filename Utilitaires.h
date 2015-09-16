#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <map>


template<typename T, typename V>
std::ostream& operator<<(std::ostream& os, const std::pair<T, V> & p)
{
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> & v)
{
    os << "[";
    bool first = true;
    for (const T & n: v)
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

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T> & s)
{
    os << "{";
    bool first = true;
    for (const T & n: s)
    {
        if (first)
            first = false;
        else
            std::cout << " ";
        std::cout << n;
    }
    os << "}";
    return os;
}

template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::map<K, V> & s)
{
    os << "{" << std::endl;
    for (const auto & p: s)
    {
        os << "    " << p.first << " => " << p.second << std::endl;
    }
    os << "}" << std::endl;
    return os;
}