#include "problemes.h"
#include "chiffres.h"

#include <fstream>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    bool impaire(nombre n) {
        while (n > 0) {
            if (n % 2 == 0)
                return false;
            n /= 10;
        }

        return true;
    }
}

ENREGISTRER_PROBLEME(145, "How many reversible numbers are there below one-billion?") {
    // Some positive integers n have the property that the sum [ n + reverse(n) ] consists entirely of odd (decimal)
    // digits. For instance, 36 + 63 = 99 and 409 + 904 = 1313. We will call such numbers reversible; so 36, 63, 409,
    // and 904 are reversible. Leading zeroes are not allowed in either n or reverse(n).
    //
    // There are 120 reversible numbers below one-thousand.
    // 
    // How many reversible numbers are there below one-billion (10^9)?
    nombre limite = 1000000000ULL;
    nombre resultat = 0;

    for (nombre n = 1; n < limite; ++n) {
        if (n % 10 != 0 && impaire(n + chiffres::inverser_nombre(n)))
            ++resultat;
    }
    return std::to_string(resultat);
}
