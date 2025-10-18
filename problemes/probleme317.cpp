#include "problemes.h"
#include "utilitaires.h"

#include <boost/math/constants/constants.hpp>
#include <vector>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(317, "Firecracker") {
    // A firecracker explodes at a height of 100 m above level ground. It breaks into a large number of very small
    // fragments, which move in every direction; all of them have the same initial velocity of 20 m/s.
    //
    // We assume that the fragments move without air resistance, in a uniform gravitational field with g=9.81 m/s2.
    //
    // Find the volume (in m3) of the region through which the fragments move before reaching the ground. Give your
    // answer rounded to four decimal places.
    const long double v = 20;
    const long double h = 100;
    const long double g = 9.81L;

    long double resultat = M_PIl * (2 * g * v * h + v * v * v) * (2 * g * v * h + v * v * v) / (4 * g * g * g);
    return std::to_fixed(resultat, 4);
}
