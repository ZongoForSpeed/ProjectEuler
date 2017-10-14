#include "problemes.h"
#include "arithmetiques.h"
#include "polynome.h"

typedef long long nombre;
typedef std::vector<nombre> vecteur;
typedef std::vector<vecteur> matrice;

typedef boost::rational<nombre> fraction;

typedef Polynome<fraction> polynome;

namespace {
    polynome OP(const nombre k, const polynome &p) {
        std::vector<fraction> X;
        std::vector<fraction> Y;
        for (nombre n = 1; n < k + 1; ++n) {
            X.emplace_back(n);
            Y.push_back(p.valeur(n));
        }

        if (Y.size() == 1) {
            polynome resultat{Y.front()};
            return resultat;
        }

        polynome resultat;
        for (size_t i = 0; i < X.size(); ++i) {
            polynome pi{Y[i]};
            for (size_t j = 0; j < X.size(); ++j) {
                if (i != j) {
                    fraction f = X[i] - X[j];
                    f = 1 / f;
                    polynome pij{-X[j] * f, f};
                    pi *= pij;
                }
            }
            resultat += pi;
        }

        return resultat;
    }

    fraction BOP(const nombre k, const polynome &p) {
        const polynome op = OP(k, p);
        if (p == op)
            return 0;
        for (nombre n = 1;; ++n) {
            const auto valeur = op.valeur(n);
            if (p.valeur(n) != valeur)
                return valeur;
        }
    }
}

ENREGISTRER_PROBLEME(101, "Optimum polynomial") {
    // If we are presented with the first k terms of a sequence it is impossible to say with certainty the value of the
    // next term, as there are infinitely many polynomial functions that can model the sequence.
    //
    // As an example, let us consider the sequence of cube numbers. This is defined by the generating function,
    // u_n = n^3: 1, 8, 27, 64, 125, 216, ...
    //
    // Suppose we were only given the first two terms of this sequence. Working on the principle that "simple is best"
    // we should assume a linear relationship and predict the next term to be 15 (common difference 7). Even if we were
    // presented with the first three terms, by the same principle of simplicity, a quadratic relationship should be
    // assumed.
    //
    // We shall define OP(k, n) to be the nth term of the optimum polynomial generating function for the first k terms
    // of a sequence. It should be clear that OP(k, n) will accurately generate the terms of the sequence for n ≤ k, and
    // potentially the first incorrect term (FIT) will be OP(k, k+1); in which case we shall call it a bad OP (BOP).
    //
    // As a basis, if we were only given the first term of sequence, it would be most sensible to assume constancy; that
    // is, for n ≥ 2, OP(1, n) = u_1.
    //
    // Hence we obtain the following OPs for the cubic sequence:
    // 		OP(1, n) = 1			1, 1, 1, 1, ...
    // 		OP(2, n) = 7n−6         1, 8, 15, ...
    //		OP(3, n) = 6n²−11n+6    1, 8, 27, 58, ...
    //		OP(4, n) = n^3          1, 8, 27, 64, 125, ...
    //
    // Clearly no BOPs exist for k ≥ 4.
    //
    // By considering the sum of FITs generated by the BOPs (indicated in red above), we obtain 1 + 15 + 58 = 74.
    //
    // Consider the following tenth degree polynomial generating function:
    //
    // un = 1 − n + n^2 − n^3 + n^4 − n^5 + n^6 − n^7 + n^8 − n^9 + n^10
    //
    // Find the sum of FITs for the BOPs.
    fraction resultat = 0;
    polynome p {1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1};
    for (size_t k = 1; k < p.taille(); ++k) {
        const auto bop = BOP(static_cast<nombre>(k), p);
        resultat += bop;
    }

    return std::to_string(resultat.numerator());
}
