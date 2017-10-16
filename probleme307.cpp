#include "problemes.h"
#include "arithmetiques.h"

typedef unsigned long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(307, "Chip Defects") {
    // k defects are randomly distributed amongst n integrated-circuit chips produced by a factory (any number of
    // defects may be found on a chip and each defect is independent of the other defects).
    //
    // Let p(k,n) represent the probability that there is a chip with at least 3 defects.
    //
    // For instance p(3,7) ≈ 0.0204081633.
    //
    // Find p(20 000, 1 000 000) and give your answer rounded to 10 decimal places in the form 0.abcdefghij
    nombre n = 1000000;
    nombre k = 20000;

    long double total = k * std::log(n);

    long double favorable = 0;
    for (nombre i = n - k + 1; i < n + 1; ++i) favorable += std::log(i);

    long double resultat = std::exp(favorable - total);
    nombre p = n - k + 1;
    nombre d = 1;
    long double factoriel = 0;
    long double tmp = 0;
    for (nombre i = 0; i < k; i += 2) {
        tmp += std::log(k - i) + std::log(k - i - 1) - std::log(2);
        favorable -= std::log(p);
        factoriel += std::log(d);
        resultat += std::exp(tmp + favorable - factoriel - total);

        p++;
        d++;
    }

    resultat = 1.0 - resultat;
    return std::to_string(resultat, 10);
}
