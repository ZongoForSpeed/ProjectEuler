#pragma once

#include <deque>
#include <ostream>

namespace std {

    template<class T, class Allocator = std::allocator<T> >
    std::ostream &operator<<(std::ostream &os, const deque<T, Allocator> &v) {
        os << "[";
        bool first = true;
        for (const T &n: v) {
            if (first)
                first = false;
            else
                os << " ";
            os << n;
        }
        os << "]";
        return os;
    }

}
