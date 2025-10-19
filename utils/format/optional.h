#pragma once

#include <optional>
#include <ostream>

namespace std {

    template<typename T>
    constexpr ostream &operator<<(ostream &os, std::optional<T> s) {
        if (s)
            os << *s;
        else
            os << "<none>";
        return os;
    }

}
