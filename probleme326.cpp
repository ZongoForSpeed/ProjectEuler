#include "problemes.h"
#include "utilitaires.h"
#include "mp_nombre.h"
#include "matrice.h"

typedef std::vector<size_t> vecteur;

namespace {
    size_t a(size_t n) {
        size_t nd = n / 6;
        // a_{6n}   = 3n
        // a_{6n+1} = 4n + 1
        // a_{6n+2} = 3n + 1
        // a_{6n+3} = n
        // a_{6n+4} = 6n + 3
        // a_{6n+5} = n
        switch (n % 6) {
            case 0:
                return 3 * nd;
            case 1:
                return 4 * nd + 1;
            case 2:
                return 3 * nd + 1;
            case 4:
                return 6 * nd + 3;
            default:
                return nd;
        }
    }
}

ENREGISTRER_PROBLEME(326, "Modulo Summations") {
    // Let an be a sequence recursively defined by: a1 = 1, an = [Sum k.ak k = 1..n-1] mod n.
    //
    // So the first 10 elements of an are: 1,1,0,3,0,3,5,4,1,9.
    //
    // Let f(N,M) represent the number of pairs (p,q) such that:
    //
    // 1 ≤ p ≤ q ≤ N and [Sum ai i = p..q] mod M = 0
    //
    // It can be seen that f(10,10)=4 with the pairs (3,3), (5,5), (7,9) and (9,10).
    //
    // You are also given that f(10^4,10^3)=97158.
    // Find f(10^12,10^6).
    const size_t N = 1000000000000ULL;
    const size_t M = 1000000;

    vecteur sommes(M, 0);
    sommes.front() += 1 + N / (6 * M);

    size_t courant = 0;
    for (size_t n = 1; n < std::min(6 * M, N + 1); n++) {
        courant += a(n);
        courant %= M;
        sommes[courant] += 1 + (N - n) / (6 * M);
    }

    size_t resultat = 0;
    for (size_t n : sommes) {
        resultat += n * (n - 1) / 2;
    }
    return std::to_string(resultat);
}
