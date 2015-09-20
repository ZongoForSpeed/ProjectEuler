#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <utility>

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2> & p)
{
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template<typename T1, typename T2, typename T3>
std::ostream& operator<<(std::ostream& os, const std::tuple<T1, T2, T3> & t)
{
    os << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ")";
    return os;
}

template<typename T1, typename T2, typename T3, typename T4>
std::ostream& operator<<(std::ostream& os, const std::tuple<T1, T2, T3, T4> & t)
{
    os << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ", " << std::get<3>(t) << ")";
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

template<typename T1, typename T2>
std::string concatener(const T1 & t1, const T2 & t2)
{
    std::ostringstream oss;
    oss << t1 << t2;
    return oss.str();
}

template<typename T1, typename T2, typename T3>
std::string concatener(const T1 & t1, const T2 & t2, const T3 & t3)
{
    std::ostringstream oss;
    oss << t1 << t2 << t3;
    return oss.str();
}

template<typename T1, typename T2, typename T3, typename T4>
std::string concatener(const T1 & t1, const T2 & t2, const T3 & t3, const T4 & t4)
{
    std::ostringstream oss;
    oss << t1 << t2 << t3 << t4;
    return oss.str();
}
