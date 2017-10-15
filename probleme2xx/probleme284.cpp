#include "problemes.h"
#include "arithmetiques.h"
#include "mp_nombre.h"

typedef std::vector<mp_nombre> vecteur;

namespace {
    mp_nombre restes_chinois(const vecteur &modulos, const vecteur &restes) {
        // https://fr.wikipedia.org/wiki/Th%C3%A9or%C3%A8me_des_restes_chinois
        if (modulos.size() != restes.size())
            return 0;

        mp_nombre n = 1;
        for (const auto &p: modulos) n *= p;

        mp_nombre resultat = 0;

        std::for_each2(modulos.begin(), modulos.end(), restes.begin(),
                       [&resultat, &n](const mp_nombre &modulo, const mp_nombre &reste) {
                           mp_nombre r = n / modulo;
                           if (auto inverse = mp_nombre::inverse_modulaire(r, modulo))
                               resultat += r * reste * (*inverse);
                           resultat %= n;
                       }
        );
        return resultat;
    }
}

ENREGISTRER_PROBLEME(284, "Steady Squares") {
    // The 3-digit number 376 in the decimal numbering system is an example of numbers with the special property that
    // its square ends with the same digits: 376² = 141376. Let's call a number with this property a steady square.
    //
    // Steady squares can also be observed in other numbering systems. In the base 14 numbering system, the 3-digit
    // number c37 is also a steady square: c37² = aa0c37, and the sum of its digits is c+3+7=18 in the same numbering
    // system. The letters a, b, c and d are used for the 10, 11, 12 and 13 digits respectively, in a manner similar to
    // the hexadecimal numbering system.
    //
    // For 1 ≤ n ≤ 9, the sum of the digits of all the n-digit steady squares in the base 14 numbering system is 2d8
    // (582 decimal). Steady squares with leading 0's are not allowed.
    // 
    // Find the sum of the digits of all the n-digit steady squares in the base 14 numbering system for 1 ≤ n ≤ 10000
    // (decimal) and give your answer in the base 14 system using lower case letters where necessary.
    const vecteur restes1{0, 1};
    const vecteur restes2{1, 0};

    mp_nombre borne = 1;
    vecteur modulos{2, 7};

    mp_nombre resultat = 1; // Cas n = 1 
    for (size_t k = 1; k < 10000 + 1; ++k) {
        // Cas n = 0 mod 2^k and n = 1 mod 7^k
        mp_nombre n1 = restes_chinois(modulos, restes1);
        if (n1 > borne)
            resultat += n1.somme_chiffres(14);
        // Cas n = 1 mod 2^k and n = 0 mod 7^k
        mp_nombre n2 = restes_chinois(modulos, restes2);
        if (n2 > borne)
            resultat += n2.somme_chiffres(14);

        borne *= 14;
        modulos.front() *= 2;
        modulos.back() *= 7;
    }

    return resultat.to_string(14);
}
