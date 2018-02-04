#include "problemes.h"
#include "arithmetiques.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::tuple<nombre, nombre, nombre> triplet;

ENREGISTRER_PROBLEME(224, "Almost right-angled triangles II") {
    // Let us call an integer sided triangle with sides a ≤ b ≤ c barely obtuse if the sides satisfy a² + b² = c² - 1.
    //
    // How many barely obtuse triangles are there with perimeter ≤ 75,000,000?
    const nombre taille = 75000000;
    nombre resultat = 0;

    std::queue<triplet> q;

    q.push(std::make_tuple(2, 2, 3));
    ++resultat;

    while (!q.empty()) {
        nombre a1, b1, c1;
        std::tie(a1, b1, c1) = q.front();
        q.pop();

        nombre a2 = a1 - 2 * b1 + 2 * c1;
        nombre b2 = 2 * a1 - b1 + 2 * c1;
        nombre c2 = 2 * a1 - 2 * b1 + 3 * c1;
        if (a2 + b2 + c2 <= taille) {
            q.push(std::make_tuple(a2, b2, c2));
            ++resultat;
        }

        a2 = a1 + 2 * b1 + 2 * c1;
        b2 = 2 * a1 + b1 + 2 * c1;
        c2 = 2 * a1 + 2 * b1 + 3 * c1;
        if (a2 + b2 + c2 <= taille) {
            q.push(std::make_tuple(a2, b2, c2));
            ++resultat;
        }

        if (a1 != b1) {
            a2 = 2 * b1 + 2 * c1 - a1;
            b2 = b1 + 2 * c1 - 2 * a1;
            c2 = 2 * b1 + 3 * c1 - 2 * a1;
            if (a2 + b2 + c2 <= taille) {
                q.push(std::make_tuple(a2, b2, c2));
                ++resultat;
            }
        }
    }

    return std::to_string(resultat);
}
