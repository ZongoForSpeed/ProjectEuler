#pragma once

#include "numerique.h"

#include <algorithm>
#include <deque>
#include <numeric>
#include <sstream>
#include <vector>

namespace chiffres {
    template<typename Nombre, class Operation>
    void boucle_chiffre(Nombre n, Operation op, unsigned short base = 10) {
        static_assert(numeric::is_integral<Nombre>::value, "Nombre doit être un entier.");
        while (n != 0) {
            op(n % base);
            n /= base;
        }
    }

    template<typename Nombre>
    size_t nombre_chiffres(Nombre n, unsigned short base = 10) {
        size_t d = 0;
        boucle_chiffre(n, [&d](Nombre) { ++d; }, base);
        return d;
    }

    template<typename Nombre>
    Nombre somme_chiffres(Nombre n, unsigned short base = 10) {
        Nombre resultat = 0;
        boucle_chiffre(n, [&resultat](Nombre d) { resultat += d; }, base);
        return resultat;
    }

    template<typename Nombre>
    std::deque<Nombre> extraire_chiffres(Nombre n, unsigned short base = 10) {
        std::deque<Nombre> resultat;
        boucle_chiffre(n, [&resultat](Nombre d) { resultat.push_front(d); }, base);
        return resultat;
    }

    template<typename Nombre>
    bool palindrome(Nombre n, unsigned short base = 10) {
        const auto chiffres = extraire_chiffres(n, base);
        return std::equal(chiffres.begin(), chiffres.begin() + chiffres.size() / 2, chiffres.rbegin());
    }

    template<typename Nombre>
    bool pandigital(const Nombre &n, unsigned short base = 10) {
        std::vector<size_t> chiffres(base + 1, 0);
        boucle_chiffre(n, [&chiffres](Nombre d) { ++chiffres[d]; }, base);
        if (chiffres[0] != 0)
            return false;
        return std::all_of(chiffres.begin(), chiffres.end(), [](size_t c) { return c < 2; });
    }

    template<typename Nombre, class InputIterator1, class InputIterator2>
    Nombre conversion_nombre(InputIterator1 debut, InputIterator2 fin, unsigned short base = 10) {
        return std::accumulate(debut, fin, Nombre(0), [&base](const Nombre resultat, const Nombre chiffre) {
            return resultat * base + chiffre;
        });
    }

    template<typename Nombre>
    bool permutation_chiffres(Nombre n, Nombre m, unsigned short base = 10) {
        auto chiffres_n = extraire_chiffres(n, base);
        auto chiffres_m = extraire_chiffres(m, base);
        return std::is_permutation(chiffres_n.begin(), chiffres_n.end(), chiffres_m.begin());
    }

    template<typename Nombre>
    Nombre inverser_nombre(Nombre n, unsigned short base = 10) {
        Nombre resultat = 0;
        boucle_chiffre(n, [&resultat, &base](Nombre d) { resultat = base * resultat + d; }, base);
        return resultat;
    }

    template<typename Nombre>
    Nombre concatener(Nombre a, Nombre b) {
        std::stringstream ss;
        ss << a << b;
        Nombre r;
        ss >> r;
        return r;
    }

    template<typename Nombre>
    Nombre concatener(Nombre a, Nombre b, Nombre c) {
        std::stringstream ss;
        ss << a << b << c;
        Nombre r;
        ss >> r;
        return r;
    }

    template<typename Nombre>
    Nombre concatener(Nombre a, Nombre b, Nombre c, Nombre d) {
        std::stringstream ss;
        ss << a << b << c << d;
        Nombre r;
        ss >> r;
        return r;
    }
}
