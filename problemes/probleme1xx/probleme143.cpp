#include <numeric>
#include "problemes.h"
#include "arithmetique.h"

#include <execution>
#include <map>
#include <set>
#include <vector>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::pair<nombre, nombre> paire;
typedef std::set<nombre> ensemble;
typedef std::map<nombre, vecteur> matrice;

ENREGISTRER_PROBLEME(143, "Investigating the Torricelli point of a triangle") {
    // Let ABC be a triangle with all interior angles being less than 120 degrees.
    // Let X be any point inside the triangle and let XA = p, XB = q, and XC = r.
    //
    // Fermat challenged Torricelli to find the position of X such that p + q + r was minimised.
    //
    // Torricelli was able to prove that if equilateral triangles AOB, BNC and AMC are constructed on each side of
    // triangle ABC, the circumscribed circles of AOB, BNC, and AMC will intersect at a single point, T, inside the
    // triangle.
    // Moreover he proved that T, called the Torricelli/Fermat point, minimises p + q + r.
    // Even more remarkable, it can be shown that when the sum is minimised, AN = BM = CO = p + q + r and that AN, BM
    // and CO also intersect at T.
    //
    // If the sum is minimised and a, b, c, p, q and r are all positive integers we shall call triangle ABC a
    // Torricelli triangle.
    // For example, a = 399, b = 455, c = 511 is an example of a Torricelli triangle, with p + q + r = 784.
    //
    // Find the sum of all distinct values of p + q + r ≤ 120000 for Torricelli triangles.
    nombre limite = 120000;
    matrice dictionnaire;
    for (nombre m = 1; m * m < limite; ++m) {
        for (nombre n = 1; n < m; ++n) {
            if ((m - n) % 3 == 0)
                continue;
            if (arithmetique::PGCD(n, m) != 1)
                continue;

            nombre a = 2 * n * m + n * n;
            nombre b = m * m - n * n;

            for (nombre k = 1; k * (a + b) < limite; ++k) {
                dictionnaire[a * k].push_back(b * k);
                dictionnaire[b * k].push_back(a * k);
            }
        }
    }

    for (auto &[k, v]: dictionnaire) std::ranges::sort(v);

    ensemble triplets;
    for (auto &[a, bs]: dictionnaire) {
        for (nombre b: bs) {
            if (auto itFind = dictionnaire.find(b);itFind != dictionnaire.end()) {
                vecteur resultat;
                std::set_intersection(bs.begin(), bs.end(),
                                      itFind->second.begin(), itFind->second.end(),
                                      std::back_inserter(resultat));

                for (nombre c: resultat)
                    if (a + b + c <= limite)
                        triplets.insert(a + b + c);
            }
        }
    }

    nombre resultat = std::reduce(std::execution::par, triplets.begin(), triplets.end());
    return std::to_string(resultat);
}
