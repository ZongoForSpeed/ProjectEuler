#pragma once

#include <map>
#include <ostream>

namespace std {

    template<
            class Key,
            class T,
            class Compare = std::less<Key>,
            class Allocator = std::allocator<std::pair<const Key, T> >
    >
    std::ostream &operator<<(std::ostream &os, const std::map<Key, T, Compare, Allocator> &s) {
        os << "{" << std::endl;
        for (const auto &p: s) {
            os << "    " << p.first << " => " << p.second << std::endl;
        }
        os << "}" << std::endl;
        return os;
    }

}
