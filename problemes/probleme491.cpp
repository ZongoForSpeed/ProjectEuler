#include <numeric>
#include "problemes.h"
#include "utilitaires.h"
#include "puissance.h"
#include "combinatoire.h"
#include "permutation.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::pair<nombre, nombre> paire;
typedef std::tuple<nombre, nombre, nombre> point;

ENREGISTRER_PROBLEME(491, "Double pandigital number divisible by 11") {
    // We call a positive integer double pandigital if it uses all the digits 0 to 9 exactly twice (with no leading zero).
    // For example, 40561817703823564929 is one such number.
    //
    // How many double pandigital numbers are divisible by 11?
    std::vector<nombre> pandigital(10);
    std::iota(pandigital.begin(), pandigital.end(), 0);

    nombre somme = (2 * std::reduce(pandigital.begin(), pandigital.end())) % 11;
    nombre longueur = pandigital.size();
    nombre produit_fact = combinatoire::factorielle(longueur) * combinatoire::factorielle(longueur - 1);

    // std::cout << "produit_fact = " << produit_fact << std::endl;
    nombre resultat = 0;
    for (nombre l = 4; l < longueur + 1; ++l) {
        nombre duplicats = longueur - l;
        auto puissance_2 = puissance::puissance<nombre>(2, 2 * duplicats);
        for (const auto &distribution: permutation::Combinaisons<nombre>(pandigital, l)) {
            for (const auto &dup: permutation::Combinaisons<nombre>(distribution, duplicats)) {
                std::vector<nombre> c(distribution.begin(), distribution.end());
                c.insert(c.end(), dup.begin(), dup.end());

                nombre sc = std::reduce(c.begin(), c.end());
                if ((2 * sc) % 11 == somme) {
                    // std::cout << "c = " << c << std::endl;
                    auto compteur = static_cast<nombre>(std::count_if(c.begin(), c.end(), [](const nombre &i) {
                        return i != 0;
                    }));
                    resultat += compteur * produit_fact / puissance_2;
                }

            }
        }
    }

    return std::to_string(resultat);
}
