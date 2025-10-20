#include "../problemes.h"
#include "matrice.h"
#include "puissance.h"
#include "mpz_nombre.h"

#include <fstream>

typedef long long int nombre;
typedef std::vector<nombre> vecteur;

namespace {
    template<typename Nombre>
    matrice::matrice<Nombre> puissance_matrice(matrice::matrice<Nombre> base, mpz_nombre& exposant, Nombre modulo) {
        matrice::matrice<Nombre> resultat(base.size1(), base.size2(), 0);
        for (size_t i = 0; i < base.size1(); ++i) resultat(i, i) = 1;

        while (exposant > 0) {
            if (exposant % 2 != 0) {
                resultat = boost::numeric::ublas::prod(resultat, base);
                for (auto &m: resultat.data()) m %= modulo;
            }
            exposant /= 2;
            base = boost::numeric::ublas::prod(base, base);
            for (auto &m: base.data()) m %= modulo;
        }
        return resultat;
    }

}

ENREGISTRER_PROBLEME(324, "Building a tower") {
    // Let f(n) represent the number of ways one can fill a 3×3×n tower with blocks of 2×1×1. 
    // You're allowed to rotate the blocks in any way you like+however, rotations, reflections etc of the tower itself 
    // are counted as distinct.
    //
    // For example (with q = 100000007) :
    // f(2) = 229,
    // f(4) = 117805,
    // f(10) mod q = 96149360,
    // f(10**3) mod q = 24806056,
    // f(10**6) mod q = 30808124.
    //
    // Find f(10**10000) mod 100000007.
    const long long modulo = 100000007;
    const size_t N = 10000;
    mpz_nombre exposant = mpz_nombre::puissance(10, N) / 2;
    vecteur C{679, 99923830, 3519127, 14088452, 35862961, 76806653, 56470433, 33422571, 39262562, 84928070, 25900794,
              74099213, 15071937, 60737445, 66577436, 43529574, 23193354, 64137046, 85911555, 96480880, 76177, 99999328,
              1};

    vecteur T{81862504, 75412110, 47925805, 63312159, 9101639, 12253197, 64015488, 68125412, 58262981, 72062, 18904145,
              71774943, 63444149, 7047816, 49444743, 13625499, 40041351, 96149360, 69563725, 64647289, 117805, 229, 1};

    matrice::matrice<nombre> a(C.size(), C.size(), 0);
    for (size_t i = 0; i < C.size(); ++i)
        a(0, i) = C[i] % modulo;

    for (size_t i = 0; i < C.size() - 1; ++i)
        a(i + 1, i) = 1;

    a = puissance_matrice(a, exposant, modulo);

    nombre c = 0;
    for (size_t i = 0; i < C.size(); ++i)
        c += a(C.size() - 1, i) * T[i];

    return std::to_string(c % modulo);
}
