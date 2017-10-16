#include "problemes.h"
#include "utilitaires.h"
#include "matrice.h"
#include "premiers.h"

typedef long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    nombre Mertens(nombre n, const vecteur &mertens) {
        static std::map<nombre, nombre> f;
        const auto m = static_cast<size_t>(n);
        if (m < mertens.size())
            return mertens[m];
        if (f.count(n))
            return f[n];

        nombre &ret = f[n];
        ret = 1;
        for (nombre i = 2, j; i <= n; i = j) {
            j = n / (n / i) + 1;
            ret += (i - j) * Mertens(n / i, mertens);
        }
        return ret;
    }

    nombre G(nombre v, nombre x, nombre modulo) {
        matrice::matrice<nombre> A(2, 2);
        A <<= v, 1, 0, 1;
        matrice::matrice<nombre> B = matrice::puissance_matrice(A, static_cast<size_t>(x), modulo);
        return v * B(0, 1) % modulo;
    }

    nombre g(nombre x, nombre modulo) {
        return G(3, x, modulo) - G(2, x, modulo);
    }
}

ENREGISTRER_PROBLEME(319, "Bounded Sequences") {
    // Let x1, x2,..., xn be a sequence of length n such that:
    //
    // x1 = 2
    // for all 1 < i ≤ n : xi-1 < xi
    // for all i and j with 1 ≤ i, j ≤ n : (xi)**j < (xj + 1)**i
    //
    // There are only five such sequences of length 2, namely: {2,4}, {2,5}, {2,6}, {2,7} and {2,8}.
    // There are 293 such sequences of length 5; three examples are given below:
    // {2,5,11,25,55}, {2,6,14,36,88}, {2,8,22,64,181}.
    //
    // Let t(n) denote the number of such sequences of length n. You are given that t(10) = 86195 and t(20) = 5227991891.
    //
    // Find t(10**10) and give your answer modulo 10**9.
    const nombre N = 10'000'000'000;
    const nombre modulo = 1'000'000'000;

    const size_t limite = 10'000'000;

    std::vector<size_t> premiers;
    premiers::crible235<size_t>(limite, std::inserter(premiers, premiers.begin()));

    vecteur mertens(limite + 1, 1);
    // Initialisation du vecteur avec les valeurs la fonction de Möbius
    mertens[0] = 0;
    mertens[1] = 1;
    // μ(n) = 1 if n is a square-free positive integer with an even number of prime factors.
    // μ(n) = −1 if n is a square-free positive integer with an odd number of prime factors.
    // μ(n) = 0 if n has a squared prime factor.
    for (size_t p: premiers) {
        for (size_t n = p; n < limite + 1; n += p) {
            mertens[n] *= -1;
        }
        for (size_t n = p * p; n < limite + 1; n += p * p) {
            mertens[n] = 0;
        }
    }

    for (size_t i = 0; i < limite + 1; ++i) {
        mertens[i + 1] += mertens[i];
        mertens[i + 1] %= modulo;
    }

    nombre resultat = 0, lx = 0;
    for (nombre i = 1, j; i <= N; i = j) {
        j = N / (N / i) + 1;
        nombre t = Mertens(j - 1, mertens) % modulo;
        resultat += (t - lx + modulo) * g(N / i, modulo) % modulo;
        lx = t;
    }

    return std::to_string(resultat % modulo);
}

