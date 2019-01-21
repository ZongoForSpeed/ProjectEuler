#include "problemes.h"
#include "arithmetique.h"

typedef std::vector<size_t> vecteur;

ENREGISTRER_PROBLEME(31, "Coin sums") {
    // In England the currency is made up of pound, £, and pence, p, and there are eight coins in general circulation:
    //
    // 1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
    // It is possible to make £2 in the following way:
    // 
    // 1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
    // How many different ways can £2 be made using any number of coins?
    size_t objectif = 200;
    const vecteur pieces{1, 2, 5, 10, 20, 50, 100, 200};
    vecteur dp(objectif + 1, 0);
    dp.front() = 1;
    for (const size_t piece: pieces) {
        for (size_t j = piece; j < objectif + 1; ++j) {
            dp[j] += dp[j - piece];
        }
    }

    return std::to_string(dp.back());
}
