#include "problemes.h"
#include "utilitaires.h"
#include "combinatoire.h"

typedef boost::multiprecision::cpp_int nombre;

ENREGISTRER_PROBLEME(493, "Under The Rainbow") {
    // 70 colored balls are placed in an urn, 10 for each of the seven rainbow colors.
    //
    // What is the expected number of distinct colors in 20 randomly picked balls?
    //
    // Give your answer with nine digits after the decimal point (a.bcdefghij).
    double resultat = 7 * (1.0 - combinatoire::coefficient_binomial<nombre>(60, 20).convert_to<double>()
        / combinatoire::coefficient_binomial<nombre>(70, 20).convert_to<double>());
    return std::to_string(resultat, 9);
}
