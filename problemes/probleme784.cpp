#include "problemes.h"
#include "timer.h"

#include "numerique.h"
#include "arithmetique.h"
#include "premiers.h"

#include <set>

typedef size_t nombre;

namespace {
    nombre F(const std::set<nombre>& premiers, nombre N) {
        nombre total = 0;
        for (nombre a = 2; a <= N; ++a) {
            nombre v = a * a - 1;
            auto diviseurs = arithmetique::diviseurs(v, premiers);
            for (nombre d: diviseurs) {
                if (d > a) {
                    break;
                }

                nombre p = a + d;

                if (p <= N) {
                    nombre q = a + (v / d);
                    total += p + q;
                } else {
                    break;
                }
            }
        }

        return total;
    }
}

ENREGISTRER_PROBLEME(784, "Reciprocal Pairs") {
    // Let's call a pair of positive integers p, q (p < q) reciprocal, if there is a positive integer r < p
    // such that r equals both the inverse of p modulo q and the inverse of q modulo p.
    //
    // For example, (3, 5) is one reciprocal pair for r = 2.
    // Let F(N) be the total sum of p+q for all reciprocal pairs (p, q) where p <= N.
    //
    // F(5) = 59 due to these four reciprocal pairs (3, 5), (4, 11), (5, 7) and (5, 19).
    //
    // You are also given F(10²) = 697317.
    //
    // Find F(2.10^6).
    std::set<nombre> premiers;
    {
        Timer t("crible235");
        premiers::crible235<nombre>(200'000'000, std::inserter(premiers, premiers.end()));
    }

    std::cout << "F(5) = " << F(premiers, 5) << std::endl;
    std::cout << "F(100) = " << F(premiers, 100) << std::endl;


    return std::to_string(F(premiers, 2'000'000));
}
