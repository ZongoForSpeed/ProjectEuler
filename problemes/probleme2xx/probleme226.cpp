#include "problemes.h"
#include "arithmetique.h"

#include <fstream>

typedef unsigned long long nombre;

namespace {
    long double cercle(long double x) {
        return 0.5L - std::sqrt(0.0625L - (x - 0.25L) * (x - 0.25L));
    }

    long double s(long double x) {
        long double n = std::floor(x);
        return std::min(x - n, n + 1 - x);
    }

    long double blanc(long double x, size_t precision = 50) {
        long double resultat = 0.0L;
        nombre exposant = 1;
        for (size_t n = 0; n < precision; ++n) {
            resultat += s(exposant * x) / exposant;
            exposant *= 2;
        }

        return resultat;
    }
}

ENREGISTRER_PROBLEME(226, "A Scoop of Blancmange") {
    // The blancmange curve is the set of points (x,y) such that 0 ≤ x ≤ 1 and y = Sum(s(2^n.x)/2^n, n = 0..Inf),
    // where s(x) = the distance from x to the nearest integer.
    // 
    // The area under the blancmange curve is equal to ½, shown in pink in the diagram below.
    // 
    // https://projecteuler.net/project/images/p226_scoop2.gif
    // 
    // Let C be the circle with centre (¼,½) and radius ¼, shown in black in the diagram.
    // 
    // What area under the blancmange curve is enclosed by C?
    // Give your answer rounded to eight decimal places in the form 0.abcdefgh
    long double resultat = 0.0L;
    const long double dx = 0.000001L;

    for (long double x = 0.0L; x <= 0.5L; x += dx) {
        long double y = blanc(x) - cercle(x);
        if (y > 0)
            resultat += y * dx;
    }

    return std::to_string(resultat, 8);
}
