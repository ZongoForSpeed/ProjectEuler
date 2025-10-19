#pragma once

#include <ostream>
#include <set>

namespace std {

    template<
            class Key,
            class Compare = std::less<Key>,
            class Allocator = std::allocator<Key>
    >
    std::ostream &operator<<(std::ostream &os, const std::set<Key, Compare, Allocator> &s) {
        os << "{";
        bool first = true;
        for (const Key &n: s) {
            if (first)
                first = false;
            else
                os << " ";
            os << n;
        }
        os << "}";
        return os;
    }

}
