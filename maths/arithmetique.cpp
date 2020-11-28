#include "arithmetique.h"
#include "mpz_nombre.h"

namespace arithmetique {

    template<>
    mpz_nombre PGCD(const mpz_nombre& a, const mpz_nombre& b) {
        return mpz_nombre::PGCD(a, b);
    }

    template<>
    int jacobi(const mpz_nombre &n, const mpz_nombre &k) {
        return mpz_nombre::jacobi(n, k);
    }
}
