#include "problemes.h"
#include "timer.h"
#include "arithmetique.h"
#include "multidimension.h"

#include <set>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    void fusion(const std::set<nombre> &v1, const std::set<nombre> &v2, vecteur &resultat) {
        std::set<nombre> s;
        std::ranges::set_union(v1, v2, std::inserter(s, s.begin()));
        resultat.assign(s.begin(), s.end());
    }
}

ENREGISTRER_PROBLEME(223, "Almost right-angled triangles I") {
    // Let us call an integer sided triangle with sides a ≤ b ≤ c barely acute if the sides satisfy a² + b² = c² + 1.
    //
    // How many barely acute triangles are there with perimeter ≤ 25,000,000?
    const nombre taille = 25000000;

    // Cas a > 1:
    //     a² - 1 = c² - b²
    //     (a + 1)(a - 1) = (c - b)(c + b)
    const nombre limite = (taille + 1) / 3 + 1;

    std::vector<std::set<nombre>> diviseurs(limite, {1});
    {
        Timer t("diviseurs");
        diviseurs.front() = {0};
        for (nombre i = 2; i < limite; ++i)
            for (nombre j = i; j < limite; j += i) {
                diviseurs[j].emplace(i);
            }
    }

    nombre resultat = 0;
    {
        Timer t("résultat");
        // a² + b² = c² + 1
        // ==> a² - 1 = c² - b²
        // Cas a = 1:
        //     b = c
        resultat += (taille - 1) / 2;

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
    }

    return std::to_string(resultat);
}
