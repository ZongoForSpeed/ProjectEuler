#include "problemes.h"
#include "puissance.h"
#include "utilitaires.h"
#include "mp_nombre.h"

typedef std::vector<size_t> vecteur;
typedef std::set<size_t> ensemble;

namespace {
    long double f(long double alpha, size_t n, size_t N) {
        return (std::log(1.0L * N) - n * std::log(1.0L - alpha)) /
               (std::log(1.0L + 2.0L * alpha) - std::log(1.0L - alpha));
    }

    long double recherche(std::function<long double(long double)> &f,
                          long double gauche,
                          long double droite,
                          long double epsilon) {
        if (std::abs(gauche - droite) < epsilon)
            return (gauche + droite) / 2;
        long double lr = (gauche * 2 + droite) / 3;
        long double rl = (gauche + droite * 2) / 3;
        if (f(lr) > f(rl))
            return recherche(f, lr, droite, epsilon);
        else
            return recherche(f, gauche, rl, epsilon);
    }
}

ENREGISTRER_PROBLEME(267, "Binary Circles") {
    // You are given a unique investment opportunity.
    //
    // Starting with £1 of capital, you can choose a fixed proportion, f, of your capital to bet on a fair coin toss
    // repeatedly for 1000 tosses.
    //
    // Your return is double your bet for heads and you lose your bet for tails.
    //
    // For example, if f = 1/4, for the first toss you bet £0.25, and if heads comes up you win £0.5 and so then have
    // £1.5. You then bet £0.375 and if the second toss is tails, you have £1.125.
    // 
    // Choosing f to maximize your chances of having at least £1,000,000,000 after 1,000 flips, what is the chance that
    // you become a billionaire?
    //
    // All computations are assumed to be exact (no rounding), but give your answer rounded to 12 digits behind the
    // decimal point in the form 0.abcdefghijkl.
    const size_t n = 1000;
    const auto N = puissance::puissance<size_t, unsigned>(10, 9);

    std::function<long double(long double)> lambda_f = [n, N](long double x) -> long double { return f(x, n, N); };

    const auto alpha = static_cast<size_t>(std::ceil(f(recherche(lambda_f, 0.01L, 0.99L, 0.000001L), n, N)));

    std::vector<mp_nombre> C{1};
    for (size_t k = 1; k < n + 1; ++k) {
        C.push_back(C.back() * (n - k + 1) / k);
    }

    mp_nombre resultat = 0;
    for (size_t k = alpha; k < n + 1; ++k) {
        resultat += C[k];
    }

    auto masque = puissance::puissance<size_t, unsigned>(10, 13);
    resultat *= masque;
    resultat /= mp_nombre::puissance(2, n);
    long double solution = resultat.get_double() / masque;

    return std::to_string(solution, 12);
}
