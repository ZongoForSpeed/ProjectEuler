#include "problemes.h"
#include "arithmetique.h"
#include "multidimension.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    void fusion(const vecteur &v1, const vecteur &v2, vecteur &resultat) {
        std::set<nombre> s;
        for (auto d1: v1)
            for (auto d2: v2) {
                s.insert(d1 * d2);
            }

        resultat.assign(s.begin(), s.end());
    }
}

ENREGISTRER_PROBLEME(223, "Almost right-angled triangles I") {
    // Let us call an integer sided triangle with sides a ≤ b ≤ c barely acute if the sides satisfy a² + b² = c² + 1.
    //
    // How many barely acute triangles are there with perimeter ≤ 25,000,000?
    const nombre taille = 25000000;
    nombre resultat = 0;
    // a² + b² = c² + 1 
    // ==> a² - 1 = c² - b²
    // Cas a = 1:
    //     b = c
    resultat += (taille - 1) / 2;

    // Cas a > 1:
    //     a² - 1 = c² - b²
    //     (a + 1)(a - 1) = (c - b)(c + b)
    const nombre limite = (taille + 1) / 3 + 1;

    multidimension<nombre, 2> diviseurs(limite, {1});
    diviseurs.front() = {0};

    for (nombre i = 2; i < limite; ++i)
        for (nombre j = i; j < limite; j += i) {
            diviseurs[j].push_back(i);
        }

    for (nombre i = 2; i < limite - 1; ++i) {
        vecteur d;
        fusion(diviseurs[i - 1], diviseurs[i + 1], d);
        const size_t longueur = d.size();
        for (size_t k = longueur / 2; k < longueur; ++k) {
            const nombre difference = d[k] - d[longueur - k - 1];
            if (d[k] + i > taille)
                break;
            if (difference < 2 * i || difference & 1)
                continue;
            ++resultat;
        }
    }

    return std::to_string(resultat);
}
