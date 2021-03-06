#include "problemes.h"
#include "numerique.h"
#include "polygonal.h"

typedef std::vector<size_t> vecteur;

namespace {
    vecteur fraction_continue(size_t d) {
        vecteur resultat;
        size_t d2 = racine::racine_carre(d);
        size_t a = racine::racine_carre(d), p = 0, q = 1;
        do {
            resultat.push_back(a);
            p = a * q - p;
            q = (d - p * p) / q;
            a = (p + d2) / q;
        } while (q != 1);
        resultat.push_back(a);
        return resultat;
    }

    int128_t equation_pell(size_t d) {
        const auto c = fraction_continue(d);
        size_t l = c.size() - 1;
        size_t per = l % 2 == 0 ? l - 1 : 2 * l - 1;
        int128_t a = c[0];
        int128_t a1 = 1;
        int128_t b = a;
        int128_t b1 = 0;
        for (size_t i = 1; i <= per; i++) {
            int128_t t = a;
            a = a * c[(i - 1) % l + 1] + a1;
            a1 = t;
            t = b;
            b = b * c[(i - 1) % l + 1] + b1;
            b1 = t;
        }
        return a;
    }
}

ENREGISTRER_PROBLEME(66, "Diophantine equation") {
    // Consider quadratic Diophantine equations of the form:
    //
    //                                      x² – Dy² = 1
    //
    // For example, when D=13, the minimal solution in x is 649² – 13×180² = 1.
    //
    // It can be assumed that there are no solutions in positive integers when D is square.
    // 
    // By finding minimal solutions in x for D = {2, 3, 5, 6, 7}, we obtain the following:
    //
    //      3² – 2×2² = 1
    //      2² – 3×1² = 1
    //      9² – 5×4² = 1
    //      5² – 6×2² = 1
    //      8² – 7×3² = 1
    //
    // Hence, by considering minimal solutions in x for D ≤ 7, the largest x is obtained when D=5.
    //
    // Find the value of D ≤ 1000 in minimal solutions of x for which the largest value of x is obtained.
    int128_t maximum = 0;
    size_t resultat = 0;
    for (size_t d = 2; d <= 1000; ++d) {
        if (!polygonal::est_carre(d)) {
            int128_t x = equation_pell(d);
            if (x > maximum) {
                maximum = x;
                resultat = d;
            }
        }
    }
    return std::to_string(resultat);
}
