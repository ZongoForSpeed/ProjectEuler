#include "problemes.h"
#include "arithmetiques.h"
#include "pythagoricien.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(75, "Singular integer right triangles") {
    // It turns out that 12 cm is the smallest length of wire that can be bent to form an integer sided right angle
    // triangle in exactly one way, but there are many more examples.
    //
    //      12 cm: (3,4,5)
    //      24 cm: (6,8,10)
    //      30 cm: (5,12,13)
    //      36 cm: (9,12,15)
    //      40 cm: (8,15,17)
    //      48 cm: (12,16,20)
    //
    // In contrast, some lengths of wire, like 20 cm, cannot be bent to form an integer sided right angle triangle, and
    // other lengths allow more than one solution to be found; for example, using 120 cm it is possible to form exactly
    // three different integer sided right angle triangles.
    //
    //      120 cm: (30,40,50), (20,48,52), (24,45,51)
    //
    // Given that L is the length of the wire, for how many values of L ≤ 1,500,000 can exactly one integer sided right
    // angle triangle be formed?
    const nombre limite = 1500000;

    vecteur solutions(limite + 1, 0);

    Pythagoricien pythagoricien(limite / 2);
    for (auto t: pythagoricien) {
        nombre a, b, c;
        std::tie(a, b, c) = t;

        nombre l = a + b + c;
        for (nombre k = 1; k * l <= limite; ++k) {
            solutions[k * l]++;
        }
    }

    auto resultat = std::count(solutions.begin(), solutions.end(), 1);
    return std::to_string(resultat);
}
