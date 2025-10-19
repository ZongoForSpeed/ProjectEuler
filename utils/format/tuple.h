#pragma once

#include <ostream>
#include <tuple>
#include <utility>

namespace std {

    template<typename T1, typename T2>
       constexpr std::ostream &operator<<(std::ostream &os, const pair<T1, T2> &p) {
        os << "(" << p.first << ", " << p.second << ")";
        return os;
    }

    template<typename T1, typename T2, typename T3>
    constexpr std::ostream &operator<<(std::ostream &os, const std::tuple<T1, T2, T3> &t) {
        os << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ")";
        return os;
    }

    template<typename T1, typename T2, typename T3, typename T4>
    constexpr std::ostream &operator<<(std::ostream &os, const std::tuple<T1, T2, T3, T4> &t) {
        os << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ", " << std::get<3>(t)
           << ")";
        return os;
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
    constexpr std::ostream &operator<<(std::ostream &os, const std::tuple<T1, T2, T3, T4, T5> &t) {
        os << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t) << ", " << std::get<3>(t)
           << ", " << std::get<4>(t) << ")";
        return os;
    }

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    constexpr std::ostream &operator<<(std::ostream &os, const std::tuple<T1, T2, T3, T4, T5, T6> &t) {
        os << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ", " << std::get<2>(t)
           << ", " << std::get<3>(t) << ", " << std::get<4>(t) << ", " << std::get<5>(t) << ")";
        return os;
    }

}
