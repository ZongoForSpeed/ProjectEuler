#pragma once

#include "numerique.h"
#include <boost/multiprecision/integer.hpp>
#include "utilitaires.h"

namespace puissance {
    template<typename Base, typename Exposant>
    constexpr Base puissance(Base base, Exposant exposant) {
        static_assert(std::is_arithmetic<Base>::value, "Base doit être un type arithmetique.");
        static_assert(std::is_arithmetic<Exposant>::value, "Exposant doit être un entier non signé.");

        Base resultat = 1;
        while (exposant > 0) {
            if (exposant % 2)
                resultat *= base;
            exposant /= 2;
            base *= base;
        }
        return resultat;
    }

    template<typename Base, typename Exposant, typename Modulo>
    constexpr Base puissance_modulaire(Base base, Exposant exposant, Modulo modulo) {
        static_assert(std::is_arithmetic<Base>::value, "Base doit être un type arithmetique.");
        static_assert(std::is_arithmetic<Exposant>::value, "Exposant doit être un type arithmetique.");
        static_assert(std::is_arithmetic<Modulo>::value, "Modulo doit être un type arithmetique.");

        return boost::multiprecision::powm(base, exposant, modulo);
/*
        Base resultat = 1;
        while (exposant > 0) {
            if (exposant % 2)
                resultat = (base * resultat) % modulo;
            exposant /= 2;
            base = (base * base) % modulo;
        }
        return resultat;
        */
    }
}
