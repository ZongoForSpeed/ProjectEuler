#pragma once

#include <sstream>

namespace utilitaires {
    template<typename T1, typename T2>
    std::string concatener(const T1 &t1, const T2 &t2) {
        std::ostringstream oss;
        oss << t1 << t2;
        return oss.str();
    }

    template<typename T1, typename T2, typename T3>
    std::string concatener(const T1 &t1, const T2 &t2, const T3 &t3) {
        std::ostringstream oss;
        oss << t1 << t2 << t3;
        return oss.str();
    }

    template<typename T1, typename T2, typename T3, typename T4>
    std::string concatener(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4) {
        std::ostringstream oss;
        oss << t1 << t2 << t3 << t4;
        return oss.str();
    }

    template<typename Nombre>
    constexpr bool egal(const Nombre &a, const Nombre &b, std::false_type /*is_floating_point*/) {
        return a == b;
    }

    template<typename Nombre>
    constexpr bool egal(const Nombre &a, const Nombre &b, std::true_type /*is_floating_point*/) {
        return std::abs(b - a) < std::numeric_limits<Nombre>::epsilon();
    }

    template<typename Nombre>
    constexpr bool egal(const Nombre &a, const Nombre &b) {
        return egal(a, b, std::is_floating_point<Nombre>());
    }
}
