#include "problemes.h"
#include "chiffres.h"
#include "utilitaires.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(74, "Digit factorial chains") {
    // The number 145 is well known for the property that the sum of the factorial of its digits is equal to 145:
    //
    //                                  1! + 4! + 5! = 1 + 24 + 120 = 145
    //
    // Perhaps less well known is 169, in that it produces the longest chain of numbers that link back to 169; it turns
    // out that there are only three such loops that exist:
    // 
    //      169 → 363601 → 1454 → 169
    //      871 → 45361 → 871
    //      872 → 45362 → 872
    // 
    // It is not difficult to prove that EVERY starting number will eventually get stuck in a loop.
    // For example,
    // 
    //      69 → 363600 → 1454 → 169 → 363601 (→ 1454)
    //      78 → 45360 → 871 → 45361 (→ 871)
    //      540 → 145 (→ 145)
    // 
    // Starting with 69 produces a chain of five non-repeating terms, but the longest non-repeating chain with a starting
    // number below one million is sixty terms.
    // 
    // How many chains, with a starting number below one million, contain exactly sixty non-repeating terms?
    vecteur factorielle = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

    nombre resultat = 0;
    for (nombre n = 1; n < 1000000; ++n) {
        std::set<nombre> chaine;
        nombre m = n;
        do {
            chaine.insert(m);
            nombre s = 0;
            chiffres::boucle_chiffre(m, [&s, &factorielle](nombre d) { s += factorielle[d]; });
            m = s;
        } while (chaine.find(m) == chaine.end());
        if (chaine.size() == 60)
            ++resultat;
    }

    return std::to_string(resultat);
}
