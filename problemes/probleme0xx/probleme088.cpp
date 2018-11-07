#include "problemes.h"
#include "arithmetique.h"

#include <fstream>
#include <numeric>

typedef unsigned long long nombre;
typedef std::vector<nombre> vecteur;

namespace {
    bool verifier(nombre produit, nombre somme, nombre k) {
        if (somme < k)
            return false;
        if (produit == 1)
            return somme == k;
        if (k == 1)
            return produit == somme;

        for (nombre d = 2; d <= produit && d + k <= somme + 1; ++d) {
            if (produit % d == 0 && verifier(produit / d, somme - d, k - 1))
                return true;
        }
        return false;
    }
}

ENREGISTRER_PROBLEME(88, "Product-sum numbers") {
    // A natural number, N, that can be written as the sum and product of a given set of at least two natural numbers,
    // {a1, a2, ... , ak} is called a product-sum number:
    // N = a1 + a2 + ... + ak = a1 × a2 × ... × ak.
    //
    // For example, 6 = 1 + 2 + 3 = 1 × 2 × 3.
    // 
    // For a given set of size, k, we shall call the smallest N with this property a minimal product-sum number. The
    // minimal product-sum numbers for sets of size, k = 2, 3, 4, 5, and 6 are as follows.
    // 
    //      k=2: 4 = 2 × 2 = 2 + 2
    //      k=3: 6 = 1 × 2 × 3 = 1 + 2 + 3
    //      k=4: 8 = 1 × 1 × 2 × 4 = 1 + 1 + 2 + 4
    //      k=5: 8 = 1 × 1 × 2 × 2 × 2 = 1 + 1 + 2 + 2 + 2
    //      k=6: 12 = 1 × 1 × 1 × 1 × 2 × 6 = 1 + 1 + 1 + 1 + 2 + 6
    // 
    // Hence for 2≤k≤6, the sum of all the minimal product-sum numbers is 4+6+8+12 = 30; note that 8 is only counted
    // once in the sum.
    // 
    // In fact, as the complete set of minimal product-sum numbers for 2≤k≤12 is {4, 6, 8, 12, 15, 16}, the sum is 61.
    //
    // What is the sum of all the minimal product-sum numbers for 2≤k≤12000?
    std::set<nombre> resultat;
    for (nombre k = 2; k <= 12000; ++k) {
        for (nombre n = k + 1;; n++) {
            if (verifier(n, n, k)) {
                resultat.insert(n);
                break;
            }
        }
    }

    return std::to_string(std::accumulate(resultat.begin(), resultat.end(), 0ULL));
}
