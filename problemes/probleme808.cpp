#include "problemes.h"
#include "timer.h"

#include "numerique.h"
#include "arithmetique.h"
#include "premiers.h"
#include "chiffres.h"
#include "racine.h"
#include "utilitaires.h"

#include <set>

typedef size_t nombre;

ENREGISTRER_PROBLEME(808, "Reversible Prime Squares") {
    // Both 169 and 961 are the square of a prime. 169 is the reverse of 961.
    //
    // We call a number a <dfn>reversible prime square</dfn> if:
    //      It is not a palindrome, and
    //      It is the square of a prime, and
    //      Its reverse is also the square of a prime.
    //
    // $169$ and $961$ are not palindromes, so both are reversible prime squares.
    //
    // Find the sum of the first $50$ reversible prime squares.
    std::set<nombre> premiers;
    {
        Timer t("Crible");
        premiers::crible235<nombre>(100'000'000, std::inserter(premiers, premiers.end()));
    }

    std::vector<nombre> reversible;

    for(nombre p: premiers) {
        nombre n = p * p;
        if (!chiffres::palindrome(n)) {
            nombre flip = chiffres::inverser_nombre(n);
            if (auto c = racine::carre_parfait(flip)) {
                if (premiers.contains(*c)) {
                    reversible.push_back(n);
                    if (reversible.size() == 50) {
                        break;
                    }
                }
            }
        }
    }

    std::cout << reversible << std::endl;

    return std::to_string(std::reduce(reversible.begin(), reversible.end()));
}
