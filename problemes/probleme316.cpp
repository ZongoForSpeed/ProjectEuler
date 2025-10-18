#include "problemes.h"
#include "chiffres.h"
#include "puissance.h"

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(316, "Numbers in decimal expansions") {
    // Let p = p1 p2 p3 ... be an infinite sequence of random digits, selected from {0,1,2,3,4,5,6,7,8,9} with equal
    // probability.
    //
    // It can be seen that p corresponds to the real number 0.p1 p2 p3 ....
    // It can also be seen that choosing a random real number from the interval [0,1) is equivalent to choosing an
    // infinite sequence of random digits selected from {0,1,2,3,4,5,6,7,8,9} with equal probability.
    //
    // For any positive integer n with d decimal digits, let k be the smallest index such that
    // pk, pk+1, ...pk+d-1 are the decimal digits of n, in the same order.
    // Also, let g(n) be the expected value of k; it can be proven that g(n) is always finite and, interestingly, always
    // an integer number.
    //
    // For example, if n = 535, then
    // for p = 31415926535897...., we get k = 9
    // for p = 355287143650049560000490848764084685354..., we get k = 36
    // etc and we find that g(535) = 1008.
    //
    // Given that ∑ g(|10**6/n|), n=2..999 = 27280188, find ∑ g(|10**16/n|), n=2..999999
    nombre limite = puissance::puissance<nombre>(10, 16u);
    nombre resultat = 0;
    for (size_t n = 2; n < 1000000; ++n) {
        auto s = chiffres::extraire_chiffres(limite / n);
        nombre L = s.size();
        for (size_t k = 0; k <= L; k++) {
            size_t i;
            for (i = 0; i < k && s[i] == s[L - k + i]; ++i);
            if (i == k)
                resultat += puissance::puissance<nombre>(10, k);
        }
        resultat -= L;
    }
    return std::to_string(resultat);
}
