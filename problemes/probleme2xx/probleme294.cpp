#include "problemes.h"
#include "arithmetique.h"
#include "timer.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    typedef std::map<std::pair<unsigned short/*somme*/, unsigned short/*reste*/>, nombre/*compteur*/> dictionnaire;

    dictionnaire algorithme(nombre chiffres, nombre modulo, nombre masque) {
        if (chiffres == 0) {
            dictionnaire resultat{{std::make_pair(0, 0), 1}};
            return resultat;
        }

        dictionnaire resultat;
        if (chiffres % 2 == 0) {
            dictionnaire recursion = algorithme(chiffres / 2, modulo, masque);

            auto m = puissance::puissance_modulaire<unsigned short>(10, chiffres / 2, modulo);

            for (const auto &p1: recursion)
                for (const auto &p2: recursion) {
                    unsigned short somme = p1.first.first + p2.first.first;
                    if (somme > modulo)
                        break;

                    unsigned short reste = (p1.first.second * m + p2.first.second) % modulo;
                    resultat[std::make_pair(somme, reste)] += p1.second * p2.second;
                    resultat[std::make_pair(somme, reste)] %= masque;
                }
        } else {
            dictionnaire recursion = algorithme(chiffres - 1, modulo, masque);
            for (unsigned short chiffre = 0; chiffre < 10; chiffre++) {
                for (const auto &p: recursion) {
                    unsigned short somme = p.first.first + chiffre;
                    if (somme > modulo)
                        break;

                    unsigned short reste = (p.first.second * 10 + chiffre) % modulo;
                    resultat[std::make_pair(somme, reste)] += p.second;
                    resultat[std::make_pair(somme, reste)] %= masque;
                }
            }
        }
        return resultat;
    }
}

ENREGISTRER_PROBLEME(294, "Sum of digits - experience #23") {
    // For a positive integer k, define d(k) as the sum of the digits of k in its usual decimal representation. Thus
    // d(42) = 4+2 = 6.
    //
    // For a positive integer n, define S(n) as the number of positive integers k < 10**n with the following properties:
    //
    // 		- k is divisible by 23 and
    // 		- d(k) = 23.
    //
    // You are given that S(9) = 263626 and S(42) = 6377168878570056.
    // Find S(11**12) and give your answer mod 10**9.
    nombre masque = 1000000000ULL;
    nombre modulo = 23;

    auto n = puissance::puissance<nombre, unsigned>(11, 12);
    nombre resultat = algorithme(n, modulo, masque)[std::make_pair(23, 0)];

    return std::to_string(resultat);
}
