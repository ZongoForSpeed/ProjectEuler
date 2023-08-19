#pragma once

#include <cmath>
#include <optional>
#include "puissance.h"

namespace racine {
    template<typename Nombre>
    constexpr Nombre racine_carre(Nombre n) {
        static_assert(std::is_arithmetic<Nombre>::value, "Nombre doit être un type arithmetique.");
        auto x = static_cast<Nombre>(std::sqrt(n));
        while (x * x > n) --x;
        while ((x + 1) * (x + 1) <= n) ++x;
        return x;
    }

    template<typename Nombre>
    constexpr Nombre racine_cubique(Nombre n) {
        static_assert(std::is_arithmetic<Nombre>::value, "Nombre doit être un type arithmetique.");
        auto x = static_cast<Nombre>(std::cbrt(n));
        while (x * x * x > n) --x;
        while ((x + 1) * (x + 1) * (x + 1) <= n) ++x;
        return x;
    }

    template<typename Nombre>
    constexpr Nombre racine(Nombre n, size_t k) {
        static_assert(std::is_arithmetic<Nombre>::value, "Nombre doit être un type arithmetique.");
        auto x = static_cast<Nombre>(std::pow(n, 1.0 / static_cast<double>(k)));
        while (puissance::puissance<Nombre>(x, k) > n) --x;
        while (puissance::puissance<Nombre>(x + 1, k) <= n) ++x;
        return x;
    }

    template<typename Nombre>
    std::optional<Nombre> carre_parfait(Nombre x) {
        static_assert(std::is_arithmetic<Nombre>::value, "Nombre doit être un type arithmetique.");
        auto s = static_cast<Nombre>(std::sqrt(x));
        if (s * s == x)
            return s;
        else
            return std::nullopt;
    }
}
