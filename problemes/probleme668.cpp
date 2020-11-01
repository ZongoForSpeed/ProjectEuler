#include "problemes.h"
#include "numerique.h"
#include "utilitaires.h"
#include "arithmetique.h"
#include "premiers.h"
#include "timer.h"
#include "racine.h"

namespace {
    size_t S(size_t n, const std::vector<size_t> &premiers) {
        premiers::MeisselLehmer algo(premiers);

        size_t resultat = n;
        for (size_t i = 1; i * i <= n; ++i) {
            resultat += algo.pi(n / i, i - 1);
        }
        return resultat;
    }
}

ENREGISTRER_PROBLEME(668, "Square root smooth Numbers") {
    // A positive integer is called square root smooth if all of its prime factors are strictly less than its square
    // root.
    // Including the number 1, there are 29 square root smooth numbers not exceeding 100.
    //
    // How many square root smooth numbers are there not exceeding 10'000'000'000 ?
    std::vector<size_t> premiers;
    premiers::crible235<size_t>(10'000'000, std::back_inserter(premiers));

    std::cout << "S(100) = " << S(100, premiers) << std::endl;
    size_t resultat = S(10'000'000'000, premiers);
    std::cout << "S(10'000'000'000) = " << resultat << std::endl;

    return std::to_string(resultat);
}
