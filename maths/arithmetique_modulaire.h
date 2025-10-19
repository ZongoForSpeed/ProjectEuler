#pragma once

#include <ostream>
#include <utility>

#include "arithmetique.h"
#include "iterator.h"
#include "puissance.h"
#include "utilitaires.h"

namespace arithmetique_modulaire {

    template<typename Nombre, typename Conteneur>
    Nombre inverse_modulaire(Nombre a, Nombre n, const Conteneur &premiers) {
        // https://fr.wikipedia.org/wiki/Inverse_modulaire
        // si PGCD(a, n) = 1
        // alors a**phi(n) mod n = 1
        //       a**-1 = a**(phi(n) - 1) mod n
        Nombre _phi = arithmetique::phi<Nombre>(n, premiers);
        return puissance::puissance_modulaire<Nombre>(a, _phi - 1, n);
    }

    template<typename Nombre>
    Nombre inverse_modulaire(Nombre a, Nombre n) {
        Nombre inverse, ignore;
        arithmetique::Bezout(a, n, inverse, ignore);

        if (inverse < 0)
            return inverse + n;
        else
            return inverse;
    }

    template<typename Nombre, typename Conteneur1, typename Conteneur2, typename Conteneur3>
    Nombre restes_chinois(const Conteneur1 &modulos, const Conteneur2 &restes, const Conteneur3 &premiers) {
        // https://fr.wikipedia.org/wiki/Th%C3%A9or%C3%A8me_des_restes_chinois
        if (modulos.size() != restes.size())
            return 0;

        Nombre n = 1;
        for (const auto &p: modulos) n *= p;

        Nombre resultat = 0;

        iterator::for_each2(modulos.begin(), modulos.end(), restes.begin(),
                       [&resultat, &premiers, &n](const Nombre &modulo, const Nombre &reste) {
                           Nombre r = n / modulo;
                           resultat += r * inverse_modulaire(r, modulo, premiers) * reste;
                           resultat %= n;
                       }
        );
        return resultat;
    }

    template<typename Nombre, typename Conteneur1, typename Conteneur2>
    Nombre restes_chinois(const Conteneur1 &modulos, const Conteneur2 &restes) {
        // https://fr.wikipedia.org/wiki/Th%C3%A9or%C3%A8me_des_restes_chinois
        if (modulos.size() != restes.size())
            return 0;

        Nombre n = 1;
        for (const auto &p: modulos) n *= p;

        Nombre resultat = 0;

        iterator::for_each2(modulos.begin(), modulos.end(), restes.begin(),
                       [&resultat, &n](const Nombre &modulo, const Nombre &reste) {
                           Nombre r = n / modulo;
                           resultat += r * inverse_modulaire(r, modulo) * reste;
                           resultat %= n;
                       }
        );
        return resultat;
    }
}
