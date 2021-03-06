#include "problemes.h"
#include "arithmetique.h"

typedef long long nombre;
typedef std::vector<nombre> vecteur;

ENREGISTRER_PROBLEME(78, "Coin partitions") {
    // Let p(n) represent the number of different ways in which n coins can be separated into piles.
    // For example, five coins can be separated into piles in exactly seven different ways, so p(5)=7.
    //
    //      OOOOO
    //      OOOO O
    //      OOO OO
    //      OOO O O
    //      OO OO O
    //      OO O O O
    //      O O O O O
    //
    // Find the least value of n for which p(n) is divisible by one million.
    std::vector<nombre> partition = {1};
    size_t n = 1;
    while (true) {
        nombre p = 0;
        for (size_t k = 1; k <= n; ++k) {
            if (2 * n >= k * (3 * k - 1))
                p += (k % 2 == 0 ? (-1) : 1) * partition[n - k * (3 * k - 1) / 2];
            if (2 * n >= k * (3 * k + 1))
                p += (k % 2 == 0 ? (-1) : 1) * partition[n - k * (3 * k + 1) / 2];
        }

        if (p % 1000000 == 0)
            break;

        ++n;
        partition.push_back(p % 1000000);
    }

    return std::to_string(n);
}
