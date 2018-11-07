#include "problemes.h"
#include "arithmetique.h"

typedef boost::multiprecision::cpp_int nombre;
typedef std::vector<nombre> vecteur;

namespace {
    nombre nombre_facteur(const nombre &n, const nombre &p, const nombre &modulo) {
        nombre quotient = n / p;
        nombre resultat = quotient;

        while (quotient >= p) {
            quotient /= p;
            resultat += quotient;
            resultat %= modulo;
        }

        return resultat;
    }

    nombre NF(size_t p, size_t q, size_t n) {
        const nombre modulo = puissance::puissance<nombre>(p, n);
        size_t S = 290797;

        nombre resultat = 0;

        vecteur cache(p, 0);
        for (size_t i = 0; i <= q; ++i) {
            size_t T = S % p;
            S = (S * S) % 50515093;

            if (i < n) {
                resultat += nombre_facteur(T * puissance::puissance<nombre>(p, i), p, modulo);
            } else {
                if (cache[T] == 0) cache[T] = nombre_facteur(T * modulo, p, modulo);
                resultat += cache[T];
            }

            resultat %= modulo;
        }

        return resultat;
    }
}

ENREGISTRER_PROBLEME(288, "An enormous factorial") {
    // For any prime p the number N(p,q) is defined by N(p,q) = ∑n=0 to q Tn*p**n with Tn generated by the following
    // random number generator:
    //
    // S0 = 290797
    // Sn+1 = Sn² mod 50515093
    // Tn = Sn mod p
    // 
    // Let Nfac(p,q) be the factorial of N(p,q).
    // Let NF(p,q) be the number of factors p in Nfac(p,q).
    // 
    // You are given that NF(3,10000) mod 3**20=624955285.
    //
    // Find NF(61,10**7) mod 61**10
    nombre resultat = NF(61, 10000000, 10);
    return resultat.str();
}
