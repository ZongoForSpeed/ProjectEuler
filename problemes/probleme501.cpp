#include "problemes.h"
#include "premiers.h"
#include "puissance.h"
#include "timer.h"

#include <vector>
#include "racine.h"

namespace {
    size_t f(size_t n) {
        std::vector<size_t> premiers;

        {
            Timer t("crible");
            size_t limite_crible = racine::racine_cubique(n) + 1;
            limite_crible *= limite_crible;
            premiers::crible235<size_t>(limite_crible, std::back_inserter(premiers));
        }

        premiers::MeisselLehmer algo(premiers);

        size_t resultat = 0;
        {
            Timer t("forme p^7");
            // Forme p^7
            resultat += algo.pi(racine::racine(n, 7));
        }

        {
            Timer t("forme p1^3*p2 où p1 != p2");
            // Forme p1^3*p2 où p1 != p2
            for (const size_t &p : premiers) {
                auto p3 = puissance::puissance<size_t>(p, 3u);
                if (2 * p3 > n)
                    break;

                auto r = algo.pi(n / p3);
                if (n > p3 * p) --r;
                resultat += r;
            }
        }

        {
            Timer t("forme p1*p2*p3 où p1 < p2 < p3");
            // Forme p1*p2*p3 où p1 < p2 < p3
            auto l1 = racine::racine_cubique(n);
            for (size_t n1 = 0; n1 < premiers.size(); ++n1) {
                auto p1 = premiers.at(n1);
                if (p1 > l1)
                    break;

                auto l2 = racine::racine_carre(n / p1);

                for (size_t n2 = n1 + 1; n2 < premiers.size(); ++n2) {
                    auto p2 = premiers.at(n2);
                    if (p2 > l2)
                        break;

                    auto l = n / (p1 * p2);

                    if (l <= p2)
                        break;
                    resultat += algo.pi(l) - n2 - 1;
                }
            }
        }
        return resultat;
    }
}

ENREGISTRER_PROBLEME(501, "Eight Divisors") {
    // The eight divisors of 24 are 1, 2, 3, 4, 6, 8, 12 and 24.
    // The ten numbers not exceeding 100 having exactly eight divisors are 24, 30, 40, 42, 54, 56, 66, 70, 78 and 88.
    // Let f(n) be the count of numbers not exceeding n with exactly eight divisors.
    // You are given f(100) = 10, f(1000) = 180 and f(10^6) = 224427.
    // Find f(10^12).
    // std::cout << "f(100) = "<< f(100) << std::endl;
    // std::cout << "f(1000) = "<< f(1000) << std::endl;
    // std::cout << "f(1000000) = "<< f(1'000'000) << std::endl;

    return std::to_string(f(1'000'000'000'000));
}
