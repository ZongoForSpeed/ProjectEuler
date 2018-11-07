#pragma once

#include <type_traits>
#include <cmath>
#include <optional>

namespace racine {
    template<typename Nombre>
    constexpr Nombre racine_carre(Nombre n) {
        static_assert(std::is_arithmetic<Nombre>::value, "Nombre doit être un type arithmetique.");
        return static_cast<Nombre>(std::sqrt(n));
    }

    template<typename Nombre>
    constexpr Nombre racine_cubique(Nombre n) {
        static_assert(std::is_arithmetic<Nombre>::value, "Nombre doit être un type arithmetique.");
        return static_cast<Nombre>(std::cbrt(n));
    }

    template<typename Nombre>
    std::optional<Nombre> carre_parfait(Nombre x) {
        static_assert(std::is_arithmetic<Nombre>::value, "Nombre doit être un type arithmetique.");
        Nombre h = x & 0xF;
        switch (h) {
            case 0:
            case 1:
            case 4:
            case 9: {
                Nombre s = racine_carre<Nombre>(x);
                if (s * s == x)
                    return s;
                else
                    return std::nullopt;
            }
            default:
                return std::nullopt;
        }
    }
}
