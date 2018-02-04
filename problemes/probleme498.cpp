#include "problemes.h"
#include "arithmetiques_modulaire.h"

namespace {
    template<size_t modulo>
    class Probleme498 {
        size_t n;
        size_t m;
        size_t d;
        
        typedef arithmetiques::nombre_modulaire<modulo> nombre;

    public:
        Probleme498(const size_t &_n, const size_t &_m, const size_t &_d) : n(_n),
                                                                            m(_m),
                                                                            d(_d) {}
        
        size_t algorithme() {
            size_t i = d;
            nombre resultat(0);
            while (i < m) {
                size_t j = i;
                nombre u = 0;
                nombre s = 0;
                bool first = true;
                while (j < m) {
                    if (first) {
                        u = nombre::coefficient_binomial(n, j) * nombre::coefficient_binomial(j, d);
                        // std::cout << "u_" << j << " = " << u << std::endl;
                        if (j % 2 == 0)
                            u = -u;
                        first = false;
                    } else if ((n - j + 1) % modulo == 0)
                        break;
                    else {
                        u *= n - j + 1;
                        u /= j - d;
                        u = -u;
                    }
                    ++j;
                    s += u;
                }
                // std::cout << "s_" << j << " = " << s << std::endl;
                resultat += s;
                i += modulo;
            }

            return resultat.value();
        }
    };
}

ENREGISTRER_PROBLEME(498, "Remainder of polynomial division") {
    // For positive integers n and m, we define two polynomials F_n(x) = x^n and G_m(x) = (x-1)^m.
    // We also define a polynomial Rn,m(x) as the remainder of the division of F_n(x) by G_m(x).
    // For example, R_6,3(x) = 15x² - 24x + 10.
    //
    // Let C(n, m, d) be the absolute value of the coefficient of the d-th degree term of R_n,m(x).
    // We can verify that C(6, 3, 1) = 24 and C(100, 10, 4) = 227197811615775.
    //
    // Find C(10^13, 10^12, 10^4) mod 999999937.
    Probleme498<999999937> p(10000000000000LL, 1000000000000LL, 10000);
    return std::to_string(p.algorithme());
}
