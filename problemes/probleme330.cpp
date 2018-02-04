#include "problemes.h"
#include "utilitaires.h"
#include "mp_nombre.h"
#include "premiers.h"
#include "arithmetiques.h"
#include "multidimension.h"

typedef long long int nombre;
typedef std::vector<nombre> vecteur;

namespace {
    multidimension<nombre, 2> coefficients_binomiaux(size_t n, nombre m) {
        size_t NN = n % static_cast<size_t>(m * (m - 1));
        multidimension<nombre, 2> cnk(NN + 1, NN + 1, 0);

        cnk[0][0] = 1;
        for (size_t p = 1; p <= NN; p++) {
            cnk[p][0] = 1;
            for (size_t k = 1; k <= p; k++) {
                cnk[p][k] = (cnk[p - 1][k - 1] + cnk[p - 1][k]) % m;
            }
        }
        return cnk;
    }

    nombre factoriel(size_t n, nombre m) {
        if (n == 0)
            return 1;
        else
            return (static_cast<nombre>(n) % m) * factoriel(n - 1, m);
    }

    /**
     * Compute D(n) [ m ] iteratively 
     */
    nombre somme(size_t n, nombre m) {
        auto limite = static_cast<size_t>(m * (m - 1));
        vecteur d(limite + 1, 0);
        d[0] = m - 1;
        if (n == 0)
            return 0;

        if (n > limite)
            return somme(n % limite, m);

        auto cnk = coefficients_binomiaux(n, m);
        for (size_t i = 1; i <= n; ++i) {
            for (size_t j = 0; j <= i - 1; ++j) {
                d[i] += (d[j] % m) * cnk[i][j];
            }

            if (i <= static_cast<size_t>(m - 1)) {
                d[i] -= factoriel(i, m);
            }
        }

        if (n <= static_cast<size_t>(m - 1))
            return (d[n] + factoriel(n, m)) % m;

        return d[n] % m;
    }
}

ENREGISTRER_PROBLEME(330, "Euler's Number") {
    // An infinite sequence of real numbers a(n) is defined for all integers n as follows:
    //
    //        1                     n < 0
    // a(n) = 
    //        ∑ a(n-i)/i! i=1..∞    n >= 0
    //
    // For example,
    // a(0) = e − 1
    // a(1) = 2e − 3
    // a(2) = 7/2.e − 6
    // with e = 2.7182818... being Euler's constant.
    //
    // It can be shown that a(n) is of the form	[A(n).e + B(n)] / n!
    // for integers A(n) and B(n).
    //
    // For example a(10) = [328161643 e − 652694486] /10!.
    //
    // Find A(10^9) + B(10^9) and give your answer mod 77 777 777.
    size_t n = 1000000000;

    nombre modulo = 77777777;
    vecteur premiers;
    premiers::crible235<nombre>(1000u, std::back_inserter(premiers));

    auto facteurs = arithmetiques::facteurs_premiers(modulo, premiers);
    vecteur restes;

    for (auto f : facteurs) {
        restes.push_back(somme(n, f) + f);
    }

    std::cout << facteurs << std::endl;
    std::cout << restes << std::endl;

    auto resultat = arithmetiques::restes_chinois<nombre>(facteurs, restes);

    return std::to_string(resultat);
}
