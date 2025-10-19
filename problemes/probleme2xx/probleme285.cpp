#include "problemes.h"
#include "arithmetique.h"
#include "format.h"
#include "utilitaires.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    long double aire_section_disque(long double r, long double x, long double y) {
        // http://villemin.gerard.free.fr/GeomLAV/Cercle/aaaAIRE/RectangT.htm
        return r * r * std::acos(y / r) / 2
               - y * std::sqrt(r * r - y * y) / 2
               - r * r * std::acos(std::sqrt(r * r - x * x) / r) / 2
               + std::sqrt(r * r - x * x) * std::abs(x) / 2
               - x * (std::sqrt(r * r - x * x) - y);
    }
}

ENREGISTRER_PROBLEME(285, "Pythagorean odds") {
    // Albert chooses a positive integer k, then two real numbers a, b are randomly chosen in the interval [0,1] with
    // uniform distribution.
    //
    // The square root of the sum (k·a+1)² + (k·b+1)² is then computed and rounded to the nearest integer. If the result
    // is equal to k, he scores k points; otherwise he scores nothing.
    //
    // For example, if k = 6, a = 0.2 and b = 0.85, then (k·a+1)2 + (k·b+1)2 = 42.05.
    // 
    // The square root of 42.05 is 6.484... and when rounded to the nearest integer, it becomes 6.
    // This is equal to k, so he scores 6 points.
    //
    // It can be shown that if he plays 10 turns with k = 1, k = 2, ..., k = 10, the expected value of his total score,
    // rounded to five decimal places, is 10.20914.
    //
    // If he plays 10**5 turns with k = 1, k = 2, k = 3, ..., k = 10**5, what is the expected value of his total score,
    // rounded to five decimal places?
    long double resultat = 0;
    // a et b appartient [0,1]
    // (k - 1/2)² < (ka+1)² + (kb+1)² < (k + 1/2)² 
    // (1 - 1/(2k))² < (a+1/k)² + (b+1/k)² < (1 + 1/(2k))²
    // correspond aux equations des cercles :
    //      - de centre (-1/k, -1/k) et rayon (1 + 1/(2k))², C1
    //      - de centre (-1/k, -1/k) et rayon (1 - 1/(2k))², C2
    // la probabilité de gagner devient l'aire de l'intersection du carré 
    // [0,1] x [0,1] avec le "donut" C2 - C1
    // 
    // en translatant les cercles les cercles à l'origine, le carre devient :
    //      [1/k, 1+1/k] x [1/k, 1+1/k]
    for (nombre k = 1; k <= 100000; ++k) {
        long double p = aire_section_disque(1.0L + 1.0L / (2.0L * k), 1.0L / k, 1.0L / k);
        if (k > 1) // dans le cas où k=1, l'aire de la petite section est nulle     
            p -= aire_section_disque(1.0L - 1.0L / (2.0L * k), 1.0L / k, 1.0L / k);
        resultat += k * p;
    }

    return format::to_fixed(resultat, 5);
}
