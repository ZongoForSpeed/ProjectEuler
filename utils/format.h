#pragma once

#include <iomanip>

namespace format {
    template<typename Nombre>
    std::string to_fixed(Nombre n, int p) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(p) << n;
        return oss.str();
    }

    template<typename Nombre>
    std::string to_scientific(Nombre n, int p) {
        std::ostringstream oss;
        oss << std::scientific << std::setprecision(p) << n;
        std::string str = oss.str();
        // str.erase(std::remove(str.begin(), str.end(), '+'), str.end());
        if (str[0] == '+') {
            return str.substr(1);
        }
        return str;
    }

    template<typename Nombre>
    std::string to_string(Nombre n) {
        std::ostringstream oss;
        oss << n;
        return oss.str();
    }
}
